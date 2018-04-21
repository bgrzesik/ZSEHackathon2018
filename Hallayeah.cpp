//
// Created by Bartłomiej Grzesik on 21/04/2018.
//

#include <iostream>
#include "Hallayeah.hpp"

Hallayeah::Hallayeah() {

}

bool Hallayeah::Execute(const CefString &name, CefRefPtr<CefV8Value> object, const CefV8ValueList &arguments,
                        CefRefPtr<CefV8Value> &retval, CefString &exception) {

    std::cout << "WEwef" << std::endl;
    return false;
}

