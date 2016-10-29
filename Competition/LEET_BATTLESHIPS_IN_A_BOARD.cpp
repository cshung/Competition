#include "stdafx.h"

// https://leetcode.com/problems/battleships-in-a-board/

#include "LEET_BATTLESHIPS_IN_A_BOARD.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_BATTLESHIPS_IN_A_BOARD
{
    class Solution
    {
    public:
        int countBattleships(vector<vector<char>>& board)
        {
            int m = board.size();
            if (m == 0)
            {
                return 0;
            }
            int n = board[0].size();
            if (n == 0)
            {
                return 0;
            }
            vector<int> disjoint_sets;
            disjoint_sets.resize(m * n);
            for (int i = 0; i < m * n; i++)
            {
                disjoint_sets[i] = -1;
            }
            for (int r = 0; r < m - 1; r++)
            {
                for (int c = 0; c < n - 1; c++)
                {
                    if (board[r][c] == 'X' && board[r + 1][c] == 'X')
                    {
                        union_sets(disjoint_sets, r * n + c, (r + 1) * n + c);
                    }
                    if (board[r][c] == 'X' && board[r][c + 1] == 'X')
                    {
                        union_sets(disjoint_sets, r * n + c, r * n + c + 1);
                    }
                }
                if (board[r][n - 1] == 'X' && board[r + 1][n - 1] == 'X')
                {
                    union_sets(disjoint_sets, r * n + (n - 1), (r + 1) * n + (n - 1));
                }
            }
            for (int c = 0; c < n - 1; c++)
            {
                if (board[m - 1][c] == 'X' && board[m - 1][c + 1] == 'X')
                {
                    union_sets(disjoint_sets, (m - 1) * n + c, (m - 1) * n + c + 1);
                }
            }

            int count = 0;
            for (int r = 0; r < m; r++)
            {
                for (int c = 0; c < n; c++)
                {
                    if (board[r][c] == 'X' && disjoint_sets[r * n + c] < 0)
                    {
                        count++;
                    }
                }
            }

            return count;
        }
    private:
        int find(vector<int>& disjoint_sets, int v)
        {
            if (disjoint_sets[v] < 0)
            {
                return v;
            }
            else
            {
                return disjoint_sets[v] = find(disjoint_sets, disjoint_sets[v]);
            }
        }
        void union_sets(vector<int>& disjoint_sets, int u, int v)
        {
            int set1 = find(disjoint_sets, u);
            int set2 = find(disjoint_sets, v);
            if (set1 != set2)
            {
                int size1 = -disjoint_sets[set1];
                int size2 = -disjoint_sets[set2];
                if (size1 > size2)
                {
                    disjoint_sets[set2] = set1;
                    disjoint_sets[set1] -= size2;
                }
                else
                {
                    disjoint_sets[set1] = set2;
                    disjoint_sets[set2] -= size1;
                }
            }
        }
    };
};

using namespace _LEET_BATTLESHIPS_IN_A_BOARD;

int LEET_BATTLESHIPS_IN_A_BOARD()
{
    Solution solution;
    vector<vector<char>> board;
    board.resize(3);
    for (int i = 0; i < 3; i++)
    {
        board[i].resize(4);
    }
    board[0][0] = 'X';    board[0][1] = '.';    board[0][2] = '.';    board[0][3] = 'X';
    board[1][0] = '.';    board[1][1] = '.';    board[1][2] = '.';    board[1][3] = 'X';
    board[2][0] = '.';    board[2][1] = '.';    board[2][2] = '.';    board[2][3] = 'X';
    cout << solution.countBattleships(board) << endl;
    return 0;
}