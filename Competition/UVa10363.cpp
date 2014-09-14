#include "stdafx.h"

// TODO

#include "UVa10363.h"

#include <iostream>
#include <string>

using namespace std;

/**
 * if (#X = #O)
 * {
 *   if (#X wins) { fail - that can't happen, since #O take the last move }
 *   else { possible - #O win the game or they are still playing }
 * }
 * else if (#X = #O + 1)
 * {
 *   if (#O wins) { fail - that can't happen since #x take the last move }
 *   else { possible - #X win the game or they are still playing }
 * }
 * else
 * {
 *   fail - this is impossible
 * }
 */

char match(char current, char next)
{
    if (current == 'u')
    {
        return next;
    }
    else if (current == next)
    {
        return next;
    }
    else
    {
        return '.';
    }
}

int UVa10363()
{
    string dummy;
    int number_of_games;
    cin >> number_of_games;
    getline(cin, dummy);
    for (int g = 0; g < number_of_games; g++)
    {
        string line0;
        string line1;
        string line2;
        getline(cin, line0);
        getline(cin, line1);
        getline(cin, line2);
        getline(cin, dummy);
        int x_count = 0;
        int o_count = 0;
        bool x_win = false;
        bool o_win = false;
        char b[3][3] = { { line0[0], line0[1], line0[2] } , { line1[0], line1[1], line1[2] }, { line2[0], line2[1], line2[2] }};
        for (int row = 0; row < 3; row++)
        {
            for (int col = 0; col < 3; col++)
            {
                x_count += b[row][col] == 'X';
                o_count += b[row][col] == 'O';
            }
        }
        for (int row = 0; row < 3; row++)
        {
            char row_char = 'u';
            for (int col = 0; col < 3; col++)
            {
                row_char = match(row_char, b[row][col]);
            }
            if (row_char == 'X')
            {
                x_win = true;
            }
            if (row_char == 'O')
            {
                o_win = true;
            }
        }
        for (int col = 0; col < 3; col++)
        {
            char col_char = 'u';
            for (int row = 0; row < 3; row++)
            {
                col_char = match(col_char, b[row][col]);
            }
            if (col_char == 'X')
            {
                x_win = true;
            }
            if (col_char == 'O')
            {
                o_win = true;
            }
        }
        char slash_char = 'u';
        slash_char = match(slash_char, b[0][0]);
        slash_char = match(slash_char, b[1][1]);
        slash_char = match(slash_char, b[2][2]);
        if (slash_char == 'X') { x_win = true; }
        if (slash_char == 'O') { o_win = true; }
        char back_slash_char = 'u';
        back_slash_char = match(back_slash_char, b[0][2]);
        back_slash_char = match(back_slash_char, b[1][1]);
        back_slash_char = match(back_slash_char, b[2][0]);
        if (back_slash_char == 'X') { x_win = true; }
        if (back_slash_char == 'O') { o_win = true; }

        if (x_count == o_count)
        {
            cout << (x_win ? "no" : "yes") << endl;
        }
        else if (x_count == o_count + 1)
        {
            cout << (o_win ? "no" : "yes") << endl;
        }
        else
        {
            cout << "no" << endl;
        }
    }

    return 0;
}