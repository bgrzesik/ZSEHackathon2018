//
// Created by Bartłomiej Grzesik on 11/04/2018.
//

#include "App.hpp"
#include "Handler.hpp"
#include "OSXHelper.h"

#include <iostream>
#include <include/wrapper/cef_helpers.h>
#include <include/views/cef_window_delegate.h>
#include <include/views/cef_browser_view.h>
#include <include/views/cef_window.h>


class WindowDelegate : public CefWindowDelegate {
    IMPLEMENT_REFCOUNTING(WindowDelegate);
    DISALLOW_COPY_AND_ASSIGN(WindowDelegate);
public:
    explicit WindowDelegate(CefRefPtr<CefBrowserView> browser_view): browser_view_(browser_view) {
    }

    void OnWindowCreated(CefRefPtr<CefWindow> window) override {
        window->AddChildView(this->browser_view_);
        window->Show();
        window->RequestFocus();
    }

    bool IsFrameless(CefRefPtr<CefWindow> window) override {
        return true;
    }

    void OnWindowDestroyed(CefRefPtr<CefWindow> window) override {
        browser_view_ = nullptr;
        CefShutdown();
    }

    bool CanClose(CefRefPtr<CefWindow> window) override {
        CefRefPtr<CefBrowser> browser = browser_view_->GetBrowser();
        if (browser) {
            browser->GetHost()->TryCloseBrowser();
        }
        return true;
    }

private:
    CefRefPtr<CefBrowserView> browser_view_;
};


App::App() {
}

CefRefPtr<CefBrowserProcessHandler> App::GetBrowserProcessHandler() {
    return this;
}

void App::OnContextInitialized() {
    CEF_REQUIRE_UI_THREAD();

    NSWindow *window = CreateView();

    CefBrowserSettings settings;
    CefWindowInfo window_info;
    window_info.SetAsChild(GetContentView(window), 0, 0, 800, 800);

    CefBrowserHost::CreateBrowser(window_info, Handler::GetHandler(), "http://motherfuckingwebsite.com/", settings, nullptr);
}


