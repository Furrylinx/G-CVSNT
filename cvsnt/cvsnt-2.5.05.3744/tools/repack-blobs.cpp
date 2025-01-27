//to build on linux: clang++ -std=c++17 -O2 gc-blobs.cpp blob_operations.cpp ./sha256/sha256.c -lz -lzstd -ogc-blobs

#include "simpleOsWrap.cpp.inc"
//#include "sha_blob_reference.h"
#include "src/details.h"
#include "content_addressed_fs.h"
#include <string>
#include <filesystem>
#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>
#include <atomic>
#include <ctime>
#include "flags.h"
#include "concurrent_queue.h"
#ifdef _WIN32
namespace fs = std::experimental::filesystem;
#else
namespace fs = std::filesystem;
#endif
using namespace caddressed_fs;

static size_t processed_files = 0;
static std::atomic<size_t> repacked_files = 0, affected_files = 0;
static std::atomic<int64_t> data_saved = 0;
static constexpr size_t maxQueuedItems = 1024;
static std::atomic<size_t> lastMessaged = 0;
static bool repack_unpacked = false;

void process_blob(const char *hash)
{
  affected_files++;
  const std::string filePath = caddressed_fs::get_file_path(caddressed_fs::get_default_ctx(), hash);
  const time_t mtime = get_file_mtime(filePath.c_str());
  int64_t ds = caddressed_fs::repack(caddressed_fs::get_default_ctx(), hash, repack_unpacked);
  if (ds != 0)
  {
    set_file_mtime(filePath.c_str(), mtime);
    repacked_files++;
  }
  data_saved += ds;
  if (affected_files > lastMessaged+32)
  {
    lastMessaged = size_t(affected_files);
    printf("...%lld processed, %lld repacked, saved %gMb\n", (long long)processed_files, (long long)repacked_files, data_saved/1024./1024.);
    fflush(stdout);
  }
}

static struct BlobProcessor
{
  BlobProcessor():queue(&threads){}
  void finish()
  {
    if (is_inited())
      queue.finishWork();
  }

  bool is_inited() const {return !threads.empty();}
  void init(int threads_count)
  {
    for (int ti = 0; ti < threads_count; ++ti)
      threads.emplace_back(std::thread(processor_thread_loop));
  }

  static void processor_thread_loop();
  void emplace(std::string &&hash)
  {
    queue.emplace(std::move(hash));
  }
  std::vector<std::thread> threads;
  concurrent_queue<std::string> queue;
} processor;

void BlobProcessor::processor_thread_loop()
{
  std::string task;
  while (processor.queue.wait_and_pop(task))
    process_blob(task.c_str());
}

static void process_sha_files_directory(const char *dir, time_t start_time)
{
  while (processor.is_inited() && maxQueuedItems < processed_files-affected_files)
    sleep_ms(100);
  for (const auto & entry : fs::directory_iterator(dir))
  {
    if (entry.is_directory())
      continue;
    std::string filename = entry.path().filename().string();
    if (filename.length()!=64)
    {
      printf("[E] <%s> is not a sha blob!\n", filename.c_str());
      continue;
    }
    if (start_time == 0 || get_file_mtime(entry.path().c_str()) > start_time)
    {
      ++processed_files;
      if (processor.is_inited())
        processor.emplace(std::move(filename));
      else
        process_blob(filename.c_str());
    }
  }
}

inline bool is_hex_symbol(unsigned char s)
{
  if (s >= '0' && s <= '9') return true;
  if (s >= 'a' && s <= 'f') return true;
  if (s >= 'A' && s <= 'F') return true;
  return false;
}

static void process_sha_directory(time_t start_time)
{
  std::string dirPath = blobs_dir_path(caddressed_fs::get_default_ctx());
  int dirI = 0;
  for (const auto & entry : fs::directory_iterator(dirPath.c_str()))
  {
    if (!entry.is_directory())
      continue;
    auto checkShaDirName = [](const std::string &dirName)
    { return (dirName.length() == 2) && is_hex_symbol(dirName[0]) && is_hex_symbol(dirName[1]); };
    if (!checkShaDirName(entry.path().filename().string()))
    {
      printf("[E] <%s>(%s) is not a sha directory!\n", entry.path().string().c_str(), entry.path().filename().string().c_str());
      continue;
    }
    printf("dir <%d/255> %s scheduled, %d\n", dirI++, entry.path().string().c_str(), (int)processed_files);
    for (const auto & entry2 : fs::directory_iterator(entry.path()))
    {
      if (!checkShaDirName(entry2.path().filename().string()))
      {
        printf("[E] <%s>(%s) is not a sha directory!\n", entry2.path().string().c_str(), entry2.path().filename().string().c_str());
        continue;
      }
      process_sha_files_directory(entry2.path().string().c_str(), start_time);
    }
  }
  fflush(stdout);
}

int main(int ac, const char* argv[])
{
  auto options = flags::flags{ac, argv};
  options.info("repack-blobs",
    "utility for repacking blobs to more compressed"
  );
  auto rootDir = options.arg("-root", "Root dir for CVS");
  init_temp_dir();
  auto tmpDir = options.arg_or("-tmp", "", "Tmp dir for blobs");
  auto threads = options.arg_as_or<int>("-j", 0, "concurrency level(threads to run)");
  auto days_changed = options.arg_as_or<int>("-last_days", 0, "Convert only blobs that were written in last N days");
  repack_unpacked = options.passed("-unpacked", "try to repack unpacked blobs also");

  bool help = options.passed("-h", "print help usage");
  if (help || !options.sane()) {
    if (!options.sane())
      printf("Missing required arguments:%s\n", options.print_missing().c_str());
    std::cout << options.usage();
    return help ? 0 : -1;
  }

  time_t start = 0;
  if (days_changed)
    start = time(NULL) - (days_changed*60*60*24);
  if (tmpDir.length() > 1)
    def_tmp_dir = tmpDir.c_str();
  set_root(caddressed_fs::get_default_ctx(), rootDir.c_str());
  if (tmpDir.length() > 1)
    caddressed_fs::set_temp_dir(tmpDir.c_str());
  if (threads>1)
  {
    printf("using %d threads\n", threads);
    processor.init(threads);
  }
  process_sha_directory(start);
  processor.finish();
  printf("processed %lld files, repacked %lld files, saved %lld bytes\n",
  (long long)affected_files, (long long)repacked_files, (long long)data_saved);
  return 0;
}
