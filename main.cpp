#include <iostream>

#include "OSXHelper.h"
#include "App.hpp"

int main(int argc, char *argv[]) {
    CefEnableHighDPISupport();


    CefMainArgs main_args;
    main_args.argv = argv;
    main_args.argc = argc;

    CefRefPtr<App> app(new App(main_args));

    Platform platform;

    InitPlatform(&platform);

    CefSettings settings;
    settings.single_process = 1;
    settings.command_line_args_disabled = 1;
    settings.remote_debugging_port = 9090;

    int status;
    status = CefInitialize(main_args, settings, app.get(), nullptr);
    printf("CefInitialize = %d\n", status);
    CefRunMessageLoop();
    CefShutdown();
    std::cout << "Hello, World!" << std::endl;

    ReleasePlatform(&platform);
    exit(0);

    return 0;
}