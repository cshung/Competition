#include "stdafx.h"

// https://leetcode.com/problems/integer-to-roman/

#include "LEET_INTEGER_TO_ROMAN.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_INTEGER_TO_ROMAN
{
    class Solution
    {
    private:
        void intToRoman(int num, ostringstream& os, char i, char v, char x)
        {
            if (num <= 3)
            {
                for (int c = 0; c < num; c++)
                {
                    os << i;
                }
            } else if (num == 4)
            {
                os << i;
                os << v;
            }
            else if (num <= 8)
            {
                os << v;
                intToRoman(num - 5, os, i, v, x);
            }
            else if (num == 9)
            {
                os << i;
                os << x;
            }

        }
    public:
        string intToRoman(int num)
        {
            ostringstream os;
            if (num < 10)
            {
                intToRoman(num, os, 'I', 'V', 'X');
            }
            else if (num < 100)
            {
                intToRoman((num / 10 ) % 10, os, 'X', 'L', 'C');
                intToRoman((num / 1  ) % 10, os, 'I', 'V', 'X');
            }
            else 
            {
                while (num >= 1000)
                {
                    os << 'M';
                    num -= 1000;
                }
                intToRoman((num / 100) % 10, os, 'C', 'D', 'M');
                intToRoman((num / 10 ) % 10, os, 'X', 'L', 'C');
                intToRoman((num / 1  ) % 10, os, 'I', 'V', 'X');
            }
            return os.str();
        }
    };

    string intToRoman(int num)
    {
        Solution s;
        return s.intToRoman(num);
    }
};

using namespace _LEET_INTEGER_TO_ROMAN;

int LEET_INTEGER_TO_ROMAN()
{
    Solution s;
    for (int i = 1; i <= 3999; i++)
    {
        cout << i << "\t" << s.intToRoman(i) << endl;
    }
    return 0;
}