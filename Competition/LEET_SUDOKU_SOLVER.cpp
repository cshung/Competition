#include "stdafx.h"

// https://leetcode.com/problems/sudoku-solver/

#include "LEET_SUDOKU_SOLVER.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_SUDOKU_SOLVER
{
    class Solution
    {
    public:
        void solveSudoku(vector<vector<char>>& board)
        {
            Solve(board);
            return;
        }

        int counter[9];

        void ResetCounter()
        {
            for (int i = 0; i < 9; i++)
            {
                counter[i] = 0;
            }
        }

        bool IsValid(vector<vector<char>>& board)
        {	
            for (int row = 0; row < 9; row++)
            {
                ResetCounter();
                for (int col = 0; col < 9; col++)
                {
                    char boardValue = board[col][row];
                    if (boardValue != '.')
                    {
                        if (counter[boardValue - '1'] == 0)
                        {
                            counter[boardValue - '1'] = 1;
                        }
                        else
                        {
                            return false;
                        }
                    }
                }
            }
            for (int col = 0; col < 9; col++)
            {
                ResetCounter();
                for (int row = 0; row < 9; row++)
                {
                    char boardValue = board[col][row];
                    if (boardValue != '.')
                    {
                        if (counter[boardValue - '1'] == 0)
                        {
                            counter[boardValue - '1'] = 1;
                        }
                        else
                        {
                            return false;
                        }
                    }
                }
            }

            for (int blockRow = 0; blockRow < 3; blockRow++)
            {
                for (int blockCol = 0; blockCol < 3; blockCol++)
                {
                    ResetCounter();
                    for (int row = 0; row < 3; row++)
                    {
                        for (int col = 0; col < 3; col++)
                        {
                            char boardValue = board[blockCol * 3 + col][blockRow * 3 + row];
                            if (boardValue != '.')
                            {
                                if (counter[boardValue - '1'] == 0)
                                {
                                    counter[boardValue - '1'] = 1;
                                }
                                else
                                {
                                    return false;
                                }
                            }
                        }
                    }
                }
            }

            return true;
        }

        bool Solve(vector<vector<char>>& board)
        {
            int foundRow = -1;
            int foundCol = -1;
            for (int row = 0; foundRow == -1 && row < 9; row++)
            {
                for (int col = 0; foundCol == -1 && col < 9; col++)
                {
                    if (board[row][col] == '.')
                    {
                        foundRow = row;
                        foundCol = col;
                    }
                }
            }

            if (foundRow == -1)
            {
                return true;
            }
            else
            {
                int solutionCount = 0;
                for (int candidate = 1; candidate <= 9; candidate++)
                {
                    board[foundRow][foundCol] = candidate + '0';
                    if (IsValid(board))
                    {
                        if (Solve(board))
                        {
                            return true;
                        }
                    }

                    board[foundRow][foundCol] = '.';
                }

                return false;
            }
        }
    };
}

using namespace _LEET_SUDOKU_SOLVER;

int LEET_SUDOKU_SOLVER()
{
    Solution solution;
    int boardArray[9][9] =
    {
        {0, 9, 0, 0, 3, 0, 1, 0, 0},
        {0, 8, 0, 0, 0, 1, 5, 0, 2},
        {0, 0, 2, 6, 4, 0, 0, 0, 3},
        {5, 0, 0, 1, 0, 0, 0, 6, 4},
        {0, 4, 0, 9, 0, 6, 0, 5, 0},
        {8, 6, 0, 0, 0, 4, 0, 0, 7},
        {4, 0, 0, 0, 6, 2, 8, 0, 0},
        {9, 0, 8, 4, 0, 0, 0, 2, 0},
        {0, 0, 7, 0, 5, 0, 0, 3, 0}
    };
    vector<vector<char>> board;
    board.resize(9);
    for (int row = 0; row < 9; row++)
    {
        board[row].resize(9);
        for (int col = 0; col < 9; col++)
        {
            board[row][col] = boardArray[row][col] == 0 ? '.' : (boardArray[row][col] + '0');
        }
    }
    solution.solveSudoku(board);
    for (int row = 0; row < 9; row++)
    {
        for (int col = 0; col < 9; col++)
        {
            cout << board[row][col] << " ";
        }
        cout << endl;
    }
    return 0;
}