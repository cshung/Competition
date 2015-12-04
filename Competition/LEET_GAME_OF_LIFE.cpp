#include "stdafx.h"

// https://leetcode.com/problems/game-of-life/

#include "LEET_GAME_OF_LIFE.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_GAME_OF_LIFE
{
    class Solution
    {
    public:
        void gameOfLife(vector<vector<int>>& board)
        {
            // Note the design of the NOW variant
            // the least significant bit indicate the old state, so we just read the LSB for old state
            const int DEAD = 0;
            const int LIVE = 1;
            const int NOW_LIVE_WAS_DEAD = 2;
            const int NOW_DEAD_WAS_LIVE = 3;

            int height = board.size();
            if (height == 0)
            {
                return;
            }
            int width = board[0].size();
            if (width == 0)
            {
                return;
            }
            for (int r = 0; r < height; r++)
            {
                for (int c = 0; c < width; c++)
                {
                    int living_neighbor_count = 0;
                    for (int rd = -1; rd <= 1; rd++)
                    {
                        for (int cd = -1; cd <= 1; cd++)
                        {
                            int nr = r + rd;
                            int nc = c + cd;
                            if (nr >= 0 && nr < height && nc >= 0 && nc < width)
                            {
                                if ((board[nr][nc] & 1) == 1)
                                {
                                    living_neighbor_count++;
                                }
                            }
                        }
                    }
                    if ((board[r][c] & 1) == 1)
                    {
                        // For living cell, we need to discount itself.
                        living_neighbor_count--;
                        if (living_neighbor_count < 2 || living_neighbor_count > 3)
                        {
                            board[r][c] = NOW_DEAD_WAS_LIVE;
                        }
                    }
                    else
                    {
                        if (living_neighbor_count == 3)
                        {
                            board[r][c] = NOW_LIVE_WAS_DEAD;
                        }
                    }
                }
            }
            // Clear temp flags
            for (int r = 0; r < height; r++)
            {
                for (int c = 0; c < width; c++)
                {
                    // Now we need a function that maps
                    // DEAD (0) and NOW_DEAD_WAS_LIVE (3) to 0
                    // LIVE (1) and NOW_LIVE_WAS_DEAD (2) to 1
                    // The problem is easier if we look at the number + 1
                    // 0 + 1 = 1 (001) -> 0
                    // 3 + 1 = 4 (100) -> 0
                    // 1 + 1 = 2 (010) => 1
                    // 2 + 1 = 3 (011) => 1
                    // Note the answer is simply the second bit
                    board[r][c] = ((board[r][c] + 1) & 2) >> 1;
                }
            }
        }
    };
};

using namespace _LEET_GAME_OF_LIFE;

int LEET_GAME_OF_LIFE()
{
    Solution solution;
    vector<vector<int>> board;
    board.resize(3);
    board[0].push_back(1);    board[0].push_back(1); board[0].push_back(0);
    board[1].push_back(1);    board[1].push_back(1); board[1].push_back(0);
    board[2].push_back(1);    board[2].push_back(1); board[2].push_back(0);
    solution.gameOfLife(board);
    cout << board[0][0] << board[0][1] << board[0][2] << endl;
    cout << board[1][0] << board[1][1] << board[1][2] << endl;
    cout << board[2][0] << board[2][1] << board[2][2] << endl;
    return 0;
}