#include "stdafx.h"

// https://leetcode.com/problems/binary-tree-tilt

#include "LEET_BINARY_TREE_TILT.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_BINARY_TREE_TILT
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
        void findTiltSum(TreeNode* root, int* pTilt, int* pSum)
        {
            if (root == nullptr)
            {
                *pTilt = 0;
                *pSum = 0;
            }
            else
            {
                int leftTilt;
                int leftSum;
                int rightTilt;
                int rightSum;
                findTiltSum(root->left, &leftTilt, &leftSum);
                findTiltSum(root->right, &rightTilt, &rightSum);
                *pSum = leftSum + rightSum + root->val;
                *pTilt = abs(leftSum - rightSum) + leftTilt + rightTilt;
            }
        }

        int findTilt(TreeNode* root)
        {
            int tilt;
            int sum;
            findTiltSum(root, &tilt, &sum);
            return tilt;
        }
    };
};

using namespace _LEET_BINARY_TREE_TILT;

int LEET_BINARY_TREE_TILT()
{
    Solution solution;
    TreeNode a(1);
    TreeNode b(2);
    TreeNode c(3);
    a.left = &b;
    a.right = &c;
    b.left = nullptr;
    b.right = nullptr;
    c.left = nullptr;
    c.right = nullptr;
    cout << solution.findTilt(&a) << endl;
    return 0;
}