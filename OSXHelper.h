//
// Created by Bartłomiej Grzesik on 12/04/2018.
//

#ifndef CWEB_OSXHELPER_H
#define CWEB_OSXHELPER_H

struct NSView;
struct NSWindow;
struct NSObject;
struct NSAutoreleasePool;

struct Platform {
    NSObject *delegate;
    NSAutoreleasePool *autopool;
};

extern "C" void InitPlatform(Platform *platform);
extern "C" NSWindow* CreateView();
extern "C" NSView* GetContentView(NSWindow *window);
extern "C" void ReleaseView(NSWindow *window);
extern "C" void ReleasePlatform(Platform *platform);

#endif //CWEB_OSXHELPER_H
