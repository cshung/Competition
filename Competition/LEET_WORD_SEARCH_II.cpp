#include "stdafx.h"

// https://leetcode.com/problems/word-search-ii/

#include "LEET_WORD_SEARCH_II.h"
#include <map>
#include <iostream>
#include <queue>
#include <set>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_WORD_SEARCH_II
{
    class Solution
    {
    public:
        vector<string> findWords(vector<vector<char>>& board, vector<string>& words)
        {
            vector<string> result;
            int height = board.size();
            if (height == 0)
            {
                return result;
            }
            int width = board[0].size();
            if (width == 0)
            {
                return result;
            }
            for (int i = 0; i < words.size(); i++)
            {
                bool found = false;
                for (int row = 0; !found && row < height; row++)
                {
                    for (int col = 0; !found && col < width; col++)
                    {
                        if (dfs(board, words[i], row, col, 0))
                        {
                            found = true;
                        }
                    }
                }
                if (found)
                {
                    result.push_back(words[i]);
                }
            }
            return result;
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

using namespace _LEET_WORD_SEARCH_II;

int LEET_WORD_SEARCH_II()
{
    Solution solution;

    char row1_array[] = { 'o', 'a', 'a', 'n' };
    char row2_array[] = { 'e', 't', 'a', 'e' };
    char row3_array[] = { 'i', 'h', 'k', 'r' };
    char row4_array[] = { 'i', 'f', 'l', 'v' };
    vector<vector<char>> board;
    board.push_back(vector<char>(row1_array, row1_array + _countof(row1_array)));
    board.push_back(vector<char>(row2_array, row2_array + _countof(row2_array)));
    board.push_back(vector<char>(row3_array, row3_array + _countof(row3_array)));
    board.push_back(vector<char>(row4_array, row4_array + _countof(row4_array)));
    vector<string> words;
    words.push_back("oath");
    words.push_back("pea");
    words.push_back("eat");
    words.push_back("rain");
    for (auto answer : solution.findWords(board, words))
    {
        cout << answer << endl;
    }

    return 0;
}