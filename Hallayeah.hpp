//
// Created by Bartłomiej Grzesik on 21/04/2018.
//

#ifndef AUDIONOOB_HALLAYEAH_HPP
#define AUDIONOOB_HALLAYEAH_HPP


#include <include/cef_v8.h>

class Hallayeah : public CefV8Handler {
    IMPLEMENT_REFCOUNTING(Hallayeah);
public:
    Hallayeah();
    bool Execute(const CefString &name, CefRefPtr<CefV8Value> object, const CefV8ValueList &arguments,
                 CefRefPtr<CefV8Value> &retval, CefString &exception) override;
};


#endif //AUDIONOOB_HALLAYEAH_HPP
