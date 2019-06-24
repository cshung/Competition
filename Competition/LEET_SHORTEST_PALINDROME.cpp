#include "stdafx.h"

// https://leetcode.com/problems/shortest-palindrome/

#include <vector>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

namespace _LEET_SHORTEST_PALINDROME
{
    class Solution
    {
    public:
        string shortestPalindrome(string s)
        {
            if (s.length() == 0)
            {
                return s;
            }
            vector<int> palindrome_half_lengths = manacher(s);
            ostringstream oss;
            shortestPalindrome(oss, s, s.length(), palindrome_half_lengths);
            return oss.str();
        }
        
        void shortestPalindrome(ostringstream& oss, const string& s, int end, const vector<int>& palindrome_half_lengths)
        {
            if (isPalindrome(palindrome_half_lengths, 0, end - 1))
            {
                oss << s;
            }
            else
            {
                oss << s[end - 1];
                shortestPalindrome(oss, s, end - 1, palindrome_half_lengths);
            }
        }
        
        bool isPalindrome(const vector<int>& palindrome_half_lengths, int start, int end)
        {
            // 012 -> 0123456
            // abc -> ^#a#b#c
            // 0 -> 2
            // 1 -> 4
            int conceptual_start = start * 2 + 2; // 0 -> 2
            int conceptual_end = end * 2 + 2; // 2 -> 6
            int conceptual_length = conceptual_end - conceptual_start + 1; // 6 - 2 + 1 = 5
            int conceptual_half_length = conceptual_length / 2 + 1; // 5 / 2 + 1 = 3
            int conceptual_mid = conceptual_start + conceptual_half_length - 1; // 2 + 3 - 1 = 4
            return palindrome_half_lengths[conceptual_mid] >= conceptual_half_length;
        }
        
        vector<int> manacher(const string& s)
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
            return palindrome_half_lengths;
        }

        pair<char, int> get_conceptual_character(const string& s, int position)
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

using namespace _LEET_SHORTEST_PALINDROME;

int LEET_SHORTEST_PALINDROME()
{
    Solution solution;
    string s = "aacecaaa";
    cout << s << endl;
    cout << solution.shortestPalindrome(s) << endl;
    return 0;
}
