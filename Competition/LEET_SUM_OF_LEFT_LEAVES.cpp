#include "stdafx.h"

// https://leetcode.com/problems/sum-of-left-leaves/

#include "LEET_SUM_OF_LEFT_LEAVES.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_SUM_OF_LEFT_LEAVES
{
    struct TreeNode
    {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int x) : val(x), left(NULL), right(NULL)
        {
        }
    };
    class Solution
    {
    public:
        int sumOfLeftLeaves(TreeNode* root)
        {
            int sum = 0;
            if (root != nullptr)
            {
                if (root->left != nullptr)
                {
                    if (root->left->left == nullptr && root->left->right == nullptr)
                    {
                        sum += root->left->val;
                    }
                }
                sum += sumOfLeftLeaves(root->left);
                sum += sumOfLeftLeaves(root->right);
            }
            return sum;
        }
    };
};

using namespace _LEET_SUM_OF_LEFT_LEAVES;

int LEET_SUM_OF_LEFT_LEAVES()
{
    Solution solution;
    TreeNode a(3);
    TreeNode b(9);
    TreeNode c(20);
    TreeNode d(15);
    TreeNode e(7);
    a.left = &b;
    a.right = &c;
    c.left = &d;
    c.right = &e;
    cout << solution.sumOfLeftLeaves(&a) << endl;
    return 0;
}