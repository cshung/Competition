#include "stdafx.h"

// https://leetcode.com/problems/reverse-words-in-a-string/

#include "LEET_REVERSE_WORDS_IN_A_STRING.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_REVERSE_WORDS_IN_A_STRING
{
    class Solution
    {
    public:
        void reverseWords(string &s)
        {
            int startOutput = 0;
            int scannedInput = 0;
            int wordStart = -1;

            // Phase 1: Reverse the individual words in place
            while (scannedInput < s.length())
            {
                if (wordStart == -1)
                {
                    if (s[scannedInput] == ' ')
                    {
                        scannedInput++;
                    }
                    else
                    {
                        wordStart = scannedInput;
                    }
                }
                else
                {
                    if (s[scannedInput] == ' ')
                    {
                        int wordEnd = scannedInput - 1;
                        int wordLength = wordEnd - wordStart + 1;
                        for (int i = 0; i < wordLength / 2; i++)
                        {
                            swap(s[wordStart + i], s[wordEnd - i]);
                        }
                        wordStart = -1;
                    }
                    else
                    {
                        scannedInput++;
                    }
                }
            }
            if (wordStart != -1)
            {
                int wordEnd = scannedInput - 1;
                int wordLength = wordEnd - wordStart + 1;
                for (int i = 0; i < wordLength / 2; i++)
                {
                    swap(s[wordStart + i], s[wordEnd - i]);
                }
                wordStart = -1;
            }

            // Phase 2: Reverse the whole string in place
            for (int i = 0; i < s.length() / 2; i++)
            {
                swap(s[i], s[s.length() - 1 - i]);
            }

            // Phase 3: Get rid of extra space
            int state = 0; 
            int j = 0;
            for (int i = 0; i < s.length(); i++)
            {
                if (state == 0)
                {
                    if (s[i] == ' ')
                    {
                        // no-op, swallow leading space
                    }
                    else
                    {
                        s[j++] = s[i];
                        state = 1;
                    }
                }
                else if (state == 1)
                {
                    if (s[i] == ' ')
                    {
                        s[j++] = ' ';
                        state = 0;
                    }
                    else
                    {
                        s[j++] = s[i];
                    }
                }
            }
            if (j > 0 && s[j - 1] == ' ')
            {
                j--;
            }
            s.resize(j);
        }
    };
};

using namespace _LEET_REVERSE_WORDS_IN_A_STRING;

int LEET_REVERSE_WORDS_IN_A_STRING()
{
    Solution solution;
    string s = "  the  sky  is  blue  ";
    solution.reverseWords(s);
    cout << "'" << s << "'" << endl;
    return 0;
}