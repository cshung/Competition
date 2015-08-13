#include "stdafx.h"

// https://leetcode.com/problems/happy-number/

#include "LEET_HAPPY_NUMBER.h"
#include <set>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_HAPPY_NUMBER
{
    class Solution
    {
    public:
        bool isHappy(int n)
        {
            set<int> known;
            known.insert(n);
            while (true)
            {
                int sum = 0;
                while (n >= 10)
                {
                    sum = sum + (n % 10) * (n % 10);
                    n = n / 10;
                }
                sum = sum + (n % 10) * (n % 10);
                if (sum == 1)
                {
                    return true;
                }
                else
                {
                    if (known.find(sum) == known.end())
                    {
                        known.insert(sum);
                        n = sum;
                    }
                    else
                    {
                        return false;
                    }
                }
            }
        }
    };
};

using namespace _LEET_HAPPY_NUMBER;

int LEET_HAPPY_NUMBER()
{
    Solution solution;
    cout << !solution.isHappy(10086) << endl;
    cout << solution.isHappy(19) << endl;
    return 0;
}