#include "stdafx.h"

// https://leetcode.com/problems/longest-substring-without-repeating-characters/

#include "LEET_LONGEST_SUBSTRING_WITHOUT_REPEATING_CHARACTERS.h"
#include <map>
#include <iostream>
#include <vector>

using namespace std;

// #define LOG

namespace _LEET_LONGEST_SUBSTRING_WITHOUT_REPEATING_CHARACTERS
{
    class Solution 
    {
    public:
        int lengthOfLongestSubstring(string s) 
        {
            if (s.length() == 0)
            {
                return 0;
            }
            else
            {
                int best_s = 0;
                int best_e = 0;
                int best_l = 1;
                int last_s = 0;
                int last_e = 0;
                int last_l = 1;
                map<char, int> last_index;
                last_index.insert(pair<char, int>(s[0], 0));

                for (unsigned int i = 1; i < s.length(); i++)
                {
                    map<char, int>::iterator probe = last_index.find(s[i]);
                    if (probe == last_index.end())
                    {
                        // the current character is not found - so simply extend the last sequence
                        last_index.insert(pair<char, int>(s[i], i));
                    }
                    else
                    {
                        int last_character_index = probe->second;
                        probe->second = i;
                        if (last_character_index >= last_s)
                        {
                            last_s = last_character_index + 1;
                        }
                        else
                        {
                            // There is an occurrence of the current character, but that doesn't matter since it was out already
                        }
                    }
                    last_e = i;
                    last_l = last_e - last_s + 1;
                    if (last_l > best_l)
                    {
                        best_l = last_l;
                        best_s = last_s;
                        best_e = last_e;
                    }
                    

#ifdef LOG
                    cout << "Current string: ";
                    for (unsigned int j = 0; j <= i; j++)
                    {
                        cout << s[j];
                    }
                    cout << endl;

                    cout << "The best string: ";
                    for (int bi = best_s; bi <= best_e; bi++)
                    {
                        cout << s[bi];
                    }
                    cout << endl;

                    cout << "The last string: ";
                    for (int li = last_s; li <= last_e; li++)
                    {
                        cout << s[li];
                    }
                    cout << endl;
                    cout << endl;
#endif
                }

                return best_l;
            }
        }
    };
};

using namespace _LEET_LONGEST_SUBSTRING_WITHOUT_REPEATING_CHARACTERS;

int LEET_LONGEST_SUBSTRING_WITHOUT_REPEATING_CHARACTERS()
{
    Solution solution;
    cout << solution.lengthOfLongestSubstring("abcabcbb") << endl;
    cout << solution.lengthOfLongestSubstring("bbbbb") << endl;
    return 0;
}
