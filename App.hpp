//
// Created by Bartłomiej Grzesik on 11/04/2018.
//

#include <include/cef_app.h>

#ifndef CWEB_APP_HPP
#define CWEB_APP_HPP


class App : public CefApp,
            public CefBrowserProcessHandler,
            public CefRenderProcessHandler {
    IMPLEMENT_REFCOUNTING(App)


public:
    App(CefMainArgs &args);

    void OnRegisterCustomSchemes(CefRawPtr<CefSchemeRegistrar> registrar) override;

    CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() override;

    CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() override;

    void OnContextInitialized() override;

    void OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame,
                          CefRefPtr<CefV8Context> context) override;


private:
    CefMainArgs &args_;

};


#endif //CWEB_APP_HPP
