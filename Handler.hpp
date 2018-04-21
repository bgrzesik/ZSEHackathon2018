//
// Created by Bartłomiej Grzesik on 12/04/2018.
//

#ifndef CWEB_HANDLER_HPP
#define CWEB_HANDLER_HPP

#include <include/cef_client.h>


class Handler : public CefClient,
                public CefDisplayHandler,
                public CefLifeSpanHandler,
                public CefRequestHandler {
    IMPLEMENT_REFCOUNTING(Handler);

public:
    static CefRefPtr<Handler> GetHandler();
    CefRefPtr<CefRequestHandler> GetRequestHandler() override;
    CefRefPtr<CefDisplayHandler> GetDisplayHandler() override;
    CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override;


    bool OnConsoleMessage(CefRefPtr<CefBrowser> browser, cef_log_severity_t level, const CefString &message,
                          const CefString &source, int line) override;

    void OnTitleChange(CefRefPtr<CefBrowser> browser, const CefString &title) override;

    void OnAfterCreated(CefRefPtr<CefBrowser> browser) override;

    bool DoClose(CefRefPtr<CefBrowser> browser) override;

    void OnBeforeClose(CefRefPtr<CefBrowser> browser) override;

    void CloseAll();
private:
    Handler();
    std::vector<CefRefPtr<CefBrowser>> browsers_;
};


#endif //CWEB_HANDLER_HPP
