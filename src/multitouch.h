// $Id$
// Description: Multitouch emulation handler
// (C) Cyberpad Technologies 2011
#ifndef MULTITOUCH_H_
#define MULTITOUCH_H_

#include <string>
#include <stack>

#include "OS.h"

class Multitouch
{
    // static
private:
    static Multitouch* sInstance;

    #ifdef OS_WINDOWS
        static const std::string sLibraryName;
    #endif

public:
    static Multitouch& Get();

    // non-static
private:
    Multitouch();
    void Init();

    #ifdef OS_WINDOWS
        std::stack<TOUCHINPUT> mPendingTouch;
    #endif

public:
    bool Supported() const;
    unsigned int MaximumTouch() const;

    void Touch();
    //void

};

#endif // MULTITOUCH_H_

