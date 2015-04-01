#include "stdafx.h"

// https://leetcode.com/problems/excel-sheet-column-number/

#include "LEET_EXCEL_SHEET_COLUMN_NUMBER.h"
#include <map>
#include <iostream>
#include <vector>

using namespace std;

namespace _LEET_EXCEL_SHEET_COLUMN_NUMBER
{
    class Solution
    {
    public:
        int titleToNumber(string s)
        {
            int result = 0;
            int digitFactor = 1;
            for (int i = s.length() - 1; i >= 0; i--)
            {
                result += (s[i] - 'A' + 1) * digitFactor;
                digitFactor *= 26;
            }

            return result;
        }
    };
};

using namespace _LEET_EXCEL_SHEET_COLUMN_NUMBER;

int LEET_EXCEL_SHEET_COLUMN_NUMBER()
{
    Solution solution;
    cout << solution.titleToNumber("A") << endl;
    cout << solution.titleToNumber("Z") << endl;
    cout << solution.titleToNumber("AA") << endl;
    cout << solution.titleToNumber("AZ") << endl;
    cout << solution.titleToNumber("BA") << endl;
    cout << solution.titleToNumber("ZZ") << endl;
    cout << solution.titleToNumber("AAA") << endl;
    cout << solution.titleToNumber("AAZ") << endl;
    cout << solution.titleToNumber("ABA") << endl;
    cout << solution.titleToNumber("AZZ") << endl;
    cout << solution.titleToNumber("BAA") << endl;
    return 0;
}
