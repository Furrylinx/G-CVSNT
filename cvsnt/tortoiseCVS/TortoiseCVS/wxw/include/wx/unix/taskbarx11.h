/////////////////////////////////////////////////////////////////////////
// File:        wx/unix/taskbarx11.h
// Purpose:     Defines wxTaskBarIcon class for most common X11 desktops
// Author:      Vaclav Slavik
// Modified by:
// Created:     04/04/2003
// RCS-ID:      $Id: taskbarx11.h,v 1.1 2012/03/04 01:07:53 aliot Exp $
// Copyright:   (c) Vaclav Slavik, 2003
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////

#ifndef _TASKBAR_H_
#define _TASKBAR_H_

class WXDLLEXPORT wxIcon;
class WXDLLEXPORT wxFrame;
class WXDLLEXPORT wxWindow;

class WXDLLIMPEXP_ADV wxTaskBarIconArea;

class WXDLLIMPEXP_ADV wxTaskBarIcon: public wxTaskBarIconBase
{
public:
    wxTaskBarIcon();
    virtual ~wxTaskBarIcon();

    // Accessors:
    bool IsOk() const;
    bool IsIconInstalled() const;

    // Operations:
    bool SetIcon(const wxIcon& icon, const wxString& tooltip = wxEmptyString);
    bool RemoveIcon();
    bool PopupMenu(wxMenu *menu);

protected:
    wxTaskBarIconArea *m_iconWnd;

private:
    void OnDestroy(wxWindowDestroyEvent&);

    DECLARE_DYNAMIC_CLASS(wxTaskBarIcon)
};

#endif
    // _TASKBAR_H_
