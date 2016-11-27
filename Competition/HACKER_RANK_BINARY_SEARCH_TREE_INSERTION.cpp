#include "stdafx.h"

// https://www.hackerrank.com/challenges/binary-search-tree-insertion

#include "HACKER_RANK_BINARY_SEARCH_TREE_INSERTION.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _HACKER_RANK_BINARY_SEARCH_TREE_INSERTION
{
    typedef struct node
    {
        int data;
        node * left;
        node * right;
    } node;

    node * insert(node * root, int value)
    {
        if (root == nullptr)
        {
            node* new_node = new node();
            new_node->data = value;
            new_node->left = nullptr;
            new_node->right = nullptr;
            return new_node;
        }
        else
        {
            if (value < root->data)
            {
                root->left = insert(root->left, value);
            }
            else
            {
                root->right = insert(root->right, value);
            }
            return root;
        }
    }
};

using namespace _HACKER_RANK_BINARY_SEARCH_TREE_INSERTION;

int HACKER_RANK_BINARY_SEARCH_TREE_INSERTION()
{
    node a;
    node b;
    node c;
    node d;
    node e;
    a.data = 4;
    b.data = 2;
    c.data = 7;
    d.data = 1;
    e.data = 3;
    a.left = &b;
    a.right = &c;
    b.left = &d;
    b.right = &e;
    c.left = nullptr;
    c.right = nullptr;
    d.left = nullptr;
    d.right = nullptr;
    e.left = nullptr;
    e.right = nullptr;
    node* f = insert(&a, 6);
    cout << f->right->left->data << endl;
    return 0;
}