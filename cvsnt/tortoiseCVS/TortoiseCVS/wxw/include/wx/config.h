/////////////////////////////////////////////////////////////////////////////
// Name:        config.h
// Purpose:     wxConfig base header
// Author:      Julian Smart
// Modified by:
// Created:
// Copyright:   (c) Julian Smart
// RCS-ID:      $Id: config.h,v 1.1 2012/03/04 01:07:24 aliot Exp $
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _WX_CONFIG_H_BASE_
#define _WX_CONFIG_H_BASE_

#include "wx/confbase.h"

#if wxUSE_CONFIG

#if defined(__WXMSW__) && wxUSE_CONFIG_NATIVE
#    ifdef __WIN32__
#        include "wx/msw/regconf.h"
#    else
#        include "wx/msw/iniconf.h"
#    endif
#elif defined(__WXPALMOS__) && wxUSE_CONFIG_NATIVE
#    include "wx/palmos/prefconf.h"
#else
#    include "wx/fileconf.h"
#endif

#endif // wxUSE_CONFIG

#endif // _WX_CONFIG_H_BASE_
