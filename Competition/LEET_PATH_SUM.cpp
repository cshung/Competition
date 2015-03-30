#include "stdafx.h"

// https://leetcode.com/problems/path-sum/

#include "LEET_PATH_SUM.h"

#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <algorithm>

using namespace std;

namespace _LEET_PATH_SUM
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
        bool hasPathSum(TreeNode *root, int sum)
        {
            if (root == NULL)
            {
                return false;
            }
            else if (root->left == NULL && root->right == NULL && root->val == sum)
            {
                return true;
            }
            else
            {
                return hasPathSum(root->left, sum - root->val) || hasPathSum(root->right, sum - root->val);
            }
        }
    };
}

using namespace _LEET_PATH_SUM;

int LEET_PATH_SUM()
{
    TreeNode a(1);
    TreeNode b(2);
    TreeNode c(3);
    a.left = NULL;    a.right = &b;
    b.left = &c;  b.right = NULL;
    c.left = NULL;  c.right = NULL;
    Solution solution;
    cout << solution.hasPathSum(&a, 1) << endl;
    cout << solution.hasPathSum(&a, 2) << endl;
    cout << solution.hasPathSum(&a, 3) << endl;
    cout << solution.hasPathSum(&a, 4) << endl;
    cout << solution.hasPathSum(&a, 5) << endl;
    cout << solution.hasPathSum(&a, 6) << endl;
    return 0;
}
