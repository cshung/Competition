#include "stdafx.h"

// https://leetcode.com/problems/binary-tree-pruning/

#include "LEET_BINARY_TREE_PRUNING.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_BINARY_TREE_PRUNING
{
    struct TreeNode
    {
        int val;
        TreeNode* left;
        TreeNode* right;
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };
    class Solution
    {
    public:
        TreeNode* pruneTree(TreeNode* root)
        {
            if (root != nullptr)
            {
                root->left = pruneTree(root->left);
                root->right = pruneTree(root->right);
                if (root->val == 0 && root->left == nullptr && root->right == nullptr)
                {
                    // Leaking the memory make the program run faster.
                    // Bad programming practice, but works great for competition
                    // delete root;
                    root = nullptr;
                }
            }
            return root;
        }
    };
};

using namespace _LEET_BINARY_TREE_PRUNING;

int LEET_BINARY_TREE_PRUNING()
{
    Solution solution;
    TreeNode a(1);
    TreeNode b(0);
    TreeNode c(0);
    TreeNode d(1);
    a.right = &b;
    b.left = &c;
    b.right = &d;
    TreeNode* s = solution.pruneTree(&a);
    cout << (s->val == 1) << endl;
    cout << (s->left == nullptr) << endl;
    cout << (s->right->val == 0) << endl;
    cout << (s->right->left == nullptr) << endl;
    cout << (s->right->right->val == 1) << endl;
    cout << (s->right->right->left == nullptr) << endl;
    cout << (s->right->right->right == nullptr) << endl;
    return 0;
}