#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=580

#include "UVa639.h"

#include <iostream>
#include <list>
#include <vector>
#include <algorithm>

using namespace std;

struct position
{
    int row;
    int col;
    bool occupied;
    list<position*> captures;
};

void find_configurations(vector<position*>& blank_positions, int placed, int& max_configuration)
{
    bool found = false;
    // Step 3.1: Finding a blank position
    for (vector<position*>::iterator bi = blank_positions.begin(); bi != blank_positions.end(); bi++)
    {
        position* current = *bi;
        if (!current->occupied)
        {
            // Step 3.2: Trying the current position
            current->occupied = true;
            found = true;

            // Step 3.3: Capture - and remember only the list we change the flag (we don't want to uncapture those that we don't)
            list<position*> captured_now;
            for (list<position*>::iterator ci = current->captures.begin(); ci != current->captures.end(); ci++)
            {
                position* try_capture_now = *ci;
                if (!try_capture_now->occupied)
                {
                    captured_now.push_back(try_capture_now);
                    try_capture_now->occupied = true;
                }
            }
            find_configurations(blank_positions, placed + 1, max_configuration);
            
            // Step 3.4: Undo the move and try another one
            for (list<position*>::iterator ri = captured_now.begin(); ri != captured_now.end(); ri++)
            {
                (*ri)->occupied = false;
            }
            current->occupied = false;
        }
    }
    if (!found)
    {
        // Step 3.5: There is no way to place more rooks - this is a maximal configuration
        max_configuration = max(placed, max_configuration);
    }
}

int UVa639()
{
    while (true)
    {
        // Step 1: Read input
        int board_size;
        cin >> board_size;
        if (board_size == 0)
        {
            break;
        }
        char board[4][4];
        for (int i = 0; i < board_size; i++)
        {
            for (int j = 0; j < board_size; j++)
            {
                cin >> board[i][j];
            }
        }

        // Step 2: Build the capture graph

        // Step 2.1: Build the positions
        position positions[4][4];
        vector<position*> blank_position;
        for (int i = 0; i < board_size; i++)
        {
            for (int j = 0; j < board_size; j++)
            {
                positions[i][j].row = i;
                positions[i][j].col = j;
                positions[i][j].occupied = (board[i][j] == 'X');
                if (!positions[i][j].occupied)
                {
                    blank_position.push_back(&positions[i][j]);
                }
            }
        }

        // Step 2.2: Deduce capture relationship
        for (unsigned int i = 0; i < blank_position.size(); i++)
        {
            for (unsigned int j = i + 1; j < blank_position.size(); j++)
            {
                if (blank_position[i]->row == blank_position[j]->row)
                {
                    int row = blank_position[i]->row;
                    int minCol = min(blank_position[i]->col, blank_position[j]->col);
                    int maxCol = max(blank_position[i]->col, blank_position[j]->col);
                    bool capture = true;
                    for (int c = minCol; c <= maxCol; c++)
                    {
                        if (board[row][c] == 'X')
                        {
                            capture = false;
                        }
                    }
                    if (capture)
                    {
                        blank_position[i]->captures.push_back(blank_position[j]);
                        blank_position[j]->captures.push_back(blank_position[i]);
                    }
                }
                else if (blank_position[i]->col == blank_position[j]->col)
                {
                    int col = blank_position[i]->col;
                    int minRow = min(blank_position[i]->row, blank_position[j]->row);
                    int maxRow = max(blank_position[i]->row, blank_position[j]->row);
                    bool capture = true;
                    for (int r = minRow; r <= maxRow; r++)
                    {
                        if (board[r][col] == 'X')
                        {
                            capture = false;
                        }
                    }
                    if (capture)
                    {
                        blank_position[i]->captures.push_back(blank_position[j]);
                        blank_position[j]->captures.push_back(blank_position[i]);
                    }
                }
            }
        }

        // Step 3: Recursive backtracking in action
        int max_configuration = -1;
        find_configurations(blank_position, 0, max_configuration);
        cout << max_configuration << endl;
    }

    return 0;
}