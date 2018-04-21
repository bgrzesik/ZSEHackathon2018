
#import <CoreFoundation/CoreFoundation.h>
#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>
#import <objc/NSObject.h>

extern "C" NSWindow* CreateView() {
    NSApplication *app = [NSApplication sharedApplication];
    [app activateIgnoringOtherApps: YES];

    auto rect = NSRect {100, 100, 800, 800};
    NSWindow *window = [[NSWindow alloc] initWithContentRect:rect
                                                   styleMask:NSBorderlessWindowMask
                                                     backing:NSBackingStoreBuffered
                                                       defer:NO];

    [window makeKeyAndOrderFront: nil];


//    NSRect rect = { 100, 100, 800, 800 };
//    [window release];
    return window;
}

extern "C" NSView* GetContentView(NSWindow *window) {
    return [window contentView];
}
