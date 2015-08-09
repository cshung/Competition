#include "stdafx.h"

// https://leetcode.com/problems/pascals-triangle-ii/

#include "LEET_PASCALS_TRIANGLE_II.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_PASCALS_TRIANGLE_II
{
    class Solution
    {
    public:
        vector<int> getRow(int rowIndex)
        {
            vector<int> result;
            result.resize(rowIndex + 1);
            result[0] = 1;
            for (int i = 1; i <= rowIndex; i++)
            {
                long long temp = result[i - 1];
                temp = temp * (rowIndex + 1 - i) / i;
                result[i] = (int)temp;
            }
            return result;
        }
    };
};

using namespace _LEET_PASCALS_TRIANGLE_II;

int LEET_PASCALS_TRIANGLE_II()
{
    Solution solution;
    for (int i = 1; i <= 10; i++)
    {
        vector<int> result = solution.getRow(i);
        for (unsigned int j = 0; j < result.size(); j++)
        {
            cout << result[j] << " ";
        }
        cout << endl;
    }
    return 0;
}