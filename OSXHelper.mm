
#import <CoreFoundation/CoreFoundation.h>
#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>
#import <objc/NSObject.h>
#import <include/cef_application_mac.h>
#include "Handler.hpp"
//#import "OSXHelper.h"

struct Platform {
    NSObject *delegate;
    NSAutoreleasePool *autopool;
};


@interface AppDelegate : NSObject<NSApplicationDelegate>
- (void)createApplication:(id)object;
- (void)tryToTerminateApplication:(NSApplication*)app;
@end

@implementation AppDelegate

- (void)createApplication:(id)object {
    [NSApplication sharedApplication] ;
    [[NSBundle mainBundle] loadNibNamed:@"MainMa"
                                  owner:NSApp
                        topLevelObjects:nil];
}

- (void)tryToTerminateApplication:(NSApplication *)app {
    printf("qwdweiof");

}

- (NSApplicationTerminateReply)applicationShouldTerminate: (NSApplication*)sender {
    return NSTerminateNow;
}
@end

@interface Application : NSApplication <CefAppProtocol> {

@private
    BOOL handlingEvents_;
}
@end

@implementation Application

- (BOOL)isHandlingSendEvent {
    return self->handlingEvents_;
}

- (void)setHandlingSendEvent:(BOOL)handlingSendEvent {
    self->handlingEvents_ = handlingSendEvent;
}

- (void)sendEvent:(NSEvent *)event {
    CefScopedSendingEvent sendingEvent;
    [super sendEvent:event];
}

- (void)terminate:(nullable id)sender {
    auto delegate = static_cast<AppDelegate *>([NSApp delegate]);
    [delegate tryToTerminateApplication:self];
    [super terminate:sender];
}

@end

@interface WindowDelegate : NSObject<NSWindowDelegate> {
}
@end

@implementation WindowDelegate
- (void)windowWillClose:(NSNotification *)notification {
    Handler *handler = Handler::GetHandler();

    printf("%p\n", handler);
    handler->CloseAll();
}
@end


extern "C" NSWindow* CreateView() {
    Application *app = [Application sharedApplication];
//    NSApplication *app = [NSApplication sharedApplication];

    [app activateIgnoringOtherApps: YES];

    auto rect = NSRect {100, 100, 800, 800};
    NSWindow *window = [[NSWindow alloc] initWithContentRect:rect
                                                   styleMask:NSWindowStyleMaskClosable | NSWindowStyleMaskResizable | NSWindowStyleMaskTitled
                                                     backing:NSBackingStoreBuffered
                                                       defer:NO];
    window.delegate = [[WindowDelegate alloc] init];
    [window setOpaque: NO];
    [window makeKeyAndOrderFront: nil];
    return window;
}

extern "C" NSView* GetContentView(NSWindow *window) {
    return [window contentView];
}

extern "C" void ReleaseView(NSWindow  *window) {
    [window release];
}

extern "C" void InitPlatform(Platform *platform) {
    platform->autopool = [[NSAutoreleasePool alloc] init];
    [Application sharedApplication];

    AppDelegate *delegate = [[AppDelegate alloc] init];
    [delegate performSelectorOnMainThread: @selector(createApplication:)
                               withObject: nil
                            waitUntilDone: NO];

    platform->delegate = delegate;

}


extern "C" void ReleasePlatform(Platform *platform) {
    [platform->delegate release];
    [platform->autopool release];
}
