#include "stdafx.h"

// https://leetcode.com/problems/lexicographical-numbers/

#include "LEET_LEXICOGRAPHICAL_NUMBERS.h"
#include <stack>
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_LEXICOGRAPHICAL_NUMBERS
{
    class Solution
    {
    public:
        vector<int> lexicalOrder(int n)
        {
            vector<int> result;
            result.resize(n);
            int level = 0;
            int c = n;
            while (c > 0)
            {
                level++;
                c = c / 10;
            }

            int current = 1;
            int currentLevel = 1;

            for (int i = 0; i < n; i++)
            {
                result[i] = current;
                if ((currentLevel < level) && (current * 10 <= n))
                {
                    // We always try to increase the number of digit
                    current = current * 10;
                    currentLevel++;
                }
                else
                {
                    if (current == n)
                    {
                        // Take all the digits but the last one, increase by 1, and then add a zero
                        // e.g. 134 -> 13 -> 14 -> 140
                        current = ((current / 10) + 1) * 10;
                    }
                    else
                    {
                        current++;
                    }
                    while (current % 10 == 0)
                    {
                        // Whenever possible, remove trailing zero
                        currentLevel--;
                        current /= 10;
                    }
                }
            }
            return result;
        }
    };
};

using namespace _LEET_LEXICOGRAPHICAL_NUMBERS;

int LEET_LEXICOGRAPHICAL_NUMBERS()
{
    Solution solution;
    vector<int> r = solution.lexicalOrder(234);
    for (int i = 0; i < r.size(); i++)
    {
        cout << r[i] << endl;
    }
    return 0;
}