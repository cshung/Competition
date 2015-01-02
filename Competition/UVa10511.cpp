#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1452

// #define LOG

#include "UVa10511.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <queue>

using namespace std;

int UVa10511_assign_person_number(map<string, int>& person_numbers, map<int, string>& person_namings, string person_name);
int UVa10511_assign_party_number(map<string, int>& party_numbers, map<int, string>& party_namings, string party_name);
int UVa10511_assign_club_number(map<string, int>& club_numbers, map<int, string>& club_namings, string club_name);
int UVa10511_Edmonds_Karps(vector<vector<int>>& capacities, vector<vector<int>>& adjacency_list, int src, int dst);

int UVa10511()
{
    string line;
    int number_of_test_cases;
    cin >> number_of_test_cases;
    getline(cin, line); // consume the blank link after the number of test cases    
    getline(cin, line); // consume the blank link before the first test case
    for (int test_case = 0; test_case < number_of_test_cases; test_case++)
    {
        map<string, int> person_numbers;
        map<int, string> person_namings;
        map<string, int> party_numbers;
        map<int, string> party_namings;
        map<string, int> club_numbers;
        map<int, string> club_namings;

        vector<pair<int, int>> party_members;
        vector<pair<int, int>> person_clubs;

        while(getline(cin, line) && line != "" && line != " ")
        {
            string person_name;
            string party_name;
            string club_name;
            stringstream sin(line);
            sin >> person_name >> party_name;

            int person_id = UVa10511_assign_person_number(person_numbers, person_namings, person_name);
            int party_id = UVa10511_assign_party_number(party_numbers, party_namings, party_name);
            party_members.push_back(pair<int, int>(party_id, person_id));
            while(sin >> club_name)
            {
                int club_id = UVa10511_assign_club_number(club_numbers, club_namings, club_name);
                person_clubs.push_back(pair<int, int>(person_id, club_id));
            }   
        }
        
        int number_of_parties = party_numbers.size();
        int number_of_persons = person_numbers.size();
        int number_of_clubs = club_numbers.size();

        int number_of_nodes =
            /* master source */ 1 +
            /* parties       */ number_of_parties +
            /* person        */ number_of_persons +
            /* clubs         */ number_of_clubs +
            /* master sink   */ 1;

        vector<vector<int>> capacities;
        vector<vector<int>> adjacency_list;

        capacities.resize(number_of_nodes);
        adjacency_list.resize(number_of_nodes);

        for (int src = 0; src < number_of_nodes; src++)
        {
            capacities[src].resize(number_of_nodes);
            for (int dst = 0; dst < number_of_nodes; dst++)
            {
                capacities[src][dst] = 0;
            }
        }

        int max_party_participants = (number_of_clubs - 1) / 2; // Floor intended, not equal or more than half

        for (int p = 0; p < number_of_parties; p++)
        {
            int party_node = p + 1;
            capacities[0][party_node] = max_party_participants;
            adjacency_list[0].push_back(party_node);
            adjacency_list[party_node].push_back(0);
        }

        int person_node_start = 1 + number_of_parties;

        for (vector<pair<int, int>>::iterator pmi = party_members.begin(); pmi != party_members.end(); pmi++)
        {
            int party_id = pmi->first;
            int person_id = pmi->second;

            int party_node = party_id + 1;
            int person_node = person_node_start + person_id;

            capacities[party_node][person_node] = 1;
            adjacency_list[party_node].push_back(person_node);
            adjacency_list[person_node].push_back(party_node);
        }

        int club_node_start = 1 + number_of_parties + number_of_persons;
        for (vector<pair<int, int>>::iterator pci = person_clubs.begin(); pci != person_clubs.end(); pci++)
        {
            int person_id = pci->first;
            int club_id = pci->second;

            int person_node = person_node_start + person_id;
            int club_node = club_node_start + club_id;

            capacities[person_node][club_node] = 1;
            adjacency_list[person_node].push_back(club_node);
            adjacency_list[club_node].push_back(person_node);
        }

        for (int c = 0; c < number_of_clubs; c++)
        {
            int club_node = club_node_start + c;
            capacities[club_node][number_of_nodes - 1] = 1;
            adjacency_list[club_node].push_back(number_of_nodes - 1);
            adjacency_list[number_of_nodes - 1].push_back(club_node);
        }
        
#ifdef LOG
        cout << "digraph {" << endl;
        for (int src = 0; src < number_of_nodes; src++)
        {
            for (vector<int>::iterator di = adjacency_list[src].begin(); di != adjacency_list[src].end(); di++)
            {
                int dst = *di;
                cout << src << "->" << dst << " [label=\"" << capacities[src][dst] << "\"];" << endl;
            }
        }
        cout << "}" << endl;
#endif

        int total_flow = UVa10511_Edmonds_Karps(capacities, adjacency_list, 0, number_of_nodes - 1);

        if (test_case > 0)
        {
            cout << endl;
        }

        if (total_flow == number_of_clubs)
        {

            for (vector<pair<int, int>>::iterator pci = person_clubs.begin(); pci != person_clubs.end(); pci++)
            {
                int person_id = pci->first;
                int club_id = pci->second;

                int person_node = person_node_start + person_id;
                int club_node = club_node_start + club_id;

                if (capacities[person_node][club_node] == 0)
                {
                    cout << person_namings[person_id] << " " << club_namings[club_id] << endl;
                }
            }
        }
        else
        {
            cout << "Impossible." << endl;
        }
    }

    return 0;
}

