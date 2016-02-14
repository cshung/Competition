#include "stdafx.h"

// https://leetcode.com/problems/reconstruct-itinerary/

#include "LEET_RECONSTRUCT_ITINERARY.h"
#include <map>
#include <vector>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_RECONSTRUCT_ITINERARY
{
    class Solution
    {
    public:
        vector<string> findItinerary(vector<pair<string, string>> tickets)
        {
            map<string, vector<pair<string, bool>>> dest;

            // Step 1: Build the map
            for (size_t i = 0; i < tickets.size(); i++)
            {
                string src = tickets[i].first;
                string dst = tickets[i].second;
                map<string, vector<pair<string, bool>>>::iterator probe = dest.find(src);
                if (probe == dest.end())
                {
                    dest.insert(pair<string, vector<pair<string, bool>>>(src, vector<pair<string, bool>>()));
                }
                dest[src].push_back(pair<string, bool>(dst, true));
            }

            // Step 2 : Sort the destination vector
            for (map<string, vector<pair<string, bool>>>::iterator di = dest.begin(); di != dest.end(); di++)
            {
                sort(di->second.begin(), di->second.end());
            }
            vector<string> soln;
            soln.push_back("JFK");
            this->findItinerary("JFK", soln, tickets.size() + 1, dest);
            return soln;
        }

        bool findItinerary(string current, vector<string>& soln, int goal, map<string, vector<pair<string, bool>>>& dest)
        {
            map<string, vector<pair<string, bool>>>::iterator probe = dest.find(current);
            if (probe == dest.end())
            {
                return (soln.size() == goal);
            }
            else
            {
                vector<pair<string, bool>> & dstvector = probe->second;
                for (size_t i = 0; i < dstvector.size(); i++)
                {
                    if (dstvector[i].second)
                    {
                        dstvector[i].second = false;
                        soln.push_back(dstvector[i].first);
                        if (findItinerary(dstvector[i].first, soln, goal, dest))
                        {
                            return true;
                        }
                        soln.pop_back();
                        dstvector[i].second = true;
                    }
                }
                return (soln.size() == goal);
            }
        }
    };
};

using namespace _LEET_RECONSTRUCT_ITINERARY;

int LEET_RECONSTRUCT_ITINERARY()
{
    Solution solution;
    vector<pair<string, string>> itin;
    // [["MUC", "LHR"], ["JFK", "MUC"], ["SFO", "SJC"], ["LHR", "SFO"]]
    //itin.push_back(pair<string, string>("MUC", "LHR"));
    //itin.push_back(pair<string, string>("JFK", "MUC"));
    //itin.push_back(pair<string, string>("SFO", "SJC"));
    //itin.push_back(pair<string, string>("LHR", "SFO"));

    // [["JFK","SFO"],["JFK","ATL"],["SFO","ATL"],["ATL","JFK"],["ATL","SFO"]]
    //itin.push_back(pair<string, string>("JFK", "SFO"));
    //itin.push_back(pair<string, string>("JFK", "ATL"));
    //itin.push_back(pair<string, string>("SFO", "ATL"));
    //itin.push_back(pair<string, string>("ATL", "JFK"));
    //itin.push_back(pair<string, string>("ATL", "SFO"));

    // [["JFK", "KUL"], ["JFK", "NRT"], ["NRT", "JFK"]]
    itin.push_back(pair<string, string>("JFK", "KUL"));
    itin.push_back(pair<string, string>("JFK", "NRT"));
    itin.push_back(pair<string, string>("NRT", "JFK"));

    vector<string> result = solution.findItinerary(itin);
    for (size_t i = 0; i < result.size(); i++)
    {
        cout << result[i] << endl;
    }
    return 0;
}