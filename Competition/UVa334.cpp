#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=270

#include "UVa334.h"

#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

int UVa334_assign_event_number(map<string, int>& event_numbers, map<int, string>& event_namings, string event_name);

int UVa334()
{
    int test_case = 0;
    while (true)
    {
        test_case++;
        map<string, int> event_numbers;
        map<int, string> event_namings;
        vector<pair<int, int>> event_dependencies;
        int number_of_computations;
        cin >> number_of_computations;
        if (number_of_computations == 0)
        {
            break;
        }
        for (int c = 0; c < number_of_computations; c++)
        {
            int number_of_events;
            cin >> number_of_events;
            vector<int> events;
            events.resize(number_of_events);
            for (int e = 0; e < number_of_events; e++)
            {
                string event_name;
                cin >> event_name;
                int event_id = UVa334_assign_event_number(event_numbers, event_namings, event_name);
                events[e] = event_id;
            }

            for (int e = 1; e < number_of_events; e++)
            {
                event_dependencies.push_back(pair<int, int>(events[e - 1], events[e]));
            }
        }

        int number_of_messages;
        cin >> number_of_messages;
        for (int m = 0; m < number_of_messages; m++)
        {
            string src_event_name;
            string dst_event_name;
            cin >> src_event_name;
            cin >> dst_event_name;
            int src_event_id = event_numbers[src_event_name]; 
            int dst_event_id = event_numbers[dst_event_name];
            event_dependencies.push_back(pair<int, int>(src_event_id, dst_event_id));
        }

        // Step 2: Produce the data structures for Floyd Warshall
        int number_of_nodes = event_numbers.size();

        vector<vector<int> > adjacency_matrix;
        vector<vector<bool> > reachable;
        adjacency_matrix.resize(number_of_nodes);
        reachable.resize(number_of_nodes);
        for (int src = 0; src < number_of_nodes; src++)
        {
            adjacency_matrix[src].resize(number_of_nodes);
            reachable[src].resize(number_of_nodes);
            for (int dst = 0; dst < number_of_nodes; dst++)
            {
                adjacency_matrix[src][dst] = 0;
                reachable[src][dst] = false;
            }
        }

        for (unsigned int e = 0; e < event_dependencies.size(); e++)
        {
            pair<int, int> edge = event_dependencies[e];
            int src = edge.first;
            int dst = edge.second;

            adjacency_matrix[src][dst] = 1;
            reachable[src][dst] = true;
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

        vector<pair<int, int>> concurrent_events;
        int number_of_all_concurrent_events = 0;
        for (int src = 0; src < number_of_nodes; src++)
        {
            for (int dst = src + 1; dst < number_of_nodes; dst++)
            {
                if (!reachable[src][dst] && !reachable[dst][src])
                {
                    number_of_all_concurrent_events++;
                    if (concurrent_events.size() < 2)
                    {
                        concurrent_events.push_back(pair<int, int>(src, dst));
                    }
                }
            }
        }

        cout << "Case " << test_case << ", ";
        if (number_of_all_concurrent_events > 0)
        {
            cout << number_of_all_concurrent_events << " concurrent events:" << endl;
            if (number_of_all_concurrent_events == 1)
            {
                cout << "(" << event_namings[concurrent_events[0].first] << "," << event_namings[concurrent_events[0].second] << ") " << endl;
            }
            else
            {
                cout << "(" << event_namings[concurrent_events[0].first] << "," << event_namings[concurrent_events[0].second] << ") (" << event_namings[concurrent_events[1].first] << "," << event_namings[concurrent_events[1].second] << ") " << endl;
            }
        }
        else
        {
             cout << "no concurrent events." << endl;
        }

    }

    return 0;
}


int UVa334_assign_event_number(map<string, int>& event_numbers, map<int, string>& event_namings, string event_name)
{
    int event_number;
    map<string, int>::iterator probe = event_numbers.find(event_name);
    if (probe == event_numbers.end())
    {
        event_number = event_numbers.size();
        event_numbers.insert(pair<string, int>(event_name, event_number));
        event_namings.insert(pair<int, string>(event_number, event_name));
    }
    else
    {
        event_number = probe->second;
    }

    return event_number;
}