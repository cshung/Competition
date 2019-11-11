#include "stdafx.h"

// https://leetcode.com/problems/n-queens/

#include "LEET_N_QUEENS.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_N_QUEENS
{
    class Solution
    {
    public:
        vector<vector<string>> solveNQueens(int n)
        {
            vector<vector<int>> board;
            board.resize(n);
            for (int row = 0; row < n; row++)
            {
                board[row].resize(n);
                for (int col = 0; col < n; col++)
                {
                    board[row][col] = 0;
                }
            }
            solve(board, n, 0, 0, n);
            return solutions;
        }
    private:
        vector<vector<string>> solutions;
        void solve(vector<vector<int>>& board, int n, int row, int col, int count)
        {
            if (count == 0)
            {
                vector<string> solution;
                for (int row = 0; row < n; row++)
                {
                    string solutionString;
                    for (int col = 0; col < n; col++)
                    {
                        solutionString += (board[row][col] == -1) ? 'Q' : '.';
                    }
                    solution.push_back(solutionString);
                }
                solutions.push_back(solution);
                return;
            }
            while (true)
            {
                if (board[row][col] == 0)
                {
                    board[row][col] = -1;
                    mark(board, n, row, col, 1);
                    solve(board, n, row, col, count - 1);
                    board[row][col] = 0;
                    mark(board, n, row, col, -1);
                }
                col++;
                if (col == n)
                {
                    col = 0;
                    row++;
                }
                if (row == n)
                {
                    break;
                }
            }
        }

        void mark(vector<vector<int>>& board, int n, int row, int col, int mark)
        {
            int r;
            int c;
            for (r = 0; r < n; r++)
            {
                if (r != row)
                {
                    board[r][col] += mark;
                }
            }
            for (c = 0; c < n; c++)
            {
                if (c != col)
                {
                    board[row][c] += mark;
                }
            }
            r = row;
            c = col;
            while (0 <= r && r < n && 0 <= c && c < n)
            {
                r--;
                c--;
            }
            r++;
            c++;
            while (0 <= r && r < n && 0 <= c && c < n)
            {
                if (r != row && c != col)
                {
                    board[r][c] += mark;
                }
                r++;
                c++;
            }
            r = row;
            c = col;
            while (0 <= r && r < n && 0 <= c && c < n)
            {
                r--;
                c++;
            }
            r++;
            c--;
            while (0 <= r && r < n && 0 <= c && c < n)
            {
                if (r != row && c != col)
                {
                    board[r][c] += mark;
                }
                r++;
                c--;
            }

        }
    };
};

using namespace _LEET_N_QUEENS;

int LEET_N_QUEENS()
{
    Solution solution;
    vector<vector<string>> answers = solution.solveNQueens(9);
    for (auto answer : answers)
    {
        for (auto row : answer)
        {
            cout << row << endl;
        }
        cout << endl;
    }
    return 0;
}