#include "stdafx.h"

// https://leetcode.com/problems/reverse-words-in-a-string-ii/

#include "LEET_REVERSE_WORDS_IN_A_STRING_II.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_REVERSE_WORDS_IN_A_STRING_II
{
    class Solution
    {
    public:
        void reverseWords(vector<char>& s)
        {
            reverse(s, 0, s.size() - 1);
            int last = 0;
            for (int i = 0; i < s.size(); i++)
            {
                if (s[i] == ' ')
                {
                    reverse(s, last, i - 1);
                    last = i + 1;
                }
            }
            reverse(s, last, s.size() - 1);
        }

        void reverse(vector<char>& s, int i, int j)
        {
            while (i < j)
            {
                swap(s[i], s[j]);
                i++;
                j--;
            }
        }
    };
};

using namespace _LEET_REVERSE_WORDS_IN_A_STRING_II;

int LEET_REVERSE_WORDS_IN_A_STRING_II()
{
    Solution solution;
    char test_array[] = { 't', 'h', 'e', ' ', 's', 'k', 'y', ' ', 'i', 's', ' ', 'b', 'l', 'u', 'e' };
    vector<char> test(test_array, test_array + _countof(test_array));
    solution.reverseWords(test);
    for (char c : test)
    {
        cout << c;
    }
    cout << endl;
    return 0;
}