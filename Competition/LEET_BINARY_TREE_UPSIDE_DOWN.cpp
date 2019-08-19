// LEET_BINARY_TREE_UPSIDE_DOWN
#include "stdafx.h"

// https://leetcode.com/problems/binary-tree-upside-down/

#include "LEET_BINARY_TREE_UPSIDE_DOWN.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_BINARY_TREE_UPSIDE_DOWN
{
    struct TreeNode
    {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };
    class Solution
    {
    public:
        TreeNode* upsideDownBinaryTree(TreeNode* root)
        {
            if (root == nullptr)
            {
                return nullptr;
            }
            if (root->left == nullptr)
            {
                return root;
            }
            TreeNode* toBeLeft = root->right;
            TreeNode* toBeRight = root;
            TreeNode* toBeRoot = root->left;
            TreeNode* answer = upsideDownBinaryTree(root->left);
            toBeRoot->left = toBeLeft;
            toBeRoot->right = toBeRight;
            toBeRight->left = nullptr;
            toBeRight->right = nullptr;
            return answer;
        }
    };
};

using namespace _LEET_BINARY_TREE_UPSIDE_DOWN;

int LEET_BINARY_TREE_UPSIDE_DOWN()
{
    Solution solution;
    TreeNode a(1);
    TreeNode b(2);
    TreeNode c(3);
    TreeNode d(4);
    TreeNode e(5);
    a.left = &b;
    a.right = &c;
    b.left = &d;
    b.right = &e;
    TreeNode* ans = solution.upsideDownBinaryTree(&a);

    cout << (ans->val == 4) << endl;
    cout << (ans->left->val == 5) << endl;
    cout << (ans->right->val == 2) << endl;
    cout << (ans->left->left == nullptr) << endl;
    cout << (ans->left->right == nullptr) << endl;
    cout << (ans->right->left->val == 3) << endl;
    cout << (ans->right->right->val == 1) << endl;
    cout << (ans->right->left->left == nullptr) << endl;
    cout << (ans->right->left->right == nullptr) << endl;
    cout << (ans->right->right->left == nullptr) << endl;
    cout << (ans->right->right->right == nullptr) << endl;
    return 0;
}