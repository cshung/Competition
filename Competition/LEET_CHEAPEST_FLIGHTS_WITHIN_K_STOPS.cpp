#include "stdafx.h"

// https://leetcode.com/problems/cheapest-flights-within-k-stops/

#include "LEET_CHEAPEST_FLIGHTS_WITHIN_K_STOPS.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_CHEAPEST_FLIGHTS_WITHIN_K_STOPS
{
    class Solution
    {
    public:
        int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K)
        {
            vector<int> distance(n, -1);
            distance[src] = 0;
            for (int i = 0; i < K + 1; i++)
            {
                vector<int> prev = distance;
                for (auto edge : flights)
                {
                    int from = edge[0];
                    int to = edge[1];
                    int cost = edge[2];
                    if (prev[from] != -1)
                    {
                        int new_route = prev[from] + cost;
                        if (distance[to] == -1 || distance[to] > new_route)
                        {
                            distance[to] = new_route;
                        }
                    }
                }
            }
            return distance[dst];
        }
    };
};

using namespace _LEET_CHEAPEST_FLIGHTS_WITHIN_K_STOPS;

int LEET_CHEAPEST_FLIGHTS_WITHIN_K_STOPS()
{
    Solution solution;
    vector<vector<int>> flights(3, vector<int>(3, 0));
    flights[0][0] = 0;    flights[0][1] = 1;    flights[0][2] = 100;
    flights[1][0] = 1;    flights[1][1] = 2;    flights[1][2] = 100;
    flights[2][0] = 0;    flights[2][1] = 2;    flights[2][2] = 500;
    cout << solution.findCheapestPrice(3, flights, 0, 2, 1) << endl;
    cout << solution.findCheapestPrice(3, flights, 0, 2, 0) << endl;
    return 0;
}