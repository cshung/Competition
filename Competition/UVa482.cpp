#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=423

#include "UVa482.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int UVa482()
{
    string dummy;
    int number_of_cases;
    cin >> number_of_cases;
    getline(cin, dummy);

    for (int c = 0; c < number_of_cases; c++)
    {
        getline(cin, dummy);
        vector<int> input_indices;
        vector<string> values;
        int current = 0;
        while (true)
        {
            char ch = cin.get();
            if (ch != ' ' && ch != '\n')
            {
                current = current * 10 + (ch - '0');
            } 
            else 
            {
                input_indices.push_back(current);
                current = 0;
                if (ch == '\n')
                {
                    break;
                }
            }
        }
        for (unsigned int i = 0; i < input_indices.size(); i++)
        {
            string value;
            cin >> value;
            values.push_back(value);
        }
        getline(cin, dummy);

        vector<int> output_indice;
        output_indice.resize(input_indices.size());

        int count = 0;
        for (vector<int>::iterator i = input_indices.begin(); i != input_indices.end(); i++)
        {
            output_indice[(*i) - 1] = count++;
        }

        for (vector<int>::iterator i = output_indice.begin(); i != output_indice.end(); i++)
        {
            cout << values[*i] << endl;
        }

        if (c != number_of_cases - 1)
        {
            cout << endl;
        }
    }

    return 0;
}