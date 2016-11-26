#include "stdafx.h"

// https://www.hackerrank.com/challenges/tree-inorder-traversal

#include "HACKER_RANK_TREE_INORDER_TRAVERSAL.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _HACKER_RANK_TREE_INORDER_TRAVERSAL
{
    struct node
    {
        int data;
        node* left;
        node* right;
    };

    void inOrder(node *root)
    {
        if (root == nullptr)
        {
            return;
        }
        inOrder(root->left);
        cout << root->data << " ";
        inOrder(root->right);
    }
};

using namespace _HACKER_RANK_TREE_INORDER_TRAVERSAL;

int HACKER_RANK_TREE_INORDER_TRAVERSAL()
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
    inOrder(&a);
    return 0;
}