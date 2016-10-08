#include "stdafx.h"

// https://leetcode.com/problems/remove-k-digits/

#include "LEET_REMOVE_K_DIGITS.h"
#include <stack>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_REMOVE_K_DIGITS
{
    class Solution
    {
    public:
        string removeKdigits(string num, int k)
        {
            if (k >= num.size())
            {
                return "0";
            }
            stack<int> increasing_indice;
            int i = 0;
            while (k > 0)
            {
                while (true)
                {
                    if (increasing_indice.size() == 0)
                    {
                        increasing_indice.push(i++);
                    }
                    else if (num[i] >= num[increasing_indice.top()])
                    {
                        increasing_indice.push(i++);
                    }
                    else
                    {
                        break;
                    }
                }
                int index_to_remove = increasing_indice.top();
                num[index_to_remove] = ' ';
                increasing_indice.pop();
                k--;
            }

            bool leading = true;
            char* resultBuffer = new char[num.size() - k + 1];
            size_t j = 0;
            for (size_t i = 0; i < num.size(); i++)
            {
                if (num[i] != ' ')
                {
                    if (!leading || num[i] != '0')
                    {
                        resultBuffer[j++] = num[i];
                        leading = false;
                    }
                }
            }

            if (leading)
            {
                resultBuffer[j++] = '0';
                leading = false;
            }

            resultBuffer[j++] = '\0';
            string resultString(resultBuffer);
            delete[] resultBuffer;
            return resultString;
        }
    };
};

using namespace _LEET_REMOVE_K_DIGITS;

int LEET_REMOVE_K_DIGITS()
{
    Solution solution;
    cout << solution.removeKdigits("1432219", 3) << endl;
    cout << solution.removeKdigits("10200", 1) << endl;
    cout << solution.removeKdigits("10", 2) << endl;
    return 0;
}