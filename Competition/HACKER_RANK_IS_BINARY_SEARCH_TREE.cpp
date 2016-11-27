#include "stdafx.h"

// https://www.hackerrank.com/challenges/is-binary-search-tree

#include "HACKER_RANK_IS_BINARY_SEARCH_TREE.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _HACKER_RANK_IS_BINARY_SEARCH_TREE
{
    struct Node
    {
        int data;
        Node* left;
        Node* right;
    };

    bool has_last = false;
    int last = 10086;

    bool checkBST(Node* root)
    {
        if (root == nullptr)
        {
            return true;
        }
        if (!checkBST(root->left)) { return false; }
        if (has_last)
        {
            if (root->data < last)
            {
                return false;
            }
        }
        else
        {
            has_last = true;
        }
        last = root->data;
        if (!checkBST(root->right)) { return false; }
        return true;
    }
};

using namespace _HACKER_RANK_IS_BINARY_SEARCH_TREE;

int HACKER_RANK_IS_BINARY_SEARCH_TREE()
{
    Node a;
    Node b;
    Node c;
    Node d;
    Node e;
    Node f;
    a.data = 3;
    b.data = 5;
    c.data = 2;
    d.data = 1;
    e.data = 4;
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
    cout << checkBST(&a) << endl;
    return 0;
}