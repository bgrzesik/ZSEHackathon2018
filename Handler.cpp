//
// Created by Bartłomiej Grzesik on 12/04/2018.
//

#include "Handler.hpp"
#include "Hallayeah.hpp"

#include <include/views/cef_browser_view.h>
#include <include/views/cef_window.h>
#include <include/cef_app.h>
#include <iostream>

Handler::Handler() {
}

CefRefPtr<CefDisplayHandler> Handler::GetDisplayHandler() {
    return this;
}

CefRefPtr<CefLifeSpanHandler> Handler::GetLifeSpanHandler() {
    return this;
}

CefRefPtr<CefRequestHandler> Handler::GetRequestHandler() {
    return this;
}


void Handler::OnTitleChange(CefRefPtr<CefBrowser> browser, const CefString &title) {
    CefRefPtr<CefBrowserView> browser_view = CefBrowserView::GetForBrowser(browser);
    if (browser_view) {
        CefRefPtr<CefWindow> window = browser_view->GetWindow();
        if (window) {
            window->SetTitle(title);
        }
    }
}

CefRefPtr<Handler> Handler::GetHandler() {
    static CefRefPtr<Handler> handler;
    if (!handler) {
        handler = new Handler;
    }
    return handler;
}

void Handler::OnAfterCreated(CefRefPtr<CefBrowser> browser) {
    this->browsers_.push_back(browser);
    browser->GetMainFrame()->ExecuteJavaScript("console.log('fwewfwef');", "", 0);
}

bool Handler::DoClose(CefRefPtr<CefBrowser> browser) {
    std::cout << "DoClose" << std::endl << std::flush;
    if (browsers_.size() == 1) {
        CefQuitMessageLoop();
    }
    return true;
}

void Handler::OnBeforeClose(CefRefPtr<CefBrowser> browser) {
    std::cout << "OnBeforeClose" << std::endl << std::flush;
    for (auto i = browsers_.begin(); i != browsers_.end(); i++) {
        if ((*i)->IsSame(browser)) {
            browsers_.erase(i);
            return;
        }
    }
}

void Handler::CloseAll() {
    for (auto &browser : browsers_) {
        browser->GetHost()->CloseBrowser(false);
    }
}

bool Handler::OnConsoleMessage(CefRefPtr<CefBrowser> browser, cef_log_severity_t level, const CefString &message,
                               const CefString &source, int line) {
    std::cout << "Console: " << message.ToString() << std::endl << std::flush;
    return CefDisplayHandler::OnConsoleMessage(browser, level, message, source, line);
}



