#include "stdafx.h"

// https://leetcode.com/problems/word-search/

#include "LEET_WORD_SEARCH.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_WORD_SEARCH
{
    class Solution
    {
    public:
        bool exist(vector<vector<char>>& board, string word)
        {
            int height = board.size();
            if (height == 0)
            {
                return false;
            }
            int width = board[0].size();
            if (width == 0)
            {
                return false;
            }
            bool found = false;
            for (int row = 0; !found && row < height; row++)
            {
                for (int col = 0; !found && col < width; col++)
                {
                    if (dfs(board, word, row, col, 0))
                    {
                        found = true;
                    }
                }
            }
            return found;
        }
    private:
        bool dfs(vector<vector<char>>& board, string& word, int row, int col, int l)
        {
            if (row < 0 || row >= board.size() || col < 0 || col >= board[0].size() || board[row][col] != word[l])
            {
                return false;
            }
            if (l == word.length() - 1)
            {
                return true;
            }

            board[row][col] = '#';
            bool found = false ||
                dfs(board, word, row, col - 1, l + 1) ||
                dfs(board, word, row, col + 1, l + 1) ||
                dfs(board, word, row - 1, col, l + 1) ||
                dfs(board, word, row + 1, col, l + 1);
            board[row][col] = word[l];
            return found;
        }
    };
};

using namespace _LEET_WORD_SEARCH;

int LEET_WORD_SEARCH()
{
    vector<vector<char>> board(3);
    board[0].push_back('A'); board[0].push_back('B'); board[0].push_back('C'); board[0].push_back('E');
    board[1].push_back('S'); board[1].push_back('F'); board[1].push_back('C'); board[1].push_back('S');
    board[2].push_back('A'); board[2].push_back('D'); board[2].push_back('E'); board[2].push_back('E');

    Solution solution;
    cout << solution.exist(board, "ABCCED") << endl;
    cout << solution.exist(board, "SEE") << endl;
    cout << solution.exist(board, "ABCB") << endl;
    return 0;
}