#include "stdafx.h"

// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=15&page=show_problem&problem=1311

#include "UVa10397.h"
#include <iostream>
#include <vector>
using namespace std;

int UVa10370()
{
    int number_of_test_cases;
    cin >> number_of_test_cases;
    for (int t = 0; t < number_of_test_cases; t++)
    {
        int number_of_students;
        vector<int> grades;
        int total_score;
        int number_of_above_average_students;
        cin >> number_of_students;
        double percentage;

        grades.resize(number_of_students);
        total_score = 0;
        number_of_above_average_students = 0;
        for (int s = 0; s < number_of_students; s++)
        {
            cin >> grades[s];
            total_score += grades[s];
        }
        for (int s = 0; s < number_of_students; s++)
        {
            if (grades[s] * number_of_students > total_score)
            {
                number_of_above_average_students++;
            }
        }
        percentage = number_of_above_average_students * 100.0 / number_of_students;
        cout.setf(ios::fixed,ios::floatfield);
        cout.precision(3);
        cout << percentage << "%" << endl;
    }
    return 0;
}