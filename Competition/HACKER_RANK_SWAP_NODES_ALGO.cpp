#include "stdafx.h"

// https://leetcode.com/problems/climbing-stairs/

#include "HACKER_RANK_SWAP_NODES_ALGO.h"
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

namespace _HACKER_RANK_SWAP_NODES_ALGO
{
    struct node
    {
        node* left;
        node* right;
        int data;
    };

    void inOrderSwapAndPrint(node* node, int k, int depth)
    {
        if (node == nullptr)
        {
            return;
        }
        if (depth % k == 0)
        {
            swap(node->left, node->right);
        }
        inOrderSwapAndPrint(node->left, k, depth + 1);
        cout << node->data << " ";
        inOrderSwapAndPrint(node->right, k, depth + 1);
    }

    int main()
    {
        int n;
        cin >> n;
        vector<node*> nodes(n);
        vector<bool> has_parent(n);
        for (int i = 0; i < n; i++)
        {
            nodes[i] = new node();
            nodes[i]->data = i + 1;
            nodes[i]->left = nullptr;
            nodes[i]->right = nullptr;
            has_parent[i] = false;
        }

        // Build the tree from input
        for (int i = 0; i < n; i++)
        {
            int a;
            int b;
            cin >> a;
            cin >> b;
            if (a != -1)
            {
                nodes[i]->left = nodes[a - 1];
                has_parent[a - 1] = true;
            }
            if (b != -1)
            {
                nodes[i]->right = nodes[b - 1];
                has_parent[b - 1] = true;
            }
        }

        // Finding the root
        node* root = nullptr;
        for (int i = 0; i < n; i++)
        {
            if (!has_parent[i])
            {
                if (root == nullptr)
                {
                    root = nodes[i];
                }
                else
                {
                    throw 1;
                }
            }
        }

        int t;
        cin >> t;
        for (int i = 0; i < t; i++)
        {
            int k;
            cin >> k;
            inOrderSwapAndPrint(root, k, 1);
        }
        cout << endl;

        return 0;
    }
};

int HACKER_RANK_SWAP_NODES_ALGO()
{
    _HACKER_RANK_SWAP_NODES_ALGO::main();
    return 0;
}