//
// Created by Bartłomiej Grzesik on 21/04/2018.
//

#include "JSWAVFile.hpp"
#include "RefWAVFile.hpp"

bool JSWAVFile::Execute(const CefString &name, CefRefPtr<CefV8Value> object, const CefV8ValueList &arguments,
                        CefRefPtr<CefV8Value> &retval, CefString &exception) {

    RefWAVFile *rwf = dynamic_cast<RefWAVFile *>(object->GetUserData().get());

    CefRefPtr<CefV8Value> intarg = arguments[0];
    int arg = intarg->GetIntValue();

    if (name == "SetTone") {
        rwf->inner_.SetTone(arg);
    } else if (name == "SetSpeed") {
        rwf->inner_.SetSpeed(arg);
    } else {
        return true;
    }

    return true;
}
