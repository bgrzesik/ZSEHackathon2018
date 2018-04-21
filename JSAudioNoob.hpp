//
// Created by Bartłomiej Grzesik on 21/04/2018.
//

#ifndef AUDIONOOB_JSAUDIONOOB_HPP
#define AUDIONOOB_JSAUDIONOOB_HPP


#include <include/cef_v8.h>

class JSAudioNoob : public CefV8Handler {
    IMPLEMENT_REFCOUNTING(JSAudioNoob);
public:
    bool Execute(const CefString &name, CefRefPtr<CefV8Value> object, const CefV8ValueList &arguments,
                 CefRefPtr<CefV8Value> &retval, CefString &exception) override;
};


#endif //AUDIONOOB_JSAUDIONOOB_HPP
