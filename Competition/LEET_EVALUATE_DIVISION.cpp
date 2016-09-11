#include "stdafx.h"

// https://leetcode.com/contest/4/problems/evaluate-division/

#include "LEET_EVALUATE_DIVISION.h"
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_EVALUATE_DIVISION
{
    class Solution {
    public:
        vector<double> calcEquation(vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> query)
        {
            unordered_map<string, unordered_map<string, double>> adj;
            unordered_set<string> zeros;
            for (size_t i = 0; i < equations.size(); i++)
            {
                string a = equations[i].first;
                string b = equations[i].second;
                if (values[i] == 0)
                {
                    if (zeros.find(a) == zeros.end())
                    {
                        zeros.insert(b);
                    }
                }
                else
                {
                    auto probe1 = adj.find(a);
                    if (probe1 == adj.end())
                    {
                        unordered_map<string, double> new_list;
                        new_list.insert(make_pair(b, values[i]));
                        adj.insert(make_pair(a, new_list));
                    }
                    else
                    {
                        unordered_map<string, double>& old_list = probe1->second;
                        auto probe2 = old_list.find(b);
                        if (probe2 == old_list.end())
                        {
                            old_list.insert(make_pair(b, values[i]));
                        }
                        else
                        {
                            throw 0;
                        }
                    }
                    auto probe3 = adj.find(b);
                    if (probe3 == adj.end())
                    {
                        unordered_map<string, double> new_list;
                        new_list.insert(make_pair(a, 1/ values[i]));
                        adj.insert(make_pair(b, new_list));
                    }
                    else
                    {
                        unordered_map<string, double>& old_list = probe3->second;
                        auto probe4 = old_list.find(a);
                        if (probe4 == old_list.end())
                        {
                            old_list.insert(make_pair(a, 1 / values[i]));
                        }
                        else
                        {
                            throw 0;
                        }
                    }
                }
            }

            vector<double> result;
            for (auto queryIter = query.begin(); queryIter != query.end(); queryIter++)
            {
                unordered_set<string> visited;
                string& p = queryIter->first;
                string& q = queryIter->second;
                if (zeros.find(p) != zeros.end())
                {
                    result.push_back(0);
                }
                else
                {
                    result.push_back(calc(p, q, adj, visited));
                }
            }

            return result;
        }
    private:
        double calc(const string& p, const string& q, unordered_map<string, unordered_map<string, double>>& adj, unordered_set<string>& visited)
        {
            visited.insert(p);
            auto probe1 = adj.find(p);
            if (probe1 == adj.end())
            {
                return -1;
            }
            else
            {
                if (p == q)
                {
                    return 1;
                }
                for (auto neighborIter = probe1->second.begin(); neighborIter != probe1->second.end(); neighborIter++)
                {
                    const string& neighborName = neighborIter->first;
                    if (visited.find(neighborName) == visited.end())
                    {
                        double result = calc(neighborName, q, adj, visited);
                        if (result != -1)
                        {
                            return neighborIter->second * result;
                        }
                    }
                }
                return -1;
            }
        }
    };
};

using namespace _LEET_EVALUATE_DIVISION;

int LEET_EVALUATE_DIVISION()
{
    Solution solution;
    vector<pair<string, string>> equations;
    equations.push_back(make_pair("a", "b"));
    equations.push_back(make_pair("b", "c"));
    vector<double> values;
    values.push_back(2);
    values.push_back(3);
    vector<pair<string, string>> queries;
    queries.push_back(make_pair("a", "c"));
    queries.push_back(make_pair("b", "a"));
    queries.push_back(make_pair("a", "e"));
    queries.push_back(make_pair("a", "a"));
    queries.push_back(make_pair("x", "x"));
    vector<double> result = solution.calcEquation(equations, values, queries);
    for (size_t i = 0; i < result.size(); i++)
    {
        cout << result[i] << endl;
    }
    return 0;
}