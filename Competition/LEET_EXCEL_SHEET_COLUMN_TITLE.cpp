#include "stdafx.h"

// https://leetcode.com/problems/excel-sheet-column-title/

#include "LEET_EXCEL_SHEET_COLUMN_TITLE.h"
#include <map>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

namespace _LEET_EXCEL_SHEET_COLUMN_TITLE
{
    class Solution
    {
    public:
        string convertToTitle(int n)
        {
            stringstream result_builder;
            vector<char> result;
            while (n > 0)
            {
                int d = n % 26;
                if (d == 0)
                {
                    d = 26;
                }
                n -= d;
                n /= 26;
                result.push_back(d + 'A' - 1);
            }

            for (vector<char>::const_reverse_iterator ri = result.rbegin(); ri != result.rend(); ri++)
            {
                result_builder << *ri;
            }
            
            return result_builder.str();
        }
    };
};

using namespace _LEET_EXCEL_SHEET_COLUMN_TITLE;

int LEET_EXCEL_SHEET_COLUMN_TITLE()
{
    Solution solution;
    cout << solution.convertToTitle(1) << endl;
    cout << solution.convertToTitle(26) << endl;
    cout << solution.convertToTitle(27) << endl;
    cout << solution.convertToTitle(52) << endl;
    cout << solution.convertToTitle(53) << endl;
    cout << solution.convertToTitle(702) << endl;
    cout << solution.convertToTitle(703) << endl;
    return 0;
}
