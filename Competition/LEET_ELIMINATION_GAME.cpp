#include "stdafx.h"

// https://leetcode.com/contest/2/problems/elimination-game/

#include "LEET_ELIMINATION_GAME.h"
#include <stack>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

#include <stdio.h>

using namespace std;

namespace _LEET_ELIMINATION_GAME
{
    class Solution
    {
    public:
        int lastRemaining(int n)
        {
            return lastRemaining(1, n, 0);
        }

        int lastRemaining(int smallest, int largest, int round)
        {
            if (smallest == largest)
            {
                return smallest;
            }
            if (round % 2 == 0)
            {
                if (smallest % 2 == 0)
                {
                    // Eliminate all 0
                    smallest += 1;
                    if (largest % 2 == 0) { largest -= 1; }
                    return lastRemaining(smallest >> 1, largest >> 1, 1) * 2 + 1;
                }
                else
                {
                    // Eliminating all 1
                    smallest += 1;
                    if (largest % 2 == 1) { largest -= 1; }
                    return lastRemaining(smallest >> 1, largest >> 1, 1) * 2;
                }
            }
            else
            {
                if (largest % 2 == 0)
                {
                    // Eliminate all 0
                    largest -= round;
                    if (smallest % 2 == 0) { smallest += 1; }
                    return lastRemaining(smallest >> 1, largest >> 1, 0) * 2 + 1;
                }
                else
                {
                    // Eliminating all 1
                    largest -= round;
                    if (smallest % 2 == 1) { smallest += 1; }
                    return lastRemaining(smallest >> 1, largest >> 1, 0) * 2;
                }
            }
        }
    };
};

using namespace _LEET_ELIMINATION_GAME;

int LEET_ELIMINATION_GAME()
{
    Solution solution;
    // Direct simulation is not the way to go, running out of memory
    cout << solution.lastRemaining(10000000) << endl;
    return 0;
}