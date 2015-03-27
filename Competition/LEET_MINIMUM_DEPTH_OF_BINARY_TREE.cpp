#include "stdafx.h"

// https://leetcode.com/problems/minimum-depth-of-binary-tree/

#include "LEET_MINIMUM_DEPTH_OF_BINARY_TREE.h"

#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <algorithm>

using namespace std;

namespace _LEET_MINIMUM_DEPTH_OF_BINARY_TREE
{
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };
    class Solution {
    public:
        int minDepth(TreeNode *root) {
            if (root == NULL)
            {
                return 0;
            }
            else
            {
                if (root->left == NULL)
                {
                    return 1 + minDepth(root->right);
                }
                if (root->right == NULL)
                {
                    return 1 + minDepth(root->left);
                }
                return 1 + min(minDepth(root->left), minDepth(root->right));
            }
        }
    };
}

using namespace _LEET_MINIMUM_DEPTH_OF_BINARY_TREE;

int LEET_MINIMUM_DEPTH_OF_BINARY_TREE()
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
    cout << solution.minDepth(&a) << endl;
    return 0;
}
