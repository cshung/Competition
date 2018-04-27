#include "stdafx.h"

// https://leetcode.com/problems/card-flipping-game

#include "LEET_CARD_FLIPPING_GAME.h"
#include <map>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_CARD_FLIPPING_GAME
{
    class Solution
    {
    public:
        int flipgame(vector<int>& fronts, vector<int>& backs)
        {
            bool forbidden[2001];
            for (int i = 1; i <= 2000; i++)
            {
                forbidden[i] = false;
            }
            for (size_t i = 0; i < fronts.size(); i++)
            {
                if (fronts[i] == backs[i])
                {
                    forbidden[fronts[i]] = true;
                }
            }

            int result = 2001;

            for (size_t i = 0; i < fronts.size(); i++)
            {
                if (!forbidden[fronts[i]])
                {
                    result = min(result, fronts[i]);
                }
                if (!forbidden[backs[i]])
                {
                    result = min(result, backs[i]);
                }
            }

            if (result == 2001)
            {
                return 0;
            }

            return result;
        }
    };
};

using namespace _LEET_CARD_FLIPPING_GAME;

int LEET_CARD_FLIPPING_GAME()
{
    Solution solution;
    int fronts[] = { 1, 2, 4, 4, 7 };
    int backs[] = { 1, 3, 4, 1, 3 };
    cout << solution.flipgame(vector<int>(fronts, fronts + _countof(fronts)), vector<int>(backs, backs + _countof(backs))) << endl;
    return 0;
}