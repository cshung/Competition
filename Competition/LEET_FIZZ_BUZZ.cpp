#include "stdafx.h"

// https://leetcode.com/problems/fizz-buzz

#include "LEET_FIZZ_BUZZ.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_FIZZ_BUZZ
{
    class Solution
    {
    public:
        vector<string> fizzBuzz(int n)
        {
            vector<string> result;
            for (int i = 1; i <= n; i++)
            {
                if (i % 15 == 0)
                {
                    result.push_back("FizzBuzz");
                }
                else if (i % 5 == 0)
                {
                    result.push_back("Buzz");
                }
                else if (i % 3 == 0)
                {
                    result.push_back("Fizz");
                }
                else
                {
                    stringstream sout;
                    sout << i;
                    result.push_back(sout.str());
                }
            }
            return result;
        }
    };
};

using namespace _LEET_FIZZ_BUZZ;

int LEET_FIZZ_BUZZ()
{
    Solution solution;
    vector<string> result = solution.fizzBuzz(15);
    for (size_t i = 0; i < result.size(); i++)
    {
        cout << result[i] << endl;
    }
    return 0;
}