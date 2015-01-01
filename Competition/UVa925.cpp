#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=866

#include "UVa925.h"

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int UVa925_assign_course_number(map<string, int>& course_numbers, map<int, string>& course_namings, string course_name);

int UVa925()
{
    int number_of_test_cases;
    cin >> number_of_test_cases;
    for (int test_case = 1; test_case <= number_of_test_cases; test_case++)
    {
        map<string, int> course_numbers;
        map<int, string> course_namings;
        int number_of_courses;
        cin >> number_of_courses;
        

        for (int c = 0; c < number_of_courses; c++)
        {
            string course_name;
            cin >> course_name;
            int course_id = UVa925_assign_course_number(course_numbers, course_namings, course_name);
        }

        int number_of_nodes = number_of_courses;
        vector<vector<int> > adjacency_matrix;
        vector<vector<int> > adjacency_list;
        vector<vector<bool> > reachable;
        reachable.resize(number_of_nodes);
        adjacency_matrix.resize(number_of_nodes);
        adjacency_list.resize(number_of_nodes);
        for (int src = 0; src < number_of_nodes; src++)
        {
            adjacency_matrix[src].resize(number_of_nodes);
            reachable[src].resize(number_of_nodes);
            for (int dst = 0; dst < number_of_courses; dst++)
            {
                adjacency_matrix[src][dst] = 0;
                reachable[src][dst] = false;
            }
        }

        int number_of_courses_with_prerequisite;
        cin >> number_of_courses_with_prerequisite;
        for (int c = 0; c < number_of_courses_with_prerequisite; c++)
        {
            string src_course_name;
            cin >> src_course_name;
            int src_course_id = course_numbers[src_course_name];
            int number_of_prerequisites;
            cin >> number_of_prerequisites;
            for (int p = 0; p < number_of_prerequisites; p++)
            {
                string dst_course_name;
                cin >> dst_course_name;
                int dst_course_id = course_numbers[dst_course_name];
                adjacency_matrix[src_course_id][dst_course_id] = 1;
                reachable[src_course_id][dst_course_id] = true;
                adjacency_list[src_course_id].push_back(dst_course_id);
            }
        }

        for (int k = 0; k < number_of_nodes; k++)
        {
            for (int src = 0; src < number_of_nodes; src++)
            {
                for (int dst = 0; dst < number_of_nodes; dst++)
                {
                    if (reachable[src][k] && reachable[k][dst]) // relaxation is possible if the proposal is valid
                    {
                        reachable[src][dst] = true;
                    }
                }
            }
        }

        map<string, vector<string>> output;
        for (unsigned int src = 0; src < adjacency_list.size(); src++)
        {
            vector<string> real_prerequisties;
            for (unsigned int dst_index = 0; dst_index < adjacency_list[src].size(); dst_index++)
            {
                int dst = adjacency_list[src][dst_index];
                bool skippable = false;
                for (unsigned int other_dst_index = 0; other_dst_index < adjacency_list[src].size(); other_dst_index++)
                {
                    if (dst_index != other_dst_index)
                    {
                        int other_dst = adjacency_list[src][other_dst_index];
                        if (reachable[other_dst][dst])
                        {
                            skippable = true;
                            break;
                        }
                    }
                }
                if (!skippable)
                {
                    real_prerequisties.push_back(course_namings[dst]);   
                }
            }
            if (real_prerequisties.size() > 0)
            {
                sort(real_prerequisties.begin(), real_prerequisties.end());
                output.insert(pair<string, vector<string>>(course_namings[src], real_prerequisties));
            }
        }

        for (map<string, vector<string>>::iterator oi = output.begin(); oi != output.end(); oi++)
        {
            cout << oi->first << " " << oi->second.size();
            for (vector<string>::iterator pi = oi->second.begin(); pi != oi->second.end(); pi++)
            {
                cout << " " << *pi;
            }
            cout << endl;
        }
    }

    return 0;
}

int UVa925_assign_course_number(map<string, int>& course_numbers, map<int, string>& course_namings, string course_name)
{
    int course_number;
    map<string, int>::iterator probe = course_numbers.find(course_name);
    if (probe == course_numbers.end())
    {
        course_number = course_numbers.size();
        course_numbers.insert(pair<string, int>(course_name, course_number));
        course_namings.insert(pair<int, string>(course_number, course_name));
    }
    else
    {
        course_number = probe->second;
    }

    return course_number;
}