#include "stdafx.h"

// https://www.hackerrank.com/challenges/tree-level-order-traversal

#include "HACKER_RANK_TREE_LEVEL_ORDER_TRAVERSAL.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _HACKER_RANK_TREE_LEVEL_ORDER_TRAVERSAL
{
    struct node
    {
        int data;
        node* left;
        node* right;
    };

    void LevelOrder(node * root)
    {
        vector<node*> buffer1;
        vector<node*> buffer2;
        vector<node*>* pBuffer1 = &buffer1;
        vector<node*>* pBuffer2 = &buffer2;
        buffer1.push_back(root);
        while (true)
        {
            vector<node*>& prev_layer = *pBuffer1;
            vector<node*>& next_layer = *pBuffer2;
            if (prev_layer.size() == 0)
            {
                break;
            }
            for (int i = 0; i < prev_layer.size(); i++)
            {
                node* prev_node = prev_layer[i];
                cout << prev_node->data << " ";
                if (prev_node->left != nullptr)
                {
                    next_layer.push_back(prev_node->left);
                }
                if (prev_node->right != nullptr)
                {
                    next_layer.push_back(prev_node->right);
                }
            }
            prev_layer.clear();
            swap(pBuffer1, pBuffer2);
        }
    }
};

using namespace _HACKER_RANK_TREE_LEVEL_ORDER_TRAVERSAL;

int HACKER_RANK_TREE_LEVEL_ORDER_TRAVERSAL()
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
    LevelOrder(&a);
    return 0;
}