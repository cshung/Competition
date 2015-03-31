#include "stdafx.h"

// https://leetcode.com/problems/add-two-numbers/

#include "LEET_LENGTH_OF_LAST_WORD.h"
#include <map>
#include <iostream>
#include <vector>

using namespace std;

namespace _LEET_LENGTH_OF_LAST_WORD
{
    class Solution
    {
    public:
        int lengthOfLastWord(const char *s)
        {
            int length = strlen(s);
            int state = 0;
            int result = 0;
            for (int i = length - 1; i >= 0; i--)
            {
                if (state == 0)
                {
                    if (s[i] != ' ')
                    {
                        result = 1;
                        state = 1;
                    }
                }
                else if (state == 1)
                {
                    if (s[i] != ' ')
                    {
                        result++;
                    }
                    else
                    {
                        break;
                    }
                }
            }

            return result;
        }
    };
};

using namespace _LEET_LENGTH_OF_LAST_WORD;

int LEET_LENGTH_OF_LAST_WORD()
{
    Solution solution;
    cout << solution.lengthOfLastWord("Hello World") << endl;
    cout << solution.lengthOfLastWord("Hello World ") << endl;
    cout << solution.lengthOfLastWord(" ") << endl;
    cout << solution.lengthOfLastWord("Hello") << endl;
    cout << solution.lengthOfLastWord("Hello ") << endl;
    return 0;
}
