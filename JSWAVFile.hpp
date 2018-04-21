//
// Created by Bartłomiej Grzesik on 21/04/2018.
//

#ifndef AUDIONOOB_JSWAVFILE_HPP
#define AUDIONOOB_JSWAVFILE_HPP


#include <include/cef_v8.h>

class JSWAVFile : public CefV8Handler {
    IMPLEMENT_REFCOUNTING(JSWAVFile);
public:
    bool Execute(const CefString &name, CefRefPtr<CefV8Value> object, const CefV8ValueList &arguments,
                 CefRefPtr<CefV8Value> &retval, CefString &exception) override;
};


#endif //AUDIONOOB_JSWAVFILE_HPP
