#include "stdafx.h"

// https://leetcode.com/problems/count-and-say/

#include "LEET_COUNT_AND_SAY.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_COUNT_AND_SAY
{
    class Solution
    {
    public:
        string countAndSay(int n)
        {
            if (n < 1)
            {
                // Should be an error condition that is not clarified
                return "";
            }
            else if (n == 1)
            {
                return "1";
            }
            else
            {
                stringstream ss;
                string last = countAndSay(n - 1);
                for (unsigned int i = 0; i < last.length(); i++)
                {
                    int count = 1;
                    char value = last[i];
                    while (i < last.length())
                    {
                        if (last[i + 1] == value)
                        {
                            count++;
                            i++;
                        }
                        else
                        {
                            break;
                        }
                    }
                    
                    ss << count;
                    ss << value;
                }
                return ss.str();
            }
        }
    };
};

using namespace _LEET_COUNT_AND_SAY;

int LEET_COUNT_AND_SAY()
{
    Solution solution;
    for (int i = 1; i <= 10; i++)
    {
        cout << solution.countAndSay(i) << endl;
    }
    return 0;
}
