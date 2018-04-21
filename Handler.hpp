//
// Created by Bartłomiej Grzesik on 12/04/2018.
//

#ifndef CWEB_HANDLER_HPP
#define CWEB_HANDLER_HPP

#include <include/cef_client.h>


class Handler : public CefClient,
                public CefDisplayHandler,
                public CefLifeSpanHandler,
                public CefLoadHandler {
    IMPLEMENT_REFCOUNTING(Handler);

public:
    static CefRefPtr<Handler> GetHandler();

    CefRefPtr<CefDisplayHandler> GetDisplayHandler() override;
    CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override;
    CefRefPtr<CefLoadHandler> GetLoadHandler() override;

    void OnTitleChange(CefRefPtr<CefBrowser> browser, const CefString &title) override;

    void OnAfterCreated(CefRefPtr<CefBrowser> browser) override;

    bool DoClose(CefRefPtr<CefBrowser> browser) override;

    void OnBeforeClose(CefRefPtr<CefBrowser> browser) override;

    void OnLoadError(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, ErrorCode errorCode,
                     const CefString &errorText, const CefString &failedUrl) override;
};


#endif //CWEB_HANDLER_HPP
