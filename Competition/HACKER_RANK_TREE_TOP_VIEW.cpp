#include "stdafx.h"

// https://www.hackerrank.com/challenges/tree-top-view

#include "HACKER_RANK_TREE_TOP_VIEW.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _HACKER_RANK_TREE_TOP_VIEW
{
    struct node
    {
    int data;
    node* left;
    node* right;
    };

    void left_chain(node* root)
    {
        if (root == nullptr)
        {
            return;
        }
        left_chain(root->left);
        cout << root->data << " ";
    }

    void top_view(node * root)
    {
        left_chain(root);
        node* cur = root;
        while (cur != nullptr)
        {
            if (cur != root)
            {
                cout << cur->data << " ";
            }
            cur = cur->right;
        }
    }

};

using namespace _HACKER_RANK_TREE_TOP_VIEW;

int HACKER_RANK_TREE_TOP_VIEW()
{
    node a;
    node b;
    node c;
    node d;
    node e;
    node f;
    node g;
    node h;
    node i;
    a.data = 3;
    b.data = 5;
    c.data = 2;
    d.data = 1;
    e.data = 4;
    f.data = 6;
    g.data = 7;
    h.data = 9;
    i.data = 8;
    a.left = &b;
    a.right = &c;
    b.left = &d;
    b.right = &e;
    c.left = &f;
    c.right = &g;
    d.left = nullptr;
    d.right = &h;
    e.left = nullptr;
    e.right = nullptr;
    f.left = nullptr;
    f.right = nullptr;
    g.left = &i;
    g.right = nullptr;
    h.left = nullptr;
    h.right = nullptr;
    i.left = nullptr;
    i.right = nullptr;
    top_view(&a);
    return 0;
}