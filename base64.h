#ifndef BASE64_H_INCLUDED
#define BASE64_H_INCLUDED

#include <vector>
#include <string>


namespace Base64
{


    //Simple function to encode given string in base64

    const std::string &BASE64_CODES = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    std::string base64_encode(const std::string &s)
    {
        std::string ret;
        int val = 0;
        int bits = -6;
        const unsigned int b63 = 0x3F;

        for(const auto &c : s)
        {
            val = (val << 8) + c;
            bits += 8;

            while(bits >= 0)
            {
                ret.push_back(BASE64_CODES[ ( val >> bits) & b63 ] );
                bits -=6;
            }
        }

        if(bits > -6)
        {
            ret.push_back(BASE64_CODES[ ( (val << 8) >> (bits + 8) ) &b63]);
        }

        while(ret.size() % 4)
        {
            ret.push_back('=');
        }

        return ret;
    }




    //modified function for encryption

    const std::string &s1 = "abcdefg";
    const std::string &s2 = "54321";
    const std::string &s3 = "!@#$%";

    std::string base64_encrypt(std::string s)
    {
        s += s1 + s2 + s3;
        s = base64_encode(s);
        s.insert(1,"1");
        s += s2;
        s = base64_encode(s);
        s += s1 + s2;
        s = base64_encode(s);
        s.insert(2, "2");
        return s;
    }

}
#endif // BASE64_H_INCLUDED
