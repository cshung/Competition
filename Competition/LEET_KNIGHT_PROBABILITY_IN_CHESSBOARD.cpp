#include "stdafx.h"

// https://leetcode.com/problems/knight-probability-in-chessboard

#include "LEET_KNIGHT_PROBABILITY_IN_CHESSBOARD.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_KNIGHT_PROBABILITY_IN_CHESSBOARD
{
    class Solution
    {
    public:
        double knightProbability(int N, int K, int r, int c) {
            double** board_old;
            double** board_new;
            board_old = new double*[N];
            board_new = new double*[N];
            for (int r = 0; r < N; r++)
            {
                board_new[r] = new double[N];
                board_old[r] = new double[N];
                for (int c = 0; c < N; c++)
                {
                    board_old[r][c] = board_new[r][c] = 0;
                }
            }
            double** current = (double**)board_old;
            double** next = (double**)board_new;
            current[r][c] = 1;
            for (int step = 0; step < K; step++)
            {
                for (int r = 0; r < N; r++)
                {
                    for (int c = 0; c < N; c++)
                    {
                        next[r][c] = 0;
                    }
                }

                for (int r = 0; r < N; r++)
                {
                    for (int c = 0; c < N; c++)
                    {
                        if (current[r][c] != 0)
                        {
                            vector<pair<int, int>> candidates;
                            candidates.push_back(make_pair(r + 2, c + 1));
                            candidates.push_back(make_pair(r + 1, c + 2));
                            candidates.push_back(make_pair(r + 2, c - 1));
                            candidates.push_back(make_pair(r + 1, c - 2));
                            candidates.push_back(make_pair(r - 2, c + 1));
                            candidates.push_back(make_pair(r - 1, c + 2));
                            candidates.push_back(make_pair(r - 2, c - 1));
                            candidates.push_back(make_pair(r - 1, c - 2));
                            for (auto&& candidate : candidates)
                            {
                                int pr = candidate.first;
                                int pc = candidate.second;
                                if (0 <= pr && pr < N && 0 <= pc && pc < N)
                                {
                                    next[pr][pc] += current[r][c] / 8.0;
                                }
                            }
                        }
                    }
                }

                swap(current, next);
            }
            double count = 0;
            for (int r = 0; r < N; r++)
            {
                for (int c = 0; c < N; c++)
                {
                    count += current[r][c];
                }
            }
            return count;
        }
    };
};

using namespace _LEET_KNIGHT_PROBABILITY_IN_CHESSBOARD;

int LEET_KNIGHT_PROBABILITY_IN_CHESSBOARD()
{
    Solution s;
    cout << s.knightProbability(3, 2, 0, 0) << endl;
    return 0;
}