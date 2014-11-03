#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1852

#include "UVa10911.h"

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>

using namespace std;

double find_minimum_cost(int num_students, int problem, double** distance, double* memo)
{
    double result = memo[problem];
    if (result != -1)
    {
        return result;
    }
    else
    {
        vector<int> unpaired_students;
        for (int i = 0; i < num_students; i++)
        {
            int student_bit_mask = 1 << i;
            if ((problem & student_bit_mask) != 0)
            {
                unpaired_students.push_back(i);
            }
        }

        bool first = true;
        double best = -1;

        for (unsigned int i = 0; i < unpaired_students.size(); i++)
        {
            int first_bit_mask_on = 1 << unpaired_students[i];
            int first_bit_mask_off = ~(first_bit_mask_on);
            for (unsigned int j = i + 1; j < unpaired_students.size(); j++)
            {
                int second_bit_mask_on = 1 << unpaired_students[j];
                int second_bit_mask_off = ~(second_bit_mask_on);
                problem = problem & first_bit_mask_off & second_bit_mask_off;
                double candidate = find_minimum_cost(num_students, problem, distance, memo) + distance[unpaired_students[i]][unpaired_students[j]];
                problem = problem | first_bit_mask_on | second_bit_mask_on;
                if (first)
                {
                    best = candidate;
                    first = false;
                }
                else
                {
                    if (candidate < best)
                    {
                        best = candidate;
                    }
                }
            }
        }

        memo[problem] = best;
        return best;
    }
}

int UVa10911()
{
    int case_number = 1;
    while (true)
    {
        int num_pairs;
        cin >> num_pairs;
        if (num_pairs == 0)
        {
            break;
        }
        int num_students = num_pairs * 2;
        vector<pair<int, int> > student_locations;


        for (int i = 0; i < num_students; i++)
        {
            string name;
            int x;
            int y;
            cin >> name;
            cin >> x;
            cin >> y;
            student_locations.push_back(pair<int, int>(x, y));
        }
        
        // Step 1: Compute distance matrix to avoid re-computation
        double** distance = new double*[num_students];
        for (int i = 0; i < num_students; i++)
        {
            distance[i] = new double[num_students];
        }
        
        for (int i = 0; i < num_students; i++)
        {
            distance[i][i] = 0;
            for (int j = i + 1; j < num_students; j++)
            {
                double x_diff = (student_locations[i].first - student_locations[j].first);
                double y_diff = (student_locations[i].second - student_locations[j].second);
                distance[i][j] = distance[j][i] = sqrt(x_diff * x_diff + y_diff * y_diff);
            }
        }

        int table_size = 1 << num_students;
        
        double* memo = new double[table_size];
        for (int i = 0; i < table_size; i++)
        {
            // Representing the sub-problem is not solved
            memo[i] = -1;
        }
        // The sub-problem of selecting no pair is trivially solved - the cost is 0
        memo[0] = 0;

        std::cout << std::setprecision(2) << std::fixed;
        cout << "Case " << case_number << ": " << find_minimum_cost(num_students, table_size - 1, distance, memo) << endl;

        for (int i = 0; i < num_students; i++)
        {
            delete[] distance[i];
        }
        delete[] distance;
        case_number++;
    }

    return 0;
}