//
// Created by Bartłomiej Grzesik on 11/04/2018.
//

#include <include/cef_app.h>

#ifndef CWEB_APP_HPP
#define CWEB_APP_HPP


class App : public CefApp, public CefBrowserProcessHandler {
    IMPLEMENT_REFCOUNTING(App);

public:
    App();

    CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() override;

    void OnContextInitialized() override;

};


#endif //CWEB_APP_HPP
