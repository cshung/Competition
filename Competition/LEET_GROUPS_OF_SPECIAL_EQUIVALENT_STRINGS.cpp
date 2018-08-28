#include "stdafx.h"

// https://leetcode.com/problems/groups-of-special-equivalent-strings

#include "LEET_GROUPS_OF_SPECIAL_EQUIVALENT_STRINGS.h"
#include <unordered_set>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

namespace _LEET_GROUPS_OF_SPECIAL_EQUIVALENT_STRINGS
{
    class Solution
    {
    public:
        int numSpecialEquivGroups(vector<string>& A)
        {
            unordered_set<string> hash;
            for (int i = 0; i < A.size(); i++)
            {
                char signature[53];
                int countOdd[26];
                int countEven[26];
                for (int j = 0; j < 26; j++)
                {
                    countOdd[j] = 0;
                    countEven[j] = 0;
                }
                for (int j = 0; j < A[i].size(); j += 2)
                {
                    countOdd[A[i][j] - 'a']++;
                }
                for (int j = 1; j < A[i].size(); j += 2)
                {
                    countEven[A[i][j] - 'a']++;
                }
                for (int j = 0; j < 26; j++)
                {
                    signature[j] = countOdd[j] + 'a';
                }
                for (int j = 0; j < 26; j++)
                {
                    signature[j + 26] = countEven[j] + 'a';
                }
                signature[52] = 0;
                auto probe = hash.find(signature);
                if (probe == hash.end())
                {
                    hash.insert(signature);
                }
            }
            return hash.size();
        }
    };
};

using namespace _LEET_GROUPS_OF_SPECIAL_EQUIVALENT_STRINGS;

int LEET_GROUPS_OF_SPECIAL_EQUIVALENT_STRINGS()
{
    Solution solution;
    vector<string> testcase1;
    testcase1.push_back("a");
    testcase1.push_back("b");
    testcase1.push_back("c");
    testcase1.push_back("a");
    testcase1.push_back("c");
    testcase1.push_back("c");

    vector<string> testcase2;
    testcase2.push_back("aa");
    testcase2.push_back("bb");
    testcase2.push_back("ab");
    testcase2.push_back("ba");

    vector<string> testcase3;
    testcase3.push_back("abc");
    testcase3.push_back("acb");
    testcase3.push_back("bac");
    testcase3.push_back("bca");
    testcase3.push_back("cab");
    testcase3.push_back("cba");

    vector<string> testcase4;
    testcase4.push_back("abcd");
    testcase4.push_back("cdab");
    testcase4.push_back("adcb");
    testcase4.push_back("cbad");

    cout << solution.numSpecialEquivGroups(testcase1) << endl;
    cout << solution.numSpecialEquivGroups(testcase2) << endl;
    cout << solution.numSpecialEquivGroups(testcase3) << endl;
    cout << solution.numSpecialEquivGroups(testcase4) << endl;

    return 0;
}