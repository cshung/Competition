#include "stdafx.h"

// https://leetcode.com/problems/group-shifted-strings/

#include "LEET_GROUP_SHIFTED_STRINGS.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_GROUP_SHIFTED_STRINGS
{
    class Solution
    {
    public:
        vector<vector<string>> groupStrings(vector<string>& strings)
        {
            map<string, vector<int>> signatures;
            for (int i = 0; i < strings.size(); i++)
            {
                string s = strings[i];
                ostringstream oss;
                for (int i = 1; i < s.size(); i++)
                {
                    char diff = ((s[i] - s[i - 1] + 26) % 26) + 'A';
                    oss << diff;
                }
                string signature = oss.str();
                auto probe = signatures.find(signature);
                if (probe == signatures.end())
                {
                    vector<int> blank;
                    signatures.insert(make_pair(signature, blank));
                }
                signatures[signature].push_back(i);
            }
            vector<vector<string>> groups;
            for (auto pair : signatures)
            {
                vector<string> group;
                for (auto i : pair.second)
                {
                    group.push_back(strings[i]);
                }
                groups.push_back(group);
            }
            return groups;
        }
    };
};

using namespace _LEET_GROUP_SHIFTED_STRINGS;

int LEET_GROUP_SHIFTED_STRINGS()
{
    Solution solution;
    string test_array[] = { "abc", "bcd", "acef", "xyz", "az", "ba", "a", "z" };
    vector<string> test(test_array, test_array + _countof(test_array));
    auto groups = solution.groupStrings(test);
    for (auto group : groups)
    {
        for (auto member : group)
        {
            cout << member << ", ";
        }
        cout << endl;
    }
    return 0;
}