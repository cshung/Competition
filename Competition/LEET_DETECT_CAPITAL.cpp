#include "stdafx.h"

// https://leetcode.com/problems/detect-capital/

#include "LEET_DETECT_CAPITAL.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_DETECT_CAPITAL
{
    class Solution
    {
    public:
        bool detectCapitalUse(string word)
        {
            int state = 0;
            for (int i = 0; i < word.length(); i++)
            {
                bool isCapital = (('A' <= word[i]) && (word[i] <= 'Z'));
                if (state == 0)
                {
                    state = isCapital ? 1 : 2;
                }
                else if (state == 1)
                {
                    state = isCapital ? 3 : 2;
                }
                else if (state == 2)
                {
                    if (isCapital)
                    {
                        return false;
                    }
                }
                else
                {
                    if (!isCapital)
                    {
                        return false;
                    }
                }
            }
            return true;
        }
    };
};

using namespace _LEET_DETECT_CAPITAL;

int LEET_DETECT_CAPITAL()
{
    Solution s;
    cout << s.detectCapitalUse("USA") << endl;
    cout << s.detectCapitalUse("FlaG") << endl;
    cout << s.detectCapitalUse("leetcode") << endl;
    cout << s.detectCapitalUse("Google") << endl;
    return 0;
}