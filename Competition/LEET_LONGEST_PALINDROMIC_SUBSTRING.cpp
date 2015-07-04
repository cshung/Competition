#include "stdafx.h"

// https://leetcode.com/problems/longest-palindromic-substring/

#include "LEET_LONGEST_PALINDROMIC_SUBSTRING.h"

#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <string>

using namespace std;

namespace _LEET_LONGEST_PALINDROMIC_SUBSTRING
{
    class Solution
    {
    public:
        string longestPalindrome(string s)
        {
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

                // Step 3: Update boundaries
                if (i + certainly_mirroring_half_length > current_palindrome_inclusive_ends)
                {
                    current_center = i;
                    current_palindrome_inclusive_ends = i + certainly_mirroring_half_length;
                }
            }
            /*
            for (int i = 1; i < conceptual_length - 1; i++)
            {
                cout << i ;
                cout << "\t";
                print_conceptual_character(s, i);
                cout << " ";
                cout << palindrome_half_lengths[i];
                cout << endl;
            }
            */
            int max_index = -1;
            int max_value = -1;

            for (int i = 1; i < conceptual_length - 1; i++)
            {
                if (palindrome_half_lengths[i] > max_value)
                {
                    max_value = palindrome_half_lengths[i];
                    max_index = i;
                }
            }
            // suppose conceptual index 10 is the palindrome, and max_value is 5.
            // which means [6, 7, 8, 9, 10] == [10, 11, 12, 13, 14] 
            int s_index = max_index - max_value + 1;
            int e_index = max_index + max_value - 1;
            s_index++;
            e_index--;
            return s.substr(s_index / 2 - 1, (e_index - s_index) / 2 + 1);
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
                return pair<char ,int>(0, 3);
            }
            else
            {
                return pair<char, int>(s[position / 2 - 1], 0);
            }
        }

    };
};

using namespace _LEET_LONGEST_PALINDROMIC_SUBSTRING;

int LEET_LONGEST_PALINDROMIC_SUBSTRING()
{
    Solution solution;
    string s = "ababc";
    cout << s << endl;
    cout << solution.longestPalindrome(s) << endl;
    return 0;
}