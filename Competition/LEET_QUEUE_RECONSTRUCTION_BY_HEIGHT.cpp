#include "stdafx.h"

// https://leetcode.com/problems/queue-reconstruction-by-height/

#include "LEET_QUEUE_RECONSTRUCTION_BY_HEIGHT.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

namespace _LEET_QUEUE_RECONSTRUCTION_BY_HEIGHT
{
    class Solution
    {
    public:
        vector<pair<int, int>> reconstructQueue(vector<pair<int, int>>& people)
        {
            if (people.size() < 2)
            {
                return people;
            }
            int n = people.size();
            for (int i = 0; i < n; i++)
            {
                people[i].second = n - people[i].second;
            }
            sort(people.begin(), people.end());
            for (int i = 0; i < n; i++)
            {
                people[i].second = n - people[i].second;
            }
            Node* tree = build_tree(0, n);

            vector<pair<int, int>> result;
            result.resize(n);
            for (int i = 0; i < n; i++)
            {
                int position = place_in_tree(tree, people[i].second);
#ifdef LOG
                cout << "Searching for " << people[i].first << ", " << people[i].second << endl;
                cout << "===================" << endl;
                print(tree, 0);
                cout << "===================" << endl;
                cout << position << endl;
#endif
                result[position] = people[i];
            }

            return result;
        }
    private:
        struct Node
        {
            Node* left;
            Node* right;
            int begin;
            int sum;
        };
#ifdef LOG
        void print(Node* tree, int indent)
        {
            if (tree == nullptr) { return; }
            for (int i = 0; i < indent; i++) { cout << " "; } cout << tree->sum << (tree->left == nullptr ? "*" : "") << endl;
            print(tree->left, indent + 2);
            print(tree->right, indent + 2);
        }
#endif
        int place_in_tree(Node* tree, int position)
        {
            tree->sum--;
            if (tree->left == NULL)
            {
                if (position != 0) { throw 1; }
                return tree->begin;
            }
            else
            {
                if (position < tree->left->sum)
                {
                    return place_in_tree(tree->left, position);
                }
                else
                {
                    return place_in_tree(tree->right, position - tree->left->sum);
                }
            }
        }
        Node* build_tree(int start, int end)
        {
            Node* result = new Node();
            result->begin = start;
            if (start + 1 == end)
            {
                result->left = result->right = nullptr;
                result->sum = 1;
            }
            else
            {
                int mid = start + (end - start) / 2;
                result->left = build_tree(start, mid);
                result->right = build_tree(mid, end);
                result->sum = result->left->sum + result->right->sum;
            }
            return result;
        }
    };
};

using namespace _LEET_QUEUE_RECONSTRUCTION_BY_HEIGHT;

int LEET_QUEUE_RECONSTRUCTION_BY_HEIGHT()
{
    vector<pair<int, int>> example;
    // [[7,0], [4,4], [7,1], [5,0], [6,1], [5,2]]
    example.push_back(make_pair(7, 0));
    example.push_back(make_pair(4, 4));
    example.push_back(make_pair(7, 1));
    example.push_back(make_pair(5, 0));
    example.push_back(make_pair(6, 1));
    example.push_back(make_pair(5, 2));
    Solution solution;
    vector<pair<int, int>> answer = solution.reconstructQueue(example);
    for (size_t i = 0; i < answer.size(); i++)
    {
        cout << answer[i].first << ", " << answer[i].second << endl;
    }
    return 0;
}