/////////////////////////////////////////////////////////////////////////////
// Name:        wx/dragimag.h
// Purpose:     wxDragImage base header
// Author:      Julian Smart
// Modified by:
// Created:
// Copyright:   (c) Julian Smart
// RCS-ID:      $Id: dragimag.h,v 1.1 2012/03/04 01:07:24 aliot Exp $
// Licence:     wxWindows Licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _WX_DRAGIMAG_H_BASE_
#define _WX_DRAGIMAG_H_BASE_

#if wxUSE_DRAGIMAGE

class WXDLLEXPORT wxRect;
class WXDLLEXPORT wxMemoryDC;
class WXDLLEXPORT wxDC;

#if defined(__WXMSW__)
#   if defined(__WXUNIVERSAL__)
#       include "wx/generic/dragimgg.h"
#       define wxDragImage wxGenericDragImage
#   else
#       include "wx/msw/dragimag.h"
#   endif

#elif defined(__WXMOTIF__)
#   include "wx/generic/dragimgg.h"
#   define wxDragImage wxGenericDragImage

#elif defined(__WXGTK__)
#   include "wx/generic/dragimgg.h"
#   define wxDragImage wxGenericDragImage

#elif defined(__WXX11__)
#   include "wx/generic/dragimgg.h"
#   define wxDragImage wxGenericDragImage

#elif defined(__WXMAC__)
#   include "wx/generic/dragimgg.h"
#   define wxDragImage wxGenericDragImage

#elif defined(__WXPM__)
#   include "wx/generic/dragimgg.h"
#   define wxDragImage wxGenericDragImage

#endif

#endif // wxUSE_DRAGIMAGE

#endif
    // _WX_DRAGIMAG_H_BASE_
