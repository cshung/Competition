#include "stdafx.h"

// https://leetcode.com/problems/network-delay-time

#include "LEET_NETWORK_DELAY_TIME.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_NETWORK_DELAY_TIME
{
    class Solution
    {
    public:
        int networkDelayTime(vector<vector<int>>& times, int N, int K)
        {
            vector<int> heap;
            vector<int> node_to_heap_index;
            vector<int> heap_to_node_index;
            vector<bool> visited;
            int heap_size;
            vector<vector<pair<int, int>>> adjacency_list;

            // Step 1: Build the graph
            adjacency_list.resize(N);
            for (size_t i = 0; i < times.size(); i++)
            {
                // Make the node number start from 0
                int src = times[i][0] - 1;
                int dst = times[i][1] - 1;
                int time = times[i][2];
                adjacency_list[src].push_back(make_pair(dst, time));
            }

            // Step 2: Initialize the Dijkstra's algorithm
            heap.resize(N);
            node_to_heap_index.resize(N);
            heap_to_node_index.resize(N);
            visited.resize(N);
            for (int i = 0; i < N; i++)
            {
                visited[i] = false;
                node_to_heap_index[i] = -1;
            }

            heap[0] = 0;
            node_to_heap_index[K - 1] = 0;
            heap_to_node_index[0] = K - 1;
            heap_size = 1;
            
            int visit_count = 0;
            int last_visit_time;

            while (heap_size > 0)
            {
                int visiting_node = heap_to_node_index[0];
                int visiting_time = heap[0];
                visited[visiting_node] = true;
                last_visit_time = visiting_time;
                visit_count++;

                int last_node = heap_to_node_index[heap_size - 1];
                int last_time = heap[heap_size - 1];

                heap_size--;
                heap_to_node_index[0] = last_node;
                node_to_heap_index[last_node] = 0;
                heap[0] = last_time;

                int stone_heap_index = 0;
                while (true)
                {
                    bool swapped = false;
                    int stone_node = heap_to_node_index[stone_heap_index];
                    int stone_time = heap[stone_heap_index];
                    int left_heap_index = (stone_heap_index + 1) * 2 - 1;
                    int right_heap_index = left_heap_index + 1;
                    if (right_heap_index < heap_size)
                    {
                        int left_time = heap[left_heap_index];
                        int left_node = heap_to_node_index[left_heap_index];
                        int right_time = heap[right_heap_index];
                        int right_node = heap_to_node_index[right_heap_index];
                        if (left_time < right_time)
                        {
                            if (left_time < stone_time)
                            {
                                node_to_heap_index[stone_node] = left_heap_index;
                                heap_to_node_index[left_heap_index] = stone_node;
                                heap[left_heap_index] = stone_time;

                                node_to_heap_index[left_node] = stone_heap_index;
                                heap_to_node_index[stone_heap_index] = left_node;
                                heap[stone_heap_index] = left_time;

                                stone_heap_index = left_heap_index;
                                swapped = true;
                            }
                        }
                        else
                        {
                            if (right_time < stone_time)
                            {
                                node_to_heap_index[stone_node] = right_heap_index;
                                heap_to_node_index[right_heap_index] = stone_node;
                                heap[right_heap_index] = stone_time;

                                node_to_heap_index[right_node] = stone_heap_index;
                                heap_to_node_index[stone_heap_index] = right_node;
                                heap[stone_heap_index] = right_time;

                                stone_heap_index = right_heap_index;
                                swapped = true;
                            }
                        }
                    }
                    else if (left_heap_index < heap_size)
                    {
                        int left_time = heap[left_heap_index];
                        int left_node = heap_to_node_index[left_heap_index];
                        if (left_time < stone_time)
                        {
                            node_to_heap_index[stone_node] = left_heap_index;
                            heap_to_node_index[left_heap_index] = stone_node;
                            heap[left_heap_index] = stone_time;

                            node_to_heap_index[left_node] = stone_heap_index;
                            heap_to_node_index[stone_heap_index] = left_node;
                            heap[stone_heap_index] = left_time;

                            stone_heap_index = left_heap_index;
                            swapped = true;
                        }
                    }
                    if (!swapped)
                    {
                        break;
                    }
                }

                for (auto neighbor : adjacency_list[visiting_node])
                {
                    int neighbor_node = neighbor.first;
                    int neighbor_dist = neighbor.second;
                    int neighbor_time = visiting_time + neighbor_dist;
                    if (!visited[neighbor_node])
                    {
                        int bubble_heap_index;
                        if (node_to_heap_index[neighbor_node] == -1)
                        {
                            heap[heap_size] = neighbor_time;
                            heap_to_node_index[heap_size] = neighbor_node;
                            node_to_heap_index[neighbor_node] = heap_size;
                            
                            heap_size++;
                            bubble_heap_index = heap_size - 1;
                        }
                        else
                        {
                            bubble_heap_index = node_to_heap_index[neighbor_node];
                            if (heap[bubble_heap_index] > neighbor_time)
                            {
                                heap[bubble_heap_index] = neighbor_time;
                            }
                        }
                        while (true)
                        {
                            bool swapped = false;
                            if (bubble_heap_index > 0)
                            {
                                int bubble_node = heap_to_node_index[bubble_heap_index];
                                int bubble_time = heap[bubble_heap_index];
                                int parent_heap_index = bubble_heap_index / 2;
                                int parent_node = heap_to_node_index[parent_heap_index];
                                int parent_time = heap[parent_heap_index];
                                if (bubble_time < parent_time)
                                {
                                    node_to_heap_index[bubble_node] = parent_heap_index;
                                    heap_to_node_index[parent_heap_index] = bubble_node;
                                    heap[parent_heap_index] = bubble_time;

                                    node_to_heap_index[parent_node] = bubble_heap_index;
                                    heap_to_node_index[bubble_heap_index] = parent_node;
                                    heap[bubble_heap_index] = parent_time;

                                    bubble_heap_index = parent_heap_index;
                                    swapped = true;
                                }
                            }
                            if (!swapped)
                            {
                                break;
                            }
                        }
                    }
                }
            }
            if (visit_count == N)
            {
                return last_visit_time;
            }
            else
            {
                return -1;
            }
        }
    };
};

using namespace _LEET_NETWORK_DELAY_TIME;

int LEET_NETWORK_DELAY_TIME()
{
    // [[2,1,1],[2,3,1],[3,4,1]]
    Solution solution;
    vector<vector<int>> problem;
    problem.resize(3);
    problem[0].push_back(2);    problem[0].push_back(1);    problem[0].push_back(1);
    problem[1].push_back(2);    problem[1].push_back(3);    problem[1].push_back(1);
    problem[2].push_back(3);    problem[2].push_back(4);    problem[2].push_back(1);
    cout << solution.networkDelayTime(problem, 4, 2) << endl;
    return 0;
}