#include "stdafx.h"

// https://leetcode.com/problems/zigzag-conversion/

#include "LEET_ZIGZAG_CONVERSION.h"

#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

namespace _LEET_ZIGZAG_CONVERSION
{
    class Solution
    {
    public:
        string convert(string s, int numRows)
        {
            if (numRows == 1)
            {
                return s;
            }
            ostringstream os;
            bool moving_down = true;
            for (int current_row = 0; current_row < numRows; current_row++)
            {
                int row = 0, col = 0;
                for (unsigned int i = 0; i < s.length(); i++)
                {
                    if (row == current_row)
                    {
                        os << s[i];
                    }
                    if (moving_down)
                    {
                        if (row == numRows - 1)
                        {
                            moving_down = false;
                            row--;
                            col++;
                        }
                        else
                        {
                            row++;
                        }
                    }
                    else
                    {
                        if (row == 0)
                        {
                            moving_down = true;
                            row++;
                        }
                        else
                        {
                            row--;
                            col++;
                        }
                    }
                }
            }
            return os.str();
        }
    };
};

using namespace _LEET_ZIGZAG_CONVERSION;

int LEET_ZIGZAG_CONVERSION()
{
    Solution solution;
    string s = "ABCD";
    cout << s << endl;
    cout << solution.convert(s, 2) << endl;
    return 0;
}