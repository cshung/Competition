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
    template<class T>
    struct Optional
    {
        bool hasValue;
        T value;
        static Optional<T> min(Optional<T> a, Optional<T> b)
        {
            if (a.hasValue)
            {
                if (b.hasValue)
                {
                    if (a.value < b.value)
                    {
                        return a;
                    }
                    else
                    {
                        return b;
                    }
                }
                else
                {
                    return a;
                }
            }
            else if (b.hasValue)
            {
                return b;
            }
            else
            {
                Optional<T> result;
                result.hasValue = false;
                return result;
            }
        }
    };
    
    class Solution {
    private:
        void getMinimumDifference(TreeNode* root, int* pMin, int* pMax, Optional<int>* pResult)
        {
            int leftMin;
            int leftMax;
            Optional<int> leftResult;
            int rightMin;
            int rightMax;
            Optional<int> rightResult;
            Optional<int> leftDifference;
            Optional<int> rightDifference;

            if (root->left != nullptr)
            {
                getMinimumDifference(root->left, &leftMin, &leftMax, &leftResult);
                leftDifference.hasValue = true;
                leftDifference.value = root->val - leftMax;
            }
            else
            {
                leftResult.hasValue = false;
                leftDifference.hasValue = false;
            }
            if (root->right != nullptr)
            {
                getMinimumDifference(root->right, &rightMin, &rightMax, &rightResult);
                rightDifference.hasValue = true;
                rightDifference.value = rightMin - root->val;
            }
            else
            {
                rightResult.hasValue = false;
                rightDifference.hasValue = false;
            }

            if (root->left != nullptr) { *pMin = leftMin; } else { *pMin = root->val; }
            if (root->right != nullptr) { *pMax = rightMax; } else { *pMax = root->val; }

            *pResult = Optional<int>::min(Optional<int>::min(Optional<int>::min(leftResult, leftDifference), rightResult), rightDifference);
        }
    public:
        int getMinimumDifference(TreeNode* root) {
            int min;
            int max;
            Optional<int> result;
            getMinimumDifference(root, &min, &max, &result);
            return result.value;
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