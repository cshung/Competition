#include "stdafx.h"

// https://www.hackerrank.com/challenges/tree-height-of-a-binary-tree

#include "HACKER_RANK_TREE_HEIGHT_OF_A_BINARY_TREE.h"
#include <iostream>
#include <algorithm>

using namespace std;

namespace _HACKER_RANK_TREE_HEIGHT_OF_A_BINARY_TREE
{
    class Node
    {
    public:
        int data;
        Node* left;
        Node* right;
    };

    int getHeight(Node* root)
    {
        if (root == nullptr)
        {
            return -1;
        }
        else
        {
            return 1 + max(getHeight(root->left), getHeight(root->right));
        }
    }
};

using namespace _HACKER_RANK_TREE_HEIGHT_OF_A_BINARY_TREE;

int HACKER_RANK_TREE_HEIGHT_OF_A_BINARY_TREE()
{
    Node a;
    Node b;
    Node c;
    Node d;
    Node e;
    Node f;
    Node g;

    a.data = 3;
    b.data = 2;
    c.data = 5;
    d.data = 1;
    e.data = 4;
    f.data = 6;
    g.data = 7;

    a.left = &b;;
    a.right = &c;
    b.left = &d;
    b.right = nullptr;
    c.left = &e;
    c.right = &f;
    d.left = nullptr;
    d.right = nullptr;
    e.left = nullptr;
    e.right = nullptr;
    f.left = nullptr;
    f.right = &g;
    g.left = nullptr;
    g.right = nullptr;
    cout << getHeight(&a) << endl;
    return 0;
}