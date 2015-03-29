#include "stdafx.h"

// https://leetcode.com/problems/balanced-binary-tree/

#include "LEET_BALANCED_BINARY_TREE.h"

#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <algorithm>

using namespace std;

namespace _LEET_BALANCED_BINARY_TREE
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
        bool isBalanced(TreeNode *root)
        {
            bool result = false;
            int depth = 0; // unused
            isBalanced(&result, &depth, root);
            return result;
        }

        void isBalanced(bool* result, int* depth, TreeNode* root)
        {
            if (root == NULL)
            {
                *result = true;
                *depth = 0;
            }
            else
            {
                bool l_result;
                int l_depth;
                bool r_result;
                int r_depth;
                isBalanced(&l_result, &l_depth, root->left);
                isBalanced(&r_result, &r_depth, root->right);
                if (l_depth < r_depth)
                {
                    *result = l_result && r_result && (r_depth - l_depth) < 2;
                    *depth = 1 + r_depth;
                }
                else
                {
                    *result = l_result && r_result && (l_depth - r_depth) < 2;
                    *depth = 1 + l_depth;
                }
            }
        }
    };
}

using namespace _LEET_BALANCED_BINARY_TREE;

int LEET_BALANCED_BINARY_TREE()
{
    TreeNode a(1);
    TreeNode b(2);
    TreeNode c(3);
    a.left = NULL;    a.right = &b;
    b.left = NULL;    b.right = &c;
    c.left = NULL;    c.right = NULL;
    Solution solution;
    cout << solution.isBalanced(&a) << endl;
    return 0;
}
