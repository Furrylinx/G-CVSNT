/////////////////////////////////////////////////////////////////////////////
// Name:        wx_cw_d.h
// Purpose:     wxWidgets definitions for CodeWarrior builds (Debug)
// Author:      Stefan Csomor
// Modified by:
// Created:     12/10/98
// RCS-ID:      $Id: wxshlba_cw_d.h,v 1.1 2012/03/04 01:07:27 aliot Exp $
// Copyright:   (c) Stefan Csomor
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _WX_CW__
#define _WX_CW__

#if __MWERKS__ >= 0x2400
#pragma old_argmatch on
#endif

#if __option(profile)
#error "profiling is not supported in debug versions"
#else
#ifdef __cplusplus
    #if __POWERPC__
        #include "wxshlba_PPC++_d.mch"
    #elif __INTEL__
        #include "wxshlba_x86++_d.mch"
    #elif __CFM68K__
        #include "wxshlba_cfm++_d.mch"
    #else
        #include "wxshlba_68k++_d.mch"
    #endif
#else
    #if __POWERPC__
        #include "wxshlba_PPC_d.mch"
    #elif __INTEL__
        #include "wxshlba_x86_d.mch"
    #elif __CFM68K__
        #include "wxshlba_cfm_d.mch"
    #else
        #include "wxshlba_68k_d.mch"
    #endif
#endif
#endif

#endif
    // _WX_CW__
