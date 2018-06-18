#include "stdafx.h"

// https://leetcode.com/problems/keys-and-rooms

#include "LEET_KEYS_AND_ROOMS.h"
#include <map>
#include <iostream>
#include <queue>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_KEYS_AND_ROOMS
{
    class Solution
    {
    public:
        bool canVisitAllRooms(vector<vector<int>>& rooms) {
            int n = rooms.size();
            queue<int> bfs;
            vector<bool> enqueued;
            enqueued.resize(n);
            for (int i = 0; i < n; i++)
            {
                enqueued[i] = i == 0;
            }
            int enqueue_count = 1;
            bfs.push(0);
            while (bfs.size() > 0)
            {
                int current = bfs.front();
                bfs.pop();
                for (auto k : rooms[current])
                {
                    if (!enqueued[k])
                    {
                        enqueue_count++;
                        enqueued[k] = true;
                        bfs.push(k);
                    }
                }
            }
            return enqueue_count == n;
        }
    };
};

using namespace _LEET_KEYS_AND_ROOMS;

int LEET_KEYS_AND_ROOMS()
{
    Solution solution;
    // [[1],[2],[3],[]]
    vector<vector<int>> rooms;
    rooms.resize(4);
    rooms[0].push_back(1);
    rooms[1].push_back(2);
    rooms[2].push_back(3);
    cout << solution.canVisitAllRooms(rooms) << endl;
    return 0;
}