//
// Created by Bartłomiej Grzesik on 21/04/2018.
//

#include <iostream>
#include "JSAudioNoob.hpp"

bool JSAudioNoob::Execute(const CefString &name, CefRefPtr<CefV8Value> object, const CefV8ValueList &arguments,
                          CefRefPtr<CefV8Value> &retval, CefString &exception) {
    if (name == "new") {
        retval = CefV8Value::CreateObject(nullptr, nullptr);
        retval->SetValue("append", CefV8Value::CreateFunction("append", this), V8_PROPERTY_ATTRIBUTE_NONE);
        retval->SetValue("addTo", CefV8Value::CreateFunction("addTo", this), V8_PROPERTY_ATTRIBUTE_NONE);
        retval->SetValue("render", CefV8Value::CreateFunction("render", this), V8_PROPERTY_ATTRIBUTE_NONE);
    }

    return false;
}
