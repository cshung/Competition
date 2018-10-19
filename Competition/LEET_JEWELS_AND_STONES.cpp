#include "stdafx.h"

// https://leetcode.com/problems/jewels-and-stones

#include "LEET_JEWELS_AND_STONES.h"
#include <stack>
#include <unordered_set>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_JEWELS_AND_STONES
{
    class Solution
    {
    public:
        int numJewelsInStones(string J, string S)
        {
            unordered_set<char> j;
            for (size_t i = 0; i < J.length(); i++)
            {
                char c = J[i];
                auto probe = j.find(c);
                if (probe == j.end()) {
                    j.insert(c);
                }
            }
            int result = 0;
            for (size_t i = 0; i < S.length(); i++) {
                char c = S[i];
                auto probe = j.find(c);
                if (probe != j.end()) {
                    result++;
                }
            }
            return result;
        }
    };
};

using namespace _LEET_JEWELS_AND_STONES;

int LEET_JEWELS_AND_STONES()
{
    Solution s;
    cout << s.numJewelsInStones("aA", "aAAbbbb") << endl;
    cout << s.numJewelsInStones("z", "ZZ") << endl;
    return 0;
}