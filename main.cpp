#include <iostream>

#include "App.hpp"

int main(int argc, char *argv[]) {
    CefEnableHighDPISupport();

    CefRefPtr<App> app(new App);

    CefMainArgs main_args;
    main_args.argv = argv;
    main_args.argc = argc;

    CefSettings settings;

    settings.remote_debugging_port = 9090;

    int status;
    status = CefInitialize(main_args, settings, app.get(), nullptr);
    printf("CefInitialize = %d\n", status);
    CefRunMessageLoop();
    CefShutdown();
    std::cout << "Hello, World!" << std::endl;
    return 0;
}