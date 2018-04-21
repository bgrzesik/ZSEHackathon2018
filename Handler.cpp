//
// Created by Bartłomiej Grzesik on 12/04/2018.
//

#include "Handler.hpp"

#include <include/views/cef_browser_view.h>
#include <include/views/cef_window.h>

CefRefPtr<CefDisplayHandler> Handler::GetDisplayHandler() {
    return this;
}

CefRefPtr<CefLifeSpanHandler> Handler::GetLifeSpanHandler() {
    return this;
}

CefRefPtr<CefLoadHandler> Handler::GetLoadHandler() {
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
}

bool Handler::DoClose(CefRefPtr<CefBrowser> browser) {
    return true;
}

void Handler::OnBeforeClose(CefRefPtr<CefBrowser> browser) {
}

void Handler::OnLoadError(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefLoadHandler::ErrorCode errorCode,
                          const CefString &errorText, const CefString &failedUrl) {
}
