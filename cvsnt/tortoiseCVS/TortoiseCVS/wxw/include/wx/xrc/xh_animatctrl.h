/////////////////////////////////////////////////////////////////////////////
// Name:        wx/xrc/xh_animatctrl.h
// Purpose:     XML resource handler for wxAnimationCtrl
// Author:      Francesco Montorsi
// Created:     2006-10-15
// RCS-ID:      $Id: xh_animatctrl.h,v 1.1 2012/03/04 01:07:54 aliot Exp $
// Copyright:   (c) 2006 Francesco Montorsi
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _WX_XH_ANIMATIONCTRL_H_
#define _WX_XH_ANIMATIONCTRL_H_

#include "wx/xrc/xmlres.h"

#if wxUSE_XRC && wxUSE_ANIMATIONCTRL

class WXDLLIMPEXP_XRC wxAnimationCtrlXmlHandler : public wxXmlResourceHandler
{
    DECLARE_DYNAMIC_CLASS(wxAnimationCtrlXmlHandler)

public:
    wxAnimationCtrlXmlHandler();
    virtual wxObject *DoCreateResource();
    virtual bool CanHandle(wxXmlNode *node);
};

#endif // wxUSE_XRC && wxUSE_ANIMATIONCTRL

#endif // _WX_XH_ANIMATIONCTRL_H_
