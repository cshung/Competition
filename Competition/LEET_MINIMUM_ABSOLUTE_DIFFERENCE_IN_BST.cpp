#include "stdafx.h"

// https://leetcode.com/problems/minimum-absolute-difference-in-bst

#include "LEET_MINIMUM_ABSOLUTE_DIFFERENCE_IN_BST.h"
#include <map>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_MINIMUM_ABSOLUTE_DIFFERENCE_IN_BST
{
    struct TreeNode
    {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };
    class Solution {
    private:
        void getMinimumDifference(TreeNode* root, int* pMin, int* pMax, bool* pHasResult, int* pResult)
        {
            int leftMin;
            int leftMax;
            bool leftHasResult;
            int leftResult;
            int rightMin;
            int rightMax;
            bool rightHasResult;
            int rightResult;

            if (root->left != nullptr)
            {
                getMinimumDifference(root->left, &leftMin, &leftMax, &leftHasResult, &leftResult);
            }
            if (root->right != nullptr)
            {
                getMinimumDifference(root->right, &rightMin, &rightMax, &rightHasResult, &rightResult);
            }

            if (root->left != nullptr) { *pMin = leftMin; }
            else { *pMin = root->val; }
            if (root->right != nullptr) { *pMax = rightMax; }
            else { *pMax = root->val; }

            if (root->left != nullptr)
            {
                if (leftHasResult)
                {
                    leftResult = min(leftResult, root->val - leftMax);
                }
                else
                {
                    leftResult = root->val - leftMax;
                }
                leftHasResult = true;
            }
            else
            {
                leftHasResult = false;
            }
            if (root->right != nullptr)
            {
                if (rightHasResult)
                {
                    rightResult = min(rightResult, rightMin - root->val);
                }
                else
                {
                    rightResult = rightMax - root->val;
                }
                rightHasResult = true;
            }
            else
            {
                rightHasResult = false;
            }
            *pHasResult = true;
            if (leftHasResult)
            {
                if (rightHasResult)
                {
                    *pResult = min(leftResult, rightResult);
                }
                else
                {
                    *pResult = leftResult;
                }
            }
            else {
                if (rightHasResult)
                {
                    *pResult = rightResult;
                }
                else
                {
                    *pHasResult = false;
                }
            }

        }
    public:
        int getMinimumDifference(TreeNode* root) {
            int min;
            int max;
            bool hasResult;
            int result;
            getMinimumDifference(root, &min, &max, &hasResult, &result);
            return result;
        }
    };
};

using namespace _LEET_MINIMUM_ABSOLUTE_DIFFERENCE_IN_BST;

int LEET_MINIMUM_ABSOLUTE_DIFFERENCE_IN_BST()
{
    Solution solution;
    TreeNode a(1);
    TreeNode b(3);
    TreeNode c(2);
    a.left = nullptr;
    a.right = &b;
    b.left = &c;
    b.right = nullptr;
    c.left = nullptr;
    c.right = nullptr;
    cout << solution.getMinimumDifference(&a) << endl;
    return 0;
}