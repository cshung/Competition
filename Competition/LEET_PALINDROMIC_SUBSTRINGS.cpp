#include "stdafx.h"

// https://leetcode.com/problems/palindromic-substrings

#include "LEET_PALINDROMIC_SUBSTRINGS.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_PALINDROMIC_SUBSTRINGS
{
    class Solution
    {
    public:
        int countSubstrings(string s)
        {
            int result = 0;
            int conceptual_length = s.length() * 2 + 3;
            vector<int> palindrome_half_lengths;
            palindrome_half_lengths.resize(conceptual_length - 1); // We do not need to palindrome_half_lengths of the $ character

            // Initialization - the ^ character match nothing, so palindrome_half_lengths[0] = 1
            palindrome_half_lengths[0] = 1;
            int current_center = 0;
            int current_palindrome_inclusive_ends = 0;
            for (int i = 1; i < conceptual_length - 1; i++) // avoid moving beyond $.
            {
                // Step 1: Infer the certainly mirroring half length at position i
                int certainly_mirroring_half_length = 1;
                if (current_palindrome_inclusive_ends > i)
                {
                    int inclusive_remaining_length = current_palindrome_inclusive_ends - i + 1;
                    int mirror_position = current_center - (i - current_center);
                    int mirror_palindrome_half_length = palindrome_half_lengths[mirror_position];
                    if (inclusive_remaining_length < mirror_palindrome_half_length)
                    {
                        certainly_mirroring_half_length = inclusive_remaining_length;
                    }
                    else
                    {
                        certainly_mirroring_half_length = mirror_palindrome_half_length;
                    }
                }
                else
                {
                    certainly_mirroring_half_length = 1;
                }

                // Step 2: Expand 
                while (get_conceptual_character(s, i - certainly_mirroring_half_length + 1) == get_conceptual_character(s, i + certainly_mirroring_half_length - 1))
                {
                    certainly_mirroring_half_length++;
                }
                certainly_mirroring_half_length--;

                palindrome_half_lengths[i] = certainly_mirroring_half_length;
                result += palindrome_half_lengths[i] / 2;

                // Step 3: Update boundaries
                if (i + certainly_mirroring_half_length > current_palindrome_inclusive_ends)
                {
                    current_center = i;
                    current_palindrome_inclusive_ends = i + certainly_mirroring_half_length;
                }
            }

            return result;
        }
    private:
        pair<char, int> get_conceptual_character(string& s, int position)
        {
            if (position == 0)
            {
                return pair<char, int>(0, 1);
            }
            else if (position % 2 == 1)
            {
                return pair<char, int>(0, 2);
            }
            else if (position == (s.length() + 1) * 2)
            {
                return pair<char, int>(0, 3);
            }
            else
            {
                return pair<char, int>(s[position / 2 - 1], 0);
            }
        }

    };
};

using namespace _LEET_PALINDROMIC_SUBSTRINGS;

int LEET_PALINDROMIC_SUBSTRINGS()
{
    Solution solution;
    cout << solution.countSubstrings("abc") << endl;
    cout << solution.countSubstrings("aaa") << endl;
    return 0;
}