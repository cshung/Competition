#include "stdafx.h"

// http://uva.onlinejudge.org/external/114/11462.html

#include "UVa11462.h"

#include <iostream>

using namespace std;

int UVa11462()
{
    while (true)
    {
        int number_of_persons;
        cin >> number_of_persons;
        if (number_of_persons == 0)
        {
            break;
        }
        int num_person_with_age[100];
        for (int i = 0; i < 100; i++)
        {
            num_person_with_age[i] = 0;
        }
        for (int i = 0; i < number_of_persons; i++)
        {
            int age;
            cin >> age;
            num_person_with_age[age]++;
        }
        int k = 0;
        for (int i = 0; i < 100; i++)
        {
            for (int j = 0; j < num_person_with_age[i]; j++)
            {
                k++;
                cout << i;
                if (k != number_of_persons)
                {
                    cout << " ";
                }
            }
        }
        cout << endl;
    }

    return 0;
}