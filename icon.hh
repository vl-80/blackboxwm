//
// icon.hh for Blackbox - an X11 Window manager
// Copyright (c) 1997, 1998 by Brad Hughes, bhughes@arn.net
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 2 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//
// (See the included file COPYING / GPL-2.0)
//

#ifndef __blackbox_icon_hh
#define __blackbox_icon_hh

// forward declaration
class BlackboxIcon;

#include "blackbox.hh"
#include "workspace.hh"


class BlackboxIcon {
private:
  Bool focus;
  Display *display;
  GC iconGC;

  struct {
    char *name;
    Window client, window, subwindow;
    int x, y;
    unsigned int height;
  } icon;

  Blackbox *blackbox;
  WorkspaceManager *ws_manager;


protected:


public:
  BlackboxIcon(Blackbox *, Window);
  ~BlackboxIcon(void);

  void buttonPressEvent(XButtonEvent *);
  void buttonReleaseEvent(XButtonEvent *);
  void enterNotifyEvent(XCrossingEvent *);
  void leaveNotifyEvent(XCrossingEvent *);
  void exposeEvent(XExposeEvent *);
  void rereadLabel(void);
  void Reconfigure(void);

  Window iconWindow(void) { return icon.window; }
  unsigned int Height(void) { return icon.height; }
  void move(int x, int y) { icon.x = x; icon.y = y; }
};


#endif
