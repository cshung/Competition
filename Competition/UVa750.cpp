#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=691

#include "UVa750.h"

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

// Global variable
int row_of_column[8];
int solution_count;

void queens(int workingColumn)
{
    if (workingColumn == 8)
    {
        // We have got an answer!
        
        // Good for debugging outputing the matrix
        /*
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (i == row_of_column[j])
                {
                    cout << "1 ";
                }
                else
                {
                    cout << "0 ";
                }
            }
            cout << endl;
        }
        cout << endl;
        */

        cout << setw(2)      // : gives a minimum width for the next output operation
            << setfill(' ')  // : sets the padding character
            << setiosflags(ios::right); // : padding on left

        cout << (++solution_count);
        cout << "     ";
        for (int i = 0; i < 8; i++)
        {
            cout << " " << (row_of_column[i] + 1);
        }
        cout << endl;

        return;
    }
    
    // If the working column is not already assigned
    if (row_of_column[workingColumn] == -1) 
    {
        for (int trial = 0; trial < 8; trial++)
        {
            bool bad = false;
            for (int test = 0; test < 8; test++)
            {
                // The coordinate of the testing column element is (row_of_column[test], test)
                // The proposed coordiate is (trial, workingColumn)
                if (row_of_column[test] != -1)
                {
                    if (row_of_column[test] == trial || abs(test - workingColumn) == abs(row_of_column[test] - trial))
                    {
                        bad = true;
                    }
                }
            }

            if (!bad)
            {
                row_of_column[workingColumn] = trial;
                queens(workingColumn + 1);
                row_of_column[workingColumn] = -1;
            }
        }
    }
    else
    {
        queens(workingColumn + 1);
    }
}

int UVa750()
{
    int number_of_cases;
    cin >> number_of_cases;

    for (int c = 0; c < number_of_cases; c++)
    {
        // Step 1: Read inputs
        int row_number;
        int col_number;
        cin >> row_number;
        cin >> col_number;

        // Step 2: Reset global state
        for (int i = 0; i < 8; i++)
        {
            row_of_column[i] = -1;
        }
        solution_count = 0;

        // Step 3: Add constraint
        row_of_column[col_number - 1] = row_number - 1;

        // Step 4: Print header
        if (c != 0)
        {
            cout << endl;
        }
        cout << "SOLN       COLUMN" << endl;
        cout << " #      1 2 3 4 5 6 7 8" << endl;
        cout << endl;

        // Step 5: Search
        queens(0);
    }

    return 0;
}