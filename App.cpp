//
// Created by Bartłomiej Grzesik on 11/04/2018.
//

#include "App.hpp"
#include "Handler.hpp"
#include "OSXHelper.h"
#include "Hallayeah.hpp"

#include <iostream>
#include <include/wrapper/cef_helpers.h>
#include <include/views/cef_window_delegate.h>
#include <include/views/cef_browser_view.h>
#include <include/views/cef_window.h>


CefRefPtr<CefBrowserProcessHandler> App::GetBrowserProcessHandler() {
    return this;
}

void App::OnContextInitialized() {
    CEF_REQUIRE_UI_THREAD();


    NSWindow *window = CreateView();
    CefBrowserSettings settings;
    CefWindowInfo window_info;
    window_info.x = 100;
    window_info.y = 100;
    window_info.width = 800;
    window_info.height = 800;
    window_info.SetAsChild(GetContentView(window), 0, 0, 800, 800);

    std::string file = "file://" + std::string(args_.argv[0]) + "/../../Resources/index.html";
    std::cout << file << std::endl << std::flush;
    CefBrowserHost::CreateBrowser(window_info, Handler::GetHandler(), file, settings, nullptr);
}

void App::OnRegisterCustomSchemes(CefRawPtr<CefSchemeRegistrar> registrar) {
    registrar->AddCustomScheme("res", true, true, false, true, false, false);
}

App::App(CefMainArgs &args): args_(args) {

}

CefRefPtr<CefRenderProcessHandler> App::GetRenderProcessHandler() {
    return this;
}

void App::OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context) {
    const CefRefPtr<CefV8Value> &global = context->GetGlobal();
    const CefRefPtr<CefV8Value> &hallayeah = global->CreateFunction("hallayeah", new Hallayeah());
    global->SetValue("hallayeah", hallayeah, V8_PROPERTY_ATTRIBUTE_NONE);
}


