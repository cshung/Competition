#include "stdafx.h"

// https://leetcode.com/problems/nim-game/

#include "LEET_NIM_GAME.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_NIM_GAME
{
    class Solution
    {
    public:
        bool canWinNim(int n)
        {
            return ((n % 4) != 0);
        }
    };
};

using namespace _LEET_NIM_GAME;

int LEET_NIM_GAME()
{
    Solution solution;
    for (int i = 1; i <= 10; i++)
    {
        cout << solution.canWinNim(i) << endl;
    }

    return 0;
}