#include "stdafx.h"

// https://www.hackerrank.com/challenges/tree-preorder-traversal

#include "HACKER_RANK_TREE_PREORDER_TRAVERSAL.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _HACKER_RANK_TREE_PREORDER_TRAVERSAL
{
    struct node
    {
        int data;
        node* left;
        node* right;
    };

    void preOrder(node *root)
    {
        if (root == nullptr)
        {
            return;
        }
        cout << root->data << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
};

using namespace _HACKER_RANK_TREE_PREORDER_TRAVERSAL;

int HACKER_RANK_TREE_PREORDER_TRAVERSAL()
{
    node a;
    node b;
    node c;
    node d;
    node e;
    node f;
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
    preOrder(&a);
    return 0;
}