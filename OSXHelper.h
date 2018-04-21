//
// Created by Bartłomiej Grzesik on 12/04/2018.
//

#ifndef CWEB_OSXHELPER_H
#define CWEB_OSXHELPER_H

struct NSView;
struct NSWindow;

extern "C" NSWindow* CreateView();
extern "C" NSView* GetContentView(NSWindow *window);

#endif //CWEB_OSXHELPER_H
