#include "stdafx.h"

// https://leetcode.com/problems/repeated-substring-pattern/

#include "LEET_REPEATED_SUBSTRING_PATTERN.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_REPEATED_SUBSTRING_PATTERN
{
    class Solution
    {
    public:
        bool repeatedSubstringPattern(string s)
        {
            vector<int> z(s.length());
            z[0] = 0; // We do NOT compute the length of the Z-box for this one
            unsigned int l = 0; // Inclusive index of the rightmost Z-box
            unsigned int r = 0; // Exclusive index of the rightmost Z-box
            for (unsigned int k = 1; k < s.length(); k++)
            {
                if (k >= r)
                {
                    // The easy (but hard work) case - the current character is not in a Z-box
                    unsigned int start_head = 0;
                    unsigned int start_here = k;
                    unsigned int matching_length = 0;
                    while (start_here < s.length())
                    {
                        if (s[start_head] == s[start_here])
                        {
                            start_head++;
                            start_here++;
                            matching_length++;
                        }
                        else
                        {
                            break;
                        }
                    }

                    z[k] = matching_length;
                    if (matching_length > 0)
                    {
                        l = k;
                        r = k + matching_length;
                    }
                }
                else
                {
                    // Denoting S[a, b) to means S[a ... b - 1]
                    // Denoting S[a -> b] to means S[a, a + b) = S[a ... a + b - 1]

                    // We are sure we know S[L, R) = S[0, R - L)
                    // We also know that L < k < R, so the current character is in a Z-box
                    // Therefore we know S[k, R) = S[k - L -> R - k]

                    int matching_length = r - k; // This is the length of S[k, R), the length of the string that we know must match

                    // We also know S[k - L -> z[k - L]] matches with S[0, z[k - L])
                    int reference_box_length = z[k - l];


                    if (reference_box_length < matching_length)
                    {
                        // We know S[k, R) = S[k - L -> R - k]
                        // We also know z[k - L] < R - k, as we just checked
                        //
                        // Therefore S[k -> z[k - L]] = S[k - L -> z[k - L]]    [ That is because if you match a string, you match a substring too]
                        //
                        // We also know S[k - L -> z[k - L]] = S[0, z[k - L])
                        //
                        // Last but not least, we know for sure that the next character does not match
                        //
                        // Therefore we know this:
                        //
                        z[k] = z[k - l];
                    }
                    else
                    {
                        // Using the logic above, we know 
                        // S[k, R) = S[0, R - k)
                        // We do not know if the remaining characters match (as we never read beyond R)
                        // So we have to march both forward to check there
                        unsigned int start_head = matching_length;
                        unsigned int start_here = k + matching_length;
                        unsigned int actual_matching_length = matching_length;
                        while (start_here < s.length())
                        {
                            if (s[start_head] == s[start_here])
                            {
                                start_head++;
                                start_here++;
                                actual_matching_length++;
                            }
                            else
                            {
                                break;
                            }
                        }

                        z[k] = actual_matching_length;
                        if (actual_matching_length > 0)
                        {
                            l = k;
                            r = k + actual_matching_length;
                        }
                    }
                }
                if (k + z[k] == s.length())
                {
                    // Here we detect the largest z-box that ends at the last character
                    // For repeated strings, the left hand side must be the repeating unit
                    // So this condition makes sense.
                    // In case it does not repeat, either the z-box is shorter than the 
                    // prefix part, where the check would automatically fail, or 
                    // we hit the 'abcabca' case where the z-box is `abca` and the 
                    // division check will still detect it.
                    return (z[k] % k) == 0;
                }
            }
            return false;
        }
    };
};

using namespace _LEET_REPEATED_SUBSTRING_PATTERN;

int LEET_REPEATED_SUBSTRING_PATTERN()
{
    Solution solution;
    cout << solution.repeatedSubstringPattern("abab") << endl;
    cout << solution.repeatedSubstringPattern("aba") << endl;
    cout << solution.repeatedSubstringPattern("abcabcabcabc") << endl;
    return 0;
}