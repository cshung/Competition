#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=122

#include "UVa186.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

void UVa186_split(string line, string* parts);
int UVa186_assign_city_number(map<string, int>& city_numbers, map<int, string>& city_namings, string city_name);

int UVa186()
{
    map<string, int> city_numbers;
    map<int, string> city_namings;
    map<pair<int, int>, string> edge_namings;
    vector<pair<pair<int, int>, int> > edges;
    vector<pair<int, int> > queries;

    // Step 1: Read inputs
    
    string line;
    getline(cin, line);
    do
    {
        string parts[4];
        UVa186_split(line, parts);

        string src = parts[0];
        string dst = parts[1];
        string route = parts[2];
        int cost = stoi(parts[3]);

        int src_id = UVa186_assign_city_number(city_numbers, city_namings, src);
        int dst_id = UVa186_assign_city_number(city_numbers, city_namings, dst);

        if (dst_id < src_id)
        {
            int temp = src_id;
            src_id = dst_id;
            dst_id = temp;
        }

        pair<int, int> edge(src_id, dst_id);
        edge_namings.insert(pair<pair<int, int>, string>(edge, route));
        edges.push_back(pair<pair<int, int>, int>(edge, cost));

        getline(cin, line);
    }
    while (line != "");

    getline(cin, line);
    while (true)
    {
        string parts[2];
        UVa186_split(line, parts);
        queries.push_back(pair<int, int>(city_numbers[parts[0]], city_numbers[parts[1]]));

        if (cin.eof())
        {
            break;
        }

        getline(cin, line);

        if (line == "")
        {
            break;
        }
    }

    // Step 2: Produce the data structures for Floyd Warshall
    int number_of_nodes = city_numbers.size();

    vector<vector<int> > adjacency_matrix;
    vector<vector<int> > distances;
    vector<vector<bool> > reachable;
    vector<vector<int> > path;
    adjacency_matrix.resize(number_of_nodes);
    distances.resize(number_of_nodes);
    reachable.resize(number_of_nodes);
    path.resize(number_of_nodes);
    for (int src = 0; src < number_of_nodes; src++)
    {
        adjacency_matrix[src].resize(number_of_nodes);
        distances[src].resize(number_of_nodes);
        reachable[src].resize(number_of_nodes);
        path[src].resize(number_of_nodes);

        for (int dst = 0; dst < number_of_nodes; dst++)
        {
            adjacency_matrix[src][dst] = 0;
            distances[src][dst] = -1;
            reachable[src][dst] = false;
            path[src][dst] = -1;
        }
    }

    for (unsigned int e = 0; e < edges.size(); e++)
    {
        pair<pair<int, int>, int> edge = edges[e];
        int src = edge.first.first;
        int dst = edge.first.second;
        int cost = edge.second;

        // The input has multiple edges!
        if (adjacency_matrix[src][dst] == 0 || cost < adjacency_matrix[src][dst])
        {
            adjacency_matrix[src][dst] = cost;
            distances[src][dst] = cost;
            reachable[src][dst] = true;
            path[src][dst] = dst;

            adjacency_matrix[dst][src] = cost;
            distances[dst][src] = cost;
            reachable[dst][src] = true;
            path[dst][src] = src;
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
                    int current_distance = distances[src][dst];
                    int propose_distance = distances[src][k] + distances[k][dst];
                    if (!reachable[src][dst] || propose_distance < current_distance)
                    {
                        distances[src][dst] = propose_distance;
                        reachable[src][dst] = true;
                        path[src][dst] = path[src][k];
                    }
                }
            }
        }
    }

    
    for (unsigned int q = 0; q < queries.size(); q++)
    {
        pair<int, int> query = queries[q];
        int src = query.first;
        int dst = query.second;

        cout << endl;
        cout << endl;

        cout << "From                 To                   Route      Miles" << endl;
        cout << "-------------------- -------------------- ---------- -----" << endl;

        int cur = src;
        while (true)
        {
            int path_src_id = cur;
            int path_dst_id = path[cur][dst];
            string path_src_name = city_namings[path_src_id];
            string path_dst_name = city_namings[path_dst_id];

            int edge_src_id = min(path_src_id, path_dst_id);
            int edge_dst_id = max(path_src_id, path_dst_id);

            string route = edge_namings[pair<int, int>(edge_src_id, edge_dst_id)];
            while (path_src_name.length() < 20)
            {
                path_src_name += ' ';
            }
            while (path_dst_name.length() < 20)
            {
                path_dst_name += ' ';
            }
            while (route.length() < 10)
            {
                route += ' ';
            }

            cout << path_src_name << " " << path_dst_name << " " << route << " ";
            cout << right << setw(5) << adjacency_matrix[path_src_id][path_dst_id] << endl;

            cur = path_dst_id;
            if (cur == dst)
            {
                break;
            }
        }
        cout << "                                                     -----" << endl;
        cout << "                                          Total      ";
        cout << right << setw(5) << distances[src][dst] << endl;
    }


    return 0;
}

void UVa186_split(string line, string* parts)
{
    string* current_part = parts;
    for (unsigned int i = 0; i < line.length(); i++)
    {
        if (line[i] != ',')
        {
            (*current_part) += line[i];
        }
        else
        {
            current_part++;
        }
    }
}

int UVa186_assign_city_number(map<string, int>& city_numbers, map<int, string>& city_namings, string city_name)
{
    int city_number;
    map<string, int>::iterator probe = city_numbers.find(city_name);
    if (probe == city_numbers.end())
    {
        city_number = city_numbers.size();
        city_numbers.insert(pair<string, int>(city_name, city_number));
        city_namings.insert(pair<int, string>(city_number, city_name));
    }
    else
    {
        city_number = probe->second;
    }

    return city_number;
}