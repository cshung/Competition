#include "stdafx.h"

// https://www.hackerrank.com/challenges/binary-search-tree-lowest-common-ancestor

#include "HACKER_RANK_BINARY_SEARCH_TREE_LOWEST_COMMON_ANCESTOR.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _HACKER_RANK_BINARY_SEARCH_TREE_LOWEST_COMMON_ANCESTOR
{
    typedef struct node
    {
        int data;
        node * left;
        node * right;
    } node;

    node * lca(node * root, int v1, int v2)
    {
        if (v1 > v2)
        {
            return lca(root, v2, v1);
        }
        if (root == nullptr)
        {
            return nullptr;
        }
        if (v1 == root->data || v2 == root->data)
        {
            return root;
        }
        if (v1 < root->data && v2 > root->data)
        {
            return root;
        }
        else if (v1 < root->data && v2 < root->data)
        {
            return lca(root->left, v1, v2);
        }
        else
        {
            return lca(root->right, v1, v2);
        }
    }
};

using namespace _HACKER_RANK_BINARY_SEARCH_TREE_LOWEST_COMMON_ANCESTOR;

int HACKER_RANK_BINARY_SEARCH_TREE_LOWEST_COMMON_ANCESTOR()
{
    node a;
    node b;
    node c;
    node d;
    node e;
    node f;
    a.data = 4;
    b.data = 2;
    c.data = 7;
    d.data = 1;
    e.data = 3;
    f.data = 6;
    a.left = &b;
    a.right = &c;
    b.left = &d;
    b.right = &e;
    c.left = &f;
    c.right = nullptr;
    d.left = nullptr;
    d.right = nullptr;
    e.left = nullptr;
    e.right = nullptr;
    f.left = nullptr;
    f.right = nullptr;
    cout << lca(&a, 1, 7)->data << endl;
    return 0;
}