#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=235

#include "UVa299.h"

#include <iostream>

using namespace std;

// The minimal number of swaps to take a number from right to left is the distance
// Insertion sort achieved that bound.

int UVa299()
{
    int number_of_cases;
    cin >> number_of_cases;
    for (int c = 0; c < number_of_cases; c++)
    {
        int number_of_carriages;
        cin >> number_of_carriages;
        int* carriages = new int[number_of_carriages];
        for (int ca = 0; ca < number_of_carriages; ca++)
        {
            cin >> carriages[ca];
        }

        int num_swap = 0;
        for (int i = 1; i < number_of_carriages; i++)
        {
            for (int j = i; j > 0; j--)
            {
                if (carriages[j] < carriages[j-1])
                {
                    int temp = carriages[j];
                    carriages[j] = carriages[j-1];
                    carriages[j-1] = temp;
                    num_swap++;

                }
            }
        }
        cout << "Optimal train swapping takes " << num_swap << " swaps." << endl;

        delete[] carriages;
    }
    return 0;
}