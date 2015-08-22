#include "stdafx.h"

// https://leetcode.com/problems/3sum/

#include "LEET_IMPLEMENT_STRSTR.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

namespace _LEET_IMPLEMENT_STRSTR
{
    class Solution
    {
    public:
        int strStr(string haystack, string needle)
        {
            // Special case - searching for empty string.
            if (needle == "")
            {
                return 0;
            }

            // Step 1: concatenate the strings
            unsigned int concatenated_length = needle.size() + 1 + haystack.size();
            char* concatenated = new char[concatenated_length];
            unsigned int i = 0;
            for (unsigned int j = 0; j < needle.size(); i++, j++)
            {
                concatenated[i] = needle[j];
            }
            concatenated[i++] = '\0';
            for (unsigned int j = 0; j < haystack.size(); i++, j++)
            {
                concatenated[i] = haystack[j];
            }

            // Step 2: Fundamental preprocessing
            int* z = new int[concatenated_length];
            z[0] = 0; // We do NOT compute the length of the Z-box for this one
            unsigned int l = 0; // Inclusive index of the rightmost Z-box
            unsigned int r = 0; // Exclusive index of the rightmost Z-box
            for (unsigned int k = 1; k < concatenated_length; k++)
            {
                if (k >= r)
                {
                    // The easy (but hard work) case - the current character is not in a Z-box
                    unsigned int start_head = 0;
                    unsigned int start_here = k;
                    unsigned int matching_length = 0;
                    while (start_here < concatenated_length)
                    {
                        if (concatenated[start_head] == concatenated[start_here])
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
                        // TODO
                        unsigned int start_head = matching_length;
                        unsigned int start_here = k + matching_length;
                        unsigned int actual_matching_length = matching_length;
                        while (start_here < concatenated_length)
                        {
                            if (concatenated[start_head] == concatenated[start_here])
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

                // If we found a match, returns right away
                if (z[k] == needle.size())
                {
                    // Skip the needle$ prefix
                    return k - needle.size() - 1;
                }
            }

            return -1;
        }
    };
};

using namespace _LEET_IMPLEMENT_STRSTR;

int LEET_IMPLEMENT_STRSTR()
{
    Solution s;
    cout << s.strStr("haystack", "sta") << endl;
    return 0;
}