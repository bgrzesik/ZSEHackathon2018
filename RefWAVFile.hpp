//
// Created by Bartłomiej Grzesik on 21/04/2018.
//

#ifndef AUDIONOOB_REFWAVFILE_HPP
#define AUDIONOOB_REFWAVFILE_HPP


#include <include/cef_base.h>
#include "WAVHelper.hpp"

class RefWAVFile : public CefBaseRefCounted {
IMPLEMENT_REFCOUNTING(RefWAVFile);
public:
    WAVFile inner_;
};


#endif //AUDIONOOB_REFWAVFILE_HPP
