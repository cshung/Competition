#include "stdafx.h"

// https://leetcode.com/problems/valid-sudoku/

#include "LEET_VALID_SUDOKU.h"
#include <stack>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_VALID_SUDOKU
{
    class Solution {
    private:
        bool found[9];
        void reset()
        {
            for (int i = 0; i < 9; i++)
            {
                found[i] = false;
            }
        }
        bool seen(char i)
        {
            if (i == '.')
            {
                return false;
            }
            i = i - '0';
            if (found[i - 1] == true)
            {
                return true;
            }
            else
            {
                found[i - 1] = true;
                return false;
            }
        }
    public:
        bool isValidSudoku(vector<vector<char>>& board)
        {
            // Rows 
            for (int row = 0; row < 9; row++)
            {
                reset();
                for (int col = 0; col < 9; col++)
                {
                    if (seen(board[row][col]))
                    {
                        return false;
                    }
                }
            }

            // Cols
            for (int col = 0; col < 9; col++)
            {
                reset();
                for (int row = 0; row < 9; row++)
                {
                    if (seen(board[row][col]))
                    {
                        return false;
                    }
                }
            }

            // Blocks
            for (int blockRow = 0; blockRow < 3; blockRow++)
            {
                for (int blockCol = 0; blockCol < 3; blockCol++)
                {
                    reset();
                    for (int row = blockRow * 3; row < blockRow * 3 + 3; row++)
                    {
                        for (int col = blockCol * 3; col < blockCol * 3 + 3; col++)
                        {
                            if (seen(board[row][col]))
                            {
                                return false;
                            }
                        }
                    }
                }
            }

            return true;

        }
    };
};

using namespace _LEET_VALID_SUDOKU;

int LEET_VALID_SUDOKU()
{
    Solution solution;
    vector<vector<char>> input;
    input.resize(9);
    for (int i = 0; i < 9; i++)
    {
        input[i].resize(9);
        for (int j = 0; j < 9; j++)
        {
            input[i][j] = '.';
        }
    }
    input[0][0] = '5';
    input[0][1] = '3';
    input[0][4] = '7';

    input[1][0] = '6';
    input[1][3] = '1';
    input[1][4] = '9';
    input[1][5] = '5';

    input[2][1] = '9';
    input[2][2] = '8';
    input[2][7] = '6';

    input[3][0] = '8';
    input[3][4] = '6';
    input[3][8] = '3';

    input[4][0] = '4';
    input[4][3] = '8';
    input[4][5] = '3';
    input[4][8] = '1';

    input[5][0] = '7';
    input[5][4] = '2';
    input[5][8] = '6';

    input[6][1] = '6';
    input[6][6] = '2';
    input[6][7] = '8';

    input[7][3] = '4';
    input[7][4] = '1';
    input[7][5] = '9';
    input[7][8] = '5';

    input[8][4] = '8';
    input[8][7] = '7';
    input[8][8] = '9';

    cout << solution.isValidSudoku(input) << endl;

    return 0;
}
