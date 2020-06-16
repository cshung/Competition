#include "stdafx.h"

// https://leetcode.com/problems/validate-ip-address/

#include "LEET_VALIDATE_IP_ADDRESS.h"
#include <map>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_VALIDATE_IP_ADDRESS
{
    class Solution
    {
    public:
        string validIPAddress(string IP)
        {
            size_t p = 0;
            bool validV4;
            bool validV6;
            number(p, IP, validV4, validV6);
            char c = next(p, IP);
            if (validV4 && c == '.')
            {
                for (int i = 0; i < 2; i++)
                {
                    number(p, IP, validV4, validV6);
                    if (!validV4)
                    {
                        return "Neither";
                    }
                    if (!dot(p, IP))
                    {
                        return "Neither";
                    }
                }
                number(p, IP, validV4, validV6);
                if (!validV4)
                {
                    return "Neither";
                }
                if (!eof(p, IP))
                {
                    return "Neither";
                }
                return "IPv4";
            }
            else if (validV6 && c == ':')
            {
                for (int i = 0; i < 6; i++)
                {
                    number(p, IP, validV4, validV6);
                    if (!validV6)
                    {
                        return "Neither";
                    }
                    if (!colon(p, IP))
                    {
                        return "Neither";
                    }
                }
                number(p, IP, validV4, validV6);
                if (!validV6)
                {
                    return "Neither";
                }
                if (!eof(p, IP))
                {
                    return "Neither";
                }
                return "IPv6";
            }
            else
            {
                return "Neither";
            }
        }
    private:
        void number(size_t& p, string& s, bool& validV4, bool& validV6)
        {
            bool leadingZero = p < s.length() && s[p] == '0';
            validV4 = true;
            int decimalValue = 0;
            int digitCount = 0;
            size_t L = min(p + 4, s.length());
            for (; p < L; p++)
            {
                bool isDecimalDigit = ('0' <= s[p] && s[p] <= '9');
                bool isHexadecimalDigit = ('A' <= s[p] && s[p] <= 'F') || ('a' <= s[p] && s[p] <= 'f');
                if (isDecimalDigit)
                {
                    decimalValue = (s[p] - '0') + decimalValue * 10;
                    digitCount++;
                }
                else if (isHexadecimalDigit)
                {
                    validV4 = false;
                    digitCount++;
                }
                else
                {
                    break;
                }
            }
            validV6 = digitCount > 0;
            if (validV4 && digitCount > 1 && leadingZero)
            {
                validV4 = false;
            }
            validV4 = validV4 && decimalValue < 256 && validV6;
        }

        char next(size_t& p, string& s)
        {
            if (p == s.length())
            {
                return '\0';
            }
            else
            {
                return s[p++];
            }
        }

        bool dot(size_t& p, string& s)
        {
            return (p < s.length()) && (s[p++] == '.');
        }

        bool colon(size_t& p, string& s)
        {
            return (p < s.length()) && (s[p++] == ':');
        }

        bool eof(size_t& p, string& s)
        {
            return p == s.length();
        }
    };
};

using namespace _LEET_VALIDATE_IP_ADDRESS;

int LEET_VALIDATE_IP_ADDRESS()
{
    Solution s;
    cout << s.validIPAddress("172.16.254.1") << endl;
    cout << s.validIPAddress("2001:0db8:85a3:0:0:8A2E:0370:7334") << endl;
    cout << s.validIPAddress("256.256.256.256") << endl;
    return 0;
}