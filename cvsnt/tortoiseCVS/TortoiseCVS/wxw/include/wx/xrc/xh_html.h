/////////////////////////////////////////////////////////////////////////////
// Name:        wx/xrc/xh_html.h
// Purpose:     XML resource handler for wxHtmlWindow
// Author:      Bob Mitchell
// Created:     2000/03/21
// RCS-ID:      $Id: xh_html.h,v 1.1 2012/03/04 01:07:54 aliot Exp $
// Copyright:   (c) 2000 Bob Mitchell and Verant Interactive
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _WX_XH_HTML_H_
#define _WX_XH_HTML_H_

#include "wx/xrc/xmlres.h"

#if wxUSE_XRC && wxUSE_HTML

class WXDLLIMPEXP_XRC wxHtmlWindowXmlHandler : public wxXmlResourceHandler
{
    DECLARE_DYNAMIC_CLASS(wxHtmlWindowXmlHandler)

public:
    wxHtmlWindowXmlHandler();
    virtual wxObject *DoCreateResource();
    virtual bool CanHandle(wxXmlNode *node);
};

#endif // wxUSE_XRC && wxUSE_HTML

#endif // _WX_XH_HTML_H_
