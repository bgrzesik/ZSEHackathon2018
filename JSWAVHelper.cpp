//
// Created by Bartłomiej Grzesik on 21/04/2018.
//

#include "JSWAVHelper.hpp"
#include "WAVHelper.hpp"
#include "RefWAVFile.hpp"

class RefWAVHelper : public CefBaseRefCounted
{
    IMPLEMENT_REFCOUNTING(RefWAVHelper);
public:
    WAVHelper inner_;
};


bool JSWAVHelper::Execute(const CefString &name, CefRefPtr<CefV8Value> object, const CefV8ValueList &arguments,
                          CefRefPtr<CefV8Value> &retval, CefString &exception) {
    if (name == "new") {
        const CefRefPtr<CefV8Value> &wav = object->CreateObject(NULL, NULL);
        wav->SetUserData(new RefWAVHelper);
        wav->SetValue("Append", object->CreateFunction("Append", new JSWAVHelper), V8_PROPERTY_ATTRIBUTE_NONE);
        wav->SetValue("AddAt", object->CreateFunction("AddAt", new JSWAVHelper), V8_PROPERTY_ATTRIBUTE_NONE);
        wav->SetValue("Render", object->CreateFunction("Render", new JSWAVHelper), V8_PROPERTY_ATTRIBUTE_NONE);

        retval = wav;
    } else {
        RefWAVHelper *rwh = dynamic_cast<RefWAVHelper *>(object->GetUserData().get());

        if (name == "Load") {
            CefRefPtr<CefV8Value> file = arguments[0];
            CefRefPtr<RefWAVFile> rwf = new RefWAVFile;
            rwf->inner_ = rwh->inner_.Load(file->GetStringValue().ToString());

            const CefRefPtr<CefV8Value> &wav = object->CreateObject(NULL, NULL);
            wav->SetUserData(rwf);
            wav->SetValue("SetTone", object->CreateFunction("SetTone", new JSWAVHelper), V8_PROPERTY_ATTRIBUTE_NONE);
            wav->SetValue("SetSpeed", object->CreateFunction("SetSpeed", new JSWAVHelper), V8_PROPERTY_ATTRIBUTE_NONE);
            retval = wav;

        } else if (name == "Append") {
            CefRefPtr<CefV8Value> wavjs = arguments[0];
            RefWAVFile *rwf = dynamic_cast<RefWAVFile *>(wavjs->GetUserData().get());
            if (arguments.size() == 2) {
                CefRefPtr<CefV8Value> lenjs = arguments[1];
                rwh->inner_.Append(rwf->inner_, static_cast<float>(lenjs->GetDoubleValue()));
            } else {
                rwh->inner_.Append(rwf->inner_);
            }
        } else if (name == "AddAt") {
            CefRefPtr<CefV8Value> wavjs = arguments[0];
            RefWAVFile *rwf = dynamic_cast<RefWAVFile *>(wavjs->GetUserData().get());
            if (arguments.size() == 2) {
                CefRefPtr<CefV8Value> offset = arguments[1];
                rwh->inner_.AddAt(rwf->inner_, static_cast<float>(offset->GetDoubleValue()));
            } else {
                CefRefPtr<CefV8Value> offset = arguments[1];
                CefRefPtr<CefV8Value> lenght = arguments[1];
                rwh->inner_.AddAt(rwf->inner_, static_cast<float>(offset->GetDoubleValue()),
                                  static_cast<float>(lenght->GetDoubleValue()));
            }
        } else if (name == "Render") {
            CefRefPtr<CefV8Value> output = arguments[0];
            rwh->inner_.Render(output->GetStringValue().ToString());
        } else {
            return false;
        }
    }
    return true;
}
