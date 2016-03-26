#include "stdafx.h"

// https://leetcode.com/problems/the-skyline-problem/

#include "LEET_THE_SKYLINE_PROBLEM.h"
#include <algorithm>
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_THE_SKYLINE_PROBLEM
{
    class Solution
    {
    private:
        class event_comparer
        {
        public:
            event_comparer(vector<vector<int>>& buildings) : m_buildings(buildings) {}
            bool operator() (pair<int, bool> i, pair<int, bool> j)
            {
                int ix = i.second ? this->m_buildings[i.first][0] : this->m_buildings[i.first][1];
                int jx = j.second ? this->m_buildings[j.first][0] : this->m_buildings[j.first][1];
                return ix < jx;
            }
        private:
            vector<vector<int>>& m_buildings;
        };

        class status
        {
        public:
            status(vector<vector<int>>& buildings) : m_buildings(buildings), m_heap_size(0)
            {
                this->m_heap.resize(buildings.size());
                this->m_building_heap_index.resize(buildings.size());
            }

            void insert(int building_index)
            {
                this->m_heap[this->m_heap_size] = building_index;
                this->m_building_heap_index[building_index] = this->m_heap_size;
                this->m_heap_size++;
                this->bubble_up(this->m_heap_size - 1);
            }

            void remove(int building_index)
            {
                int heap_index = this->m_building_heap_index[building_index];
                int last_building = this->m_heap[this->m_heap_size - 1];

                this->m_heap_size--;

                if (building_index == last_building)
                {
                    return;
                }

                this->m_heap[heap_index] = last_building;
                this->m_building_heap_index[last_building] = heap_index;

                if (this->m_heap_size > 0)
                {
                    this->bubble_down(heap_index);
                }
            }

            void bubble_up(int current_index)
            {
                if (current_index == 0)
                {
                    return;
                }

                int parent_index = (current_index + 1) / 2 - 1;
                int current_building = this->m_heap[current_index];
                int parent_building = this->m_heap[parent_index];
                int current_building_height = this->m_buildings[current_building][2];
                int parent_building_height = this->m_buildings[parent_building][2];
                if (current_building_height > parent_building_height)
                {
                    swap(this->m_heap[current_index], this->m_heap[parent_index]);
                    swap(this->m_building_heap_index[current_building], this->m_building_heap_index[parent_building]);
                    this->bubble_up(parent_index);
                }
            }

            void bubble_down(int current_index)
            {
                int right_child_index = (current_index + 1) * 2;
                int left_child_index = right_child_index - 1;

                int current_building = this->m_heap[current_index];
                int current_building_height = this->m_buildings[current_building][2];

                int max_index = current_index;
                int max_building = current_building;
                int max_height = current_building_height;
                if (left_child_index < this->m_heap_size)
                {
                    int left_building = this->m_heap[left_child_index];
                    int left_building_height = this->m_buildings[left_building][2];
                    if (left_building_height > max_height)
                    {
                        max_index = left_child_index;
                        max_building = left_building;
                        max_height = left_building_height;
                    }
                }
                if (right_child_index < this->m_heap_size)
                {
                    int right_building = this->m_heap[right_child_index];
                    int right_building_height = this->m_buildings[right_building][2];
                    if (right_building_height > max_height)
                    {
                        max_index = right_child_index;
                        max_building = right_building;
                        max_height = right_building_height;
                    }
                }
                if (max_index != current_index)
                {
                    swap(this->m_heap[current_index], this->m_heap[max_index]);
                    swap(this->m_building_heap_index[current_building], this->m_building_heap_index[max_building]);
                    this->bubble_down(max_index);
                }
            }

            int height()
            {
                if (this->m_heap_size > 0)
                {
                    int max_building = this->m_heap[0];
                    return this->m_buildings[max_building][2];
                }
                else
                {
                    return 0;
                }
            }

        private:
            vector<vector<int>>& m_buildings;
            int m_heap_size;
            vector<int> m_heap;
            vector<int> m_building_heap_index;
        };

    public:
        vector<pair<int, int>> getSkyline(vector<vector<int>>& buildings)
        {
            vector<pair<int, int>> result;

            // Step 1: Model each vertical line as an event
            vector<pair<int, bool>> events(buildings.size() * 2); // (building_number, isGoingUp)
            for (size_t i = 0; i < buildings.size(); i++)
            {
                events[i * 2] = pair<int, bool>(i, true);
                events[i * 2 + 1] = pair<int, bool>(i, false);
            }

            // Step 2: Sort the events by x-coordinates
            event_comparer my_event_comparer(buildings);
            sort(events.begin(), events.end(), my_event_comparer);

            // Step 3: Process the event and maintain the status by a heap
            status my_status(buildings);
            int event_index = 0;
            int last_height = 0;
            while (true) // make sure we process all events
            {
                if (event_index == events.size())
                {
                    break;
                }
                bool processed_one_event = false;
                int last_event_x = 1 << 31;

                while (true) // make sure we process all events with the same x
                {
                    if (event_index == events.size())
                    {
                        break;
                    }
                    // Decoding the event
                    pair<int, bool> event = events[event_index];
                    int event_building = event.first;
                    bool event_is_going_up = event.second;
                    int event_x = event_is_going_up ? buildings[event_building][0] : buildings[event_building][1];
                    int event_y = buildings[event_building][2];

                    if (processed_one_event && event_x != last_event_x)
                    {
                        break;
                    }
                    processed_one_event = true;
                    last_event_x = event_x;

                    if (event_is_going_up)
                    {
                        my_status.insert(event_building);
                    }
                    else
                    {
                        my_status.remove(event_building);
                    }

                    event_index++;
                }

                // Did we changed altitude? If so update the skyline
                if (my_status.height() != last_height)
                {
                    result.push_back(pair<int, int>(last_event_x, my_status.height()));
                    last_height = my_status.height();
                }
            }

            return result;
        }
    };
};

using namespace _LEET_THE_SKYLINE_PROBLEM;

int LEET_THE_SKYLINE_PROBLEM()
{
    Solution solution;
    vector<vector<int>> buildings(5);
    buildings[0].push_back(2);  buildings[0].push_back(9);  buildings[0].push_back(10);
    buildings[1].push_back(3);  buildings[1].push_back(7);  buildings[1].push_back(15);
    buildings[2].push_back(5);  buildings[2].push_back(12); buildings[2].push_back(12);
    buildings[3].push_back(15); buildings[3].push_back(20); buildings[3].push_back(10);
    buildings[4].push_back(19); buildings[4].push_back(24); buildings[4].push_back(8);

    vector<pair<int, int>> result = solution.getSkyline(buildings);
    for (size_t i = 0; i < result.size(); i++)
    {
        cout << result[i].first << ", " << result[i].second << endl;
    }

    return 0;
}