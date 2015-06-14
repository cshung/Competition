#include "stdafx.h"

// https://leetcode.com/problems/invert-binary-tree/

#include "LEET_INVERT_BINARY_TREE.h"
#include <iostream>
#include <algorithm>

using namespace std;

namespace _LEET_INVERT_BINARY_TREE
{
    struct TreeNode
    {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };
    class Solution {
    public:
        TreeNode* invertTree(TreeNode* root) {
            if (root == NULL)
            {
                return root;
            }
            else
            {
                invertTree(root->left);
                invertTree(root->right);
                swap(root->left, root->right);
                return root;
            }
        }
    };
}

using namespace _LEET_INVERT_BINARY_TREE;

int LEET_INVERT_BINARY_TREE()
{
    TreeNode a(4);
    TreeNode b(2);
    TreeNode c(7);
    TreeNode d(1);
    TreeNode e(3);
    TreeNode f(6);
    TreeNode g(9);
    a.left = &b;      a.right = &c;
    b.left = &d;      b.right = &e;
    c.left = &f;      c.right = &g;
    d.left = NULL;    d.right = NULL;
    e.left = NULL;    e.right = NULL;
    f.left = NULL;    f.right = NULL;
    g.left = NULL;    g.right = NULL;
    Solution solution;
    solution.invertTree(&a);
    cout << (a.left == &c) << endl;
    cout << (a.right == &b) << endl;
    cout << (c.left == &g) << endl;
    cout << (c.right == &f) << endl;
    cout << (b.left == &e) << endl;
    cout << (b.right == &d) << endl;
    return 0;
}
