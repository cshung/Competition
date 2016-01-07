#include "stdafx.h"

// https://leetcode.com/problems/climbing-stairs/

#include "LEET_MAXIMUM_PRODUCT_OF_WORD_LENGTHS.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_MAXIMUM_PRODUCT_OF_WORD_LENGTHS
{
    class Solution
    {
    public:
        int maxProduct(vector<string>& words)
        {
            vector<int> wordSummaries;
            wordSummaries.resize(words.size());
            for (unsigned int i = 0; i < words.size(); i++)
            {
                wordSummaries[i] = 0;
                for (unsigned int j = 0; j < words[i].length(); j++)
                {
                    wordSummaries[i] |= (1 << (words[i][j] - 'a'));
                }
            }

            int maxProduct = 0;
            for (unsigned int j = 0; j < words.size(); j++)
            {
                for (unsigned int k = j + 1; k < words.size(); k++)
                {
                    if ((wordSummaries[j] & wordSummaries[k]) == 0)
                    {
                        int product = words[j].length() * words[k].length();
                        maxProduct = max(maxProduct, product);
                    }
                }
            }

            return maxProduct;
        }
    };
};

using namespace _LEET_MAXIMUM_PRODUCT_OF_WORD_LENGTHS;

int LEET_MAXIMUM_PRODUCT_OF_WORD_LENGTHS()
{
    Solution solution;
    string case1_array[] = { "abcw", "baz", "foo", "bar", "xtfn", "abcdef" };
    vector<string> case1(case1_array, case1_array + _countof(case1_array));
    cout << solution.maxProduct(case1) << endl;

    string case2_array[] = { "a", "ab", "abc", "d", "cd", "bcd", "abcd" };
    vector<string> case2(case2_array, case2_array + _countof(case2_array));
    cout << solution.maxProduct(case2) << endl;

    string case3_array[] = { "a", "aa", "aaa", "aaaa" };
    vector<string> case3(case3_array, case3_array + _countof(case3_array));
    cout << solution.maxProduct(case3) << endl;

    return 0;
}