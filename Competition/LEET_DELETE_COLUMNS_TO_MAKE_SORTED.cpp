#include "stdafx.h"

// https://leetcode.com/problems/delete-columns-to-make-sorted/

#include "LEET_DELETE_COLUMNS_TO_MAKE_SORTED.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_DELETE_COLUMNS_TO_MAKE_SORTED
{
    class Solution
    {
    public:
        int minDeletionSize(vector<string>& A)
        {
            if (A.size() == 0)
            {
                return 0;
            }
            int l = A[0].length();
            int ans = 0;
            for (int c = 0; c < l; c++)
            {
                for (int r = 1; r < A.size(); r++)
                {
                    if (A[r][c] < A[r - 1][c])
                    {
                        ans++;
                        break;
                    }
                }
            }
            return ans;
        }
    };
};

using namespace _LEET_DELETE_COLUMNS_TO_MAKE_SORTED;

int LEET_DELETE_COLUMNS_TO_MAKE_SORTED()
{
    Solution s;
    vector<string> test1;
    test1.push_back("cba");
    test1.push_back("daf");
    test1.push_back("ghi");
    cout << (s.minDeletionSize(test1) == 1) << endl;
    vector<string> test2;
    test2.push_back("a");
    test2.push_back("b");
    cout << (s.minDeletionSize(test2) == 0) << endl;
    vector<string> test3;
    test3.push_back("zyx");
    test3.push_back("wvu");
    test3.push_back("tsr");
    cout << (s.minDeletionSize(test3) == 3) << endl;
    return 0;
}