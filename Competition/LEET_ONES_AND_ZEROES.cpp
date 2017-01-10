#include "stdafx.h"

// https://leetcode.com/problems/ones-and-zeroes/

#include "LEET_ONES_AND_ZEROES.h"
#include <map>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_ONES_AND_ZEROES
{
    int answer[2][101][101];

    class Solution
    {
    public:

        int findMaxForm(vector<string>& strs, int m, int n)
        {
            vector<int> o;
            vector<int> z;
            int num_items = strs.size();
            int num_ones = m;
            int num_zero = n;

            for (int w = 0; w < 2; w++)
            {
                for (int m = 0; m <= num_ones; m++)
                {
                    for (int n = 0; n <= num_zero; n++)
                    {
                        answer[w][m][n] = 0;
                    }
                }
            }

            o.resize(num_items);
            z.resize(num_items);
            for (int w = 0; w < num_items; w++)
            {
                o[w] = 0;
                z[w] = 0;
                for (int t = 0; t < strs[w].size(); t++)
                {
                    if (strs[w][t] == '0')
                    {
                        o[w]++;
                    }
                    else if (strs[w][t] == '1')
                    {
                        z[w]++;
                    }
                }
            }

            for (int w = 1; w <= num_items; w++)
            {
                for (int m = 0; m <= num_ones; m++)
                {
                    for (int n = 0; n <= num_zero; n++)
                    {
                        int a1 = answer[0][m][n];
                        if (m >= o[w - 1] && n >= z[w - 1])
                        {
                            int a2 = 1 + answer[0][m - o[w - 1]][n - z[w - 1]];
                            answer[1][m][n] = max(a1, a2);
                        }
                        else
                        {
                            answer[1][m][n] = a1;
                        }
                    }
                }
                for (int m = 0; m <= num_ones; m++)
                {
                    for (int n = 0; n <= num_zero; n++)
                    {
                        answer[0][m][n] = answer[1][m][n];
                    }
                }
            }

            return answer[1][num_ones][num_zero];
        }
    };
};

using namespace _LEET_ONES_AND_ZEROES;

int LEET_ONES_AND_ZEROES()
{
    Solution solution;
    // Input: Array = {"10", "0001", "111001", "1", "0"}, m = 5, n = 3

    vector<string> input;
    input.push_back("10");
    input.push_back("0001");
    input.push_back("111001");
    input.push_back("1");
    input.push_back("0");

    cout << solution.findMaxForm(input, 5, 3) << endl;
    
    return 0;
}