int UVa10511_assign_party_number(map<string, int>& party_numbers, map<int, string>& party_namings, string party_name)
{
    int party_number;
    map<string, int>::iterator probe = party_numbers.find(party_name);
    if (probe == party_numbers.end())
    {
        party_number = party_numbers.size();
        party_numbers.insert(pair<string, int>(party_name, party_number));
        party_namings.insert(pair<int, string>(party_number, party_name));
    }
    else
    {
        party_number = probe->second;
    }

    return party_number;
}

int UVa10511_assign_person_number(map<string, int>& person_numbers, map<int, string>& person_namings, string person_name)
{
    int person_number;
    map<string, int>::iterator probe = person_numbers.find(person_name);
    if (probe == person_numbers.end())
    {
        person_number = person_numbers.size();
        person_numbers.insert(pair<string, int>(person_name, person_number));
        person_namings.insert(pair<int, string>(person_number, person_name));
    }
    else
    {
        person_number = probe->second;
    }

    return person_number;
}

int UVa10511_assign_club_number(map<string, int>& club_numbers, map<int, string>& club_namings, string club_name)
{
    int club_number;
    map<string, int>::iterator probe = club_numbers.find(club_name);
    if (probe == club_numbers.end())
    {
        club_number = club_numbers.size();
        club_numbers.insert(pair<string, int>(club_name, club_number));
        club_namings.insert(pair<int, string>(club_number, club_name));
    }
    else
    {
        club_number = probe->second;
    }

    return club_number;
}

int UVa10511_Edmonds_Karps(vector<vector<int>>& capacities, vector<vector<int>>& adjacency_list, int src, int dst)
{
    int total_flow = 0;
    // Step 2: Edmonds Karp's
    vector<int> parents; // Allow back-tracking the path found from bfs
    int number_of_nodes = capacities.size();
    parents.resize(number_of_nodes); // avoid reallocation
    while (true)
    {
        // Step 2.1: Use BFS to find an augmenting flow
        queue<int> bfs_queue;
        for (int n = 0; n < number_of_nodes; n++)
        {
            parents[n] = -1; // indicating the node is not enqueued
        }

        parents[src] = -2; // indicating the node is enqueued but no actual parent because this is the root
        bfs_queue.push(src);
        while (bfs_queue.size() > 0)
        {
            int current = bfs_queue.front();
            bfs_queue.pop();
            for (vector<int>::iterator ni = adjacency_list[current].begin(); ni != adjacency_list[current].end(); ni++)
            {
                int neighbor = *ni;
                if (parents[neighbor] == -1 && capacities[current][neighbor] > 0)
                {
                    parents[neighbor] = current;
                    bfs_queue.push(neighbor);

                    if (neighbor == dst)
                    {
                        break;
                    }
                }
            }
            if (parents[dst] != -1)
            {
                break;
            }
        }

        if (parents[dst] == -1)
        {
            break;
        }
        else
        {
            // We have found an augmenting path, go through the path and find the max flow through this path
            int cur = dst;
            bool first = true;
            int max_flow_through_path = 0;
            while (true)
            {
                int src = parents[cur];
                if (src != -2)
                {
                    int dst = cur;
                    int available = capacities[src][dst];
#ifdef LOG
                    cout << src << "--" << available << "->" << dst << endl;
#endif
                    cur = parents[cur];
                    if (first)
                    {
                        max_flow_through_path = available;
                        first = false;
                    }
                    else
                    {
                        max_flow_through_path = min(max_flow_through_path, available);
                    }
                }
                else
                {
                    break;
                }
            }
#ifdef LOG
            cout << "flowing " << max_flow_through_path << endl << endl;
#endif
            total_flow += max_flow_through_path;
            // Flow the max flow through the augmenting path
            cur = dst;
            while (true)
            {
                int src = parents[cur];
                if (src != -2)
                {
                    capacities[src][cur] -= max_flow_through_path;
                    capacities[cur][src] += max_flow_through_path;
                    cur = parents[cur];
                }
                else
                {
                    break;
                }
            }
        }
    }

    return total_flow;
}