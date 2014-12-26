#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1248

#include "UVa10307.h"

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>

using namespace std;

int UVa10307_find(int item, vector<int>& sets)
{
    if (sets[item] < 0)
    {
        return item;
    }
    else
    {
        return sets[item] = UVa10307_find(sets[item], sets);
    }
}

bool UVa10307_union(int item1, int item2, vector<int>& sets)
{
    int set1 = UVa10307_find(item1, sets);
    int set2 = UVa10307_find(item2, sets);
    if (set1 != set2)
    {
        // Union 
        if (sets[set1] < sets[set2])              // set1 is larger
        {
            sets[set1] = sets[set1] + sets[set2]; // size increased
            sets[set2] = set1;                    // union
        }
        else
        {
            sets[set2] = sets[set1] + sets[set2]; // size increased
            sets[set1] = set2;                    // union
        }

        return true;
    }
    else
    {
        return false;
    }
}

class UVa10307_Edge
{
public:
    UVa10307_Edge(int _src, int _dst, int _weight) : src(_src), dst(_dst), weight(_weight) {}
    int src;
    int dst;
    int weight;
};

class UVa10307_Edge_Less
{
public:
    bool operator()(UVa10307_Edge edge1, UVa10307_Edge edge2)
    {
        return edge1.weight > edge2.weight;
    }
};

int UVa10307()
{
    int number_of_test_cases;
    cin >> number_of_test_cases;
    for (int test_case = 1; test_case <=number_of_test_cases; test_case++)
    {
        int num_cols;
        int num_rows;
        cin >> num_cols;
        cin >> num_rows;
        string line;
        getline(cin, line); // consume the blank line
        vector<string> maze;
        for (int r = 0; r < num_rows; r++)
        {
            getline(cin, line);
            maze.push_back(line);
        }

        // Step 1: Find the starting point and alien points
        int sr = -1;
        int sc = -1;
        vector<pair<int, int> > aliens;

        for (int r = 0; r < num_rows; r++)
        {
            for (int c = 0; c < num_cols; c++)
            {
                if (maze[r][c] == 'S')
                {
                    sr = r;
                    sc = c;
                } else if (maze[r][c] == 'A')
                {
                    aliens.push_back(pair<int, int>(r, c));
                }
            }
        }

        // Step 2: Build the graph
        int num_nodes = num_rows * num_cols;
        vector<set<int> > adjacency_list;
        adjacency_list.resize(num_nodes);
        for (int src_row = 0; src_row < num_rows; src_row++)
        {
            for (int src_col = 0; src_col < num_rows; src_col++)
            {
                if (maze[src_row][src_col] != '#')
                {
                    vector<pair<int, int> > neighbor_candidates;
                    neighbor_candidates.push_back(pair<int, int>(src_row - 1, src_col));
                    neighbor_candidates.push_back(pair<int, int>(src_row, src_col - 1));
                    neighbor_candidates.push_back(pair<int, int>(src_row + 1, src_col));
                    neighbor_candidates.push_back(pair<int, int>(src_row, src_col + 1));
                    for (vector<pair<int, int> >::iterator nci = neighbor_candidates.begin(); nci != neighbor_candidates.end(); nci++)
                    {
                        int dst_row = nci->first;
                        int dst_col = nci->second;
                        if (0 <= dst_row && dst_row < num_rows && 0 <= dst_col && dst_col < num_cols)
                        {
                            if (maze[dst_row][dst_col] != '#')
                            {
                                int src_num = src_row * num_cols + src_col;
                                int dst_num = dst_row * num_cols + dst_col;
                                adjacency_list[src_num].insert(dst_num);
                                adjacency_list[dst_num].insert(src_num);
                            }
                        }
                    }
                }
            }
        }

        // Step 3: Find shortest path between each pairs and Kruskal's 1: Push all edges to priority queue
        int number_of_split_nodes = aliens.size() + 1;
        priority_queue<UVa10307_Edge, vector<UVa10307_Edge>, UVa10307_Edge_Less> edges;
        for (int i = 0; i < number_of_split_nodes; i++)
        {
            for (int j = i + 1; j < number_of_split_nodes; j++)
            {
                int src_row = i == 0 ? sr : aliens[i - 1].first;
                int src_col = i == 0 ? sc : aliens[i - 1].second;

                int dst_row = aliens[j - 1].first;
                int dst_col = aliens[j - 1].second;
                
                int src_num = src_row * num_cols + src_col;
                int dst_num = dst_row * num_cols + dst_col;


                // Step 3.1: Finding shortest distance by BFS
                vector<int> dist;
                queue<int> bfs_queue;
                dist.resize(num_nodes);
                for (int k = 0; k < num_nodes; k++)
                {
                    dist[k] = -1;
                }

                dist[src_num] = 0;
                bfs_queue.push(src_num);

                while (true)
                {
                    int current = bfs_queue.front();
                    bfs_queue.pop();
                    if (current == dst_num)
                    {
                        edges.push(UVa10307_Edge(i, j, dist[current]));
                        break;
                    }
                    for (set<int>::iterator ni = adjacency_list[current].begin(); ni != adjacency_list[current].end(); ni++)
                    {
                        int n = *ni;
                        if (dist[n] == -1)
                        {
                            dist[n] = dist[current] + 1;
                            bfs_queue.push(n);
                        }
                    }
                }
            }
        }

        // Step 4: Kruskal's 2: Setup disjoint set union find
        vector<int> disjoint_sets;
        disjoint_sets.resize(number_of_split_nodes);
        for (int f = 0; f < number_of_split_nodes; f++)
        {
            disjoint_sets[f] = -1;
        }

        // Step 5: Kruskal's 3: For each edge, if not create cycle, add
        int num_edge_added = 0;
        int weight = 0;
        while (num_edge_added != number_of_split_nodes - 1)
        {
            UVa10307_Edge edge = edges.top();
            edges.pop();
            if (UVa10307_union(edge.src, edge.dst, disjoint_sets))
            {
                num_edge_added++;
                weight += edge.weight;
            }
        }

        cout << weight << endl;
    }
    return 0;
}