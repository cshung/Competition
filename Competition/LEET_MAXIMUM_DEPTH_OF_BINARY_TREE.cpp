#include "stdafx.h"

// https://leetcode.com/problems/maximum-depth-of-binary-tree/

#include "LEET_MAXIMUM_DEPTH_OF_BINARY_TREE.h"

#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <algorithm>

using namespace std;

namespace _LEET_MAXIMUM_DEPTH_OF_BINARY_TREE
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
        int maxDepth(TreeNode *root)
        {
            if (root == NULL)
            {
                return 0;
            }
            else
            {
                return 1 + max(maxDepth(root->left), maxDepth(root->right));
            }
        }
    };
}

using namespace _LEET_MAXIMUM_DEPTH_OF_BINARY_TREE;

int LEET_MAXIMUM_DEPTH_OF_BINARY_TREE()
{
    TreeNode a(1);
    TreeNode b(1);
    TreeNode c(1);
    TreeNode d(1);
    a.left = &b;    a.right = NULL;
    b.left = &c;    b.right = &d;
    c.left = NULL;    c.right = NULL;
    d.left = NULL;    d.right = NULL;
    Solution solution;
    cout << solution.maxDepth(&a) << endl;
    return 0;
}
