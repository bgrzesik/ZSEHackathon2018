//
// Created by Bartłomiej Grzesik on 21/04/2018.
//

#include <iostream>
#include "JSAudioNoob.hpp"
#include "AudioNoob.hpp"


class RefAudioNoob : public CefBaseRefCounted {
IMPLEMENT_REFCOUNTING(RefAudioNoob);
public:
    AudioNoob inner_;
};

bool JSAudioNoob::Execute(const CefString &name, CefRefPtr<CefV8Value> object, const CefV8ValueList &arguments,
                          CefRefPtr<CefV8Value> &retval, CefString &exception)
{
    if (name == "new") {
        const CefRefPtr<CefV8Value> &ret = object->CreateObject(NULL, NULL);
        ret->SetUserData(new RefAudioNoob);
        ret->SetValue("play", CefV8Value::CreateFunction("play", new JSAudioNoob), V8_PROPERTY_ATTRIBUTE_NONE);

        retval = ret;
    } else if (name == "play") {
        RefAudioNoob *ran = dynamic_cast<RefAudioNoob *>(object->GetUserData().get());

        const CefRefPtr<CefV8Value> &file = arguments[0];
        if (file->IsString()) {
            ran->inner_.Play(file->GetStringValue().ToString());
        } else {
            std::cerr << "AudioNoob::Execute->play" << std::endl << std::flush;
        }
    } else {
        return false;
    }

    return true;
}
