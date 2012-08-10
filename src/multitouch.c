
/*
#include "Multitouch.h"

Multitouch* Multitouch::sInstance = NULL;
std::string Multitouch::sLibraryName = "User32.dll";

Multitouch& Multitouch::get()
{
    if (sInstance == NULL)
    {
        sInstance = new Mouse();
    }
    return *sInstance;
}

Multitouch::Multitouch()
{
    Init();
}

Multitouch::~Multitouch()
{

}

void Multitouch::Init()
{
    #ifdef OS_WINDOWS
        LoadLibrary(sLibraryName);
    #endif
}

bool Multitouch::Supported() const
{
    #ifdef OS_WINDOWS

    #endif
}

unsigned int Multitouch::MaximumTouch() const
{
    #ifdef OS_WINDOWS

    #endif
}

void Multitouch::Touch(unsigned int id, int x, int y)
{
    // TODO scale x and y to server screen coordinates
    TOUCHINPUT input;
    input.x = x;
    input.y = y;
    input.hSource = 0; // Don't know what to do if the input doesn't have a corresponding device... hopefully 0 works
    input.dwID = id;
    input.dwFlags = TOUCHEVENTF_DOWN;
    input.dwMask = 0; // Could potentially send touch area
    input.dwTimeinput.dwExtraInfo = ULONG_PTR(NULL);
    input.cxContact = 0;
    input.cyContact = 0;

    SendMessage
}
*/
