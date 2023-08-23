#ifndef HELPER_H_INCLUDED
#define HELPER_H_INCLUDED

#include <string>
#include <ctime>
#include <sstream>
#include <fstream>


namespace Helper
{


    //converts different types to string
    template <class T>
    std::string ToString(const T &e)
    {
        std::ostringstream s;
        s << e;
        return s.str();
    }



    struct DateTime
    {

        int D, m, y, H, M, S;

        DateTime()
        {
            time_t ms;

            time(&ms);

            struct tm *info = localtime(&ms);

            D=info->tm_mday; //day
            m=info->tm_mon +1; //month +1 since counting starts at 0
            y=1900 + info->tm_year; // year
            M=info->tm_min; //minutes
            H=info->tm_hour; //hours
            S=info->tm_sec; //seconds
        }

        std::string GetDateString() const
        {
            //returns Date in the DD.mm.YYYY format
            return std::string(D < 10 ? "0" : "") + ToString(D) + std::string(M < 10 ? ".0" : ".") + ToString(m) + "." + ToString(y);
        }

        std::string GetTimeString() const
        {
            //returns time in the following format HH_MM_SS
            return std::string(H < 10 ? "0" : "") + ToString(H) + "_" +
                   std::string(M < 10 ? "0" : "") + ToString(M) + "_" +
                   std::string(S < 10 ? "0" : "") + ToString(S);
        }

        std::string GetDateTimeString() const
        {
            return GetDateString() + " " + GetTimeString();
        }
    };
}


#endif // HELPER_H_INCLUDED
