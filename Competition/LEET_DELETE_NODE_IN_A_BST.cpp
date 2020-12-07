#include "stdafx.h"

// https://leetcode.com/problems/delete-node-in-a-bst/

#include "LEET_DELETE_NODE_IN_A_BST.h"
#include <map>
#include <cassert>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_DELETE_NODE_IN_A_BST
{
    struct TreeNode
    {
        int val;
        TreeNode* left;
        TreeNode* right;
        TreeNode() : val(0), left(nullptr), right(nullptr) {}
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
        TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
    };
    class Solution
    {
    public:
        TreeNode* deleteNode(TreeNode* root, int key)
        {
            TreeNode* cursor = root;
            TreeNode* parent = NULL;
            TreeNode* toDelete = NULL;
            while (true)
            {
                if (cursor == NULL)
                {
                    return root;
                }
                if (cursor->val == key)
                {
                    toDelete = cursor;
                    break;
                }
                else if (cursor->val > key)
                {
                    parent = cursor;
                    cursor = cursor->left;
                }
                else
                {
                    parent = cursor;
                    cursor = cursor->right;
                }
            }
            if (toDelete->left != NULL)
            {
                TreeNode* previous = toDelete;
                cursor = toDelete->left;
                while (cursor->right != NULL)
                {
                    previous = cursor;
                    cursor = cursor->right;
                }
                toDelete->val = cursor->val;
                if (previous == toDelete)
                {
                    toDelete->left = cursor->left;
                }
                else
                {
                    previous->right = cursor->left;
                }
                delete cursor;
            }
            else if (toDelete->right != NULL)
            {
                TreeNode* previous = toDelete;
                cursor = toDelete->right;
                while (cursor->left != NULL)
                {
                    previous = cursor;
                    cursor = cursor->left;
                }
                toDelete->val = cursor->val;
                if (previous == toDelete)
                {
                    toDelete->right = cursor->right;
                }
                else
                {
                    previous->left = cursor->right;
                }
                delete cursor;
            }
            else if (parent == NULL)
            {
                delete root;
                return NULL;
            }
            else if (parent->left == toDelete)
            {
                delete toDelete;
                parent->left = NULL;
            }
            else
            {
                assert(parent->right == toDelete);
                delete toDelete;
                parent->right = NULL;
            }
            return root;
        }
    };
};

using namespace _LEET_DELETE_NODE_IN_A_BST;

int LEET_DELETE_NODE_IN_A_BST()
{
    Solution solution;
    TreeNode* a = new TreeNode(5);
    TreeNode* b = new TreeNode(3);
    TreeNode* c = new TreeNode(6);
    TreeNode* d = new TreeNode(2);
    TreeNode* e = new TreeNode(4);
    TreeNode* f = new TreeNode(7);
    a->left = b;
    a->right = c;
    b->left = d;
    b->right = e;
    c->right = f;
    TreeNode* answer = solution.deleteNode(a, 3);
    cout << ((answer->val == 5) ? "pass" : "fail") << endl;
    cout << ((answer->left->val == 2) ? "pass" : "fail") << endl;
    cout << ((answer->left->right->val == 4) ? "pass" : "fail") << endl;
    cout << ((answer->right->val == 6) ? "pass" : "fail") << endl;
    cout << ((answer->right->right->val == 7) ? "pass" : "fail") << endl;
    return 0;
}