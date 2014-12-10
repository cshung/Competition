#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=196

#include "UVa260.h"

#include <iostream>
#include <vector>
#include <map>
#include <queue>

using namespace std;

int UVa260()
{
    int test_case_number = 0;
    while (true)
    {
        test_case_number++;
        // Step 1: Performing inputs
        int dimension;
        cin >> dimension;
        if (dimension == 0)
        {
            break;
        }
        vector<vector<char> > board;
        board.resize(dimension);
        for (int row = 0; row < dimension; row++)
        {
            board[row].resize(dimension);
            for (int col = 0; col < dimension; col++)
            {
                cin >> board[row][col];
            }
        }

        // Step 2: Build the graphs


        vector<vector<int> > black_graph;
        int num_nodes = dimension * dimension + 2;
        int goal = num_nodes - 1;
        black_graph.resize(num_nodes);

        for (int col = 0; col < dimension; col++)
        {
            if (board[0][col] == 'b')
            {
                int node_id = col + 1;
                black_graph[0].push_back(node_id);
                black_graph[node_id].push_back(0);
            }
            if (board[dimension - 1][col] == 'b')
            {
                int node_id = goal - dimension + col; // 17 - 4 + [0-3] = 13 - 16
                black_graph[goal].push_back(node_id);
                black_graph[node_id].push_back(goal);
            }
        }

        /*
        ( i-1 , j-1 ) , ( i-1 ,  j  )
        (  i  , j-1 ) , (  i  , j+1 )
        ( i+1 ,  j  ) , ( i+l , j+1 )
        */
        for (int src_row = 0; src_row < dimension; src_row++)
        {
            for (int src_col = 0; src_col < dimension; src_col++)
            {
                if (board[src_row][src_col] == 'b')
                {
                    vector<pair<int, int> > candidates;
                    candidates.push_back(pair<int, int>(src_row - 1, src_col - 1));
                    candidates.push_back(pair<int, int>(src_row - 1, src_col));
                    candidates.push_back(pair<int, int>(src_row, src_col - 1));
                    candidates.push_back(pair<int, int>(src_row, src_col + 1));
                    candidates.push_back(pair<int, int>(src_row + 1, src_col));
                    candidates.push_back(pair<int, int>(src_row + 1, src_col + 1));
                    for (int c = 0; c < 6; c++)
                    {
                        int dst_row = candidates[c].first;
                        int dst_col = candidates[c].second;
                        if (0 <= dst_row && dst_row < dimension)
                        {
                            if (0 <= dst_col && dst_col < dimension)
                            {
                                if (board[dst_row][dst_col] == 'b')
                                {
                                    int src_id = src_row * dimension + src_col + 1;
                                    int dst_id = dst_row * dimension + dst_col + 1;

                                    // It is possible to have multiple edges, but we don't care
                                    black_graph[src_id].push_back(dst_id);
                                    black_graph[dst_id].push_back(src_id);
                                }
                            }
                        }
                    }
                }
            }
        }
#ifdef LOG
        // Debug dump the graph
        for (unsigned int i = 0; i < black_graph.size(); i++)
        {
            cout << i << ":";
            for (unsigned int j = 0; j < black_graph[i].size(); j++)
            {
                cout << " " << black_graph[i][j];
            }
            cout << endl;
        }
#endif
        vector<bool> enqueued;
        enqueued.resize(num_nodes);
        for (int i = 0; i < num_nodes; i++)
        {
            enqueued[i] = false;
        }

        queue<int> bfs_queue;
        bfs_queue.push(0);

        while (bfs_queue.size() > 0)
        {
            int current = bfs_queue.front();
            bfs_queue.pop();
            for (unsigned int neighbor_index = 0; neighbor_index < black_graph[current].size(); neighbor_index++)
            {
                int neighbor = black_graph[current][neighbor_index];
                if (!enqueued[neighbor])
                {
                    enqueued[neighbor] = true;
                    bfs_queue.push(neighbor);
                }
            }
        }

        if (enqueued[goal])
        {
            cout << test_case_number << " B" << endl;
        }
        else
        {
            cout << test_case_number << " W" << endl;
        }

    }
    return 0;
}