#include "stdafx.h"

// https://leetcode.com/problems/count-univalue-subtrees/

#include "LEET_COUNT_UNIVALUE_SUBTREES.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_COUNT_UNIVALUE_SUBTREES
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
        int countUnivalSubtrees(TreeNode* root)
        {
            int count;
            countUnivalSubtreesHelper(root, &count);
            return count;
        }

        bool countUnivalSubtreesHelper(TreeNode* root, int* pCount)
        {
            if (root == nullptr)
            {
                *pCount = 0;
                return true;
            }
            else
            {
                int leftCount;
                int rightCount;
                bool leftPure = countUnivalSubtreesHelper(root->left, &leftCount);
                bool rightPure = countUnivalSubtreesHelper(root->right, &rightCount);
                bool pure = true;
                if (!leftPure)
                {
                    pure = false;
                }
                else if (!rightPure)
                {
                    pure = false;
                }
                else if (root->left != nullptr && root->val != root->left->val)
                {
                    pure = false;
                }
                else if (root->right != nullptr && root->val != root->right->val)
                {
                    pure = false;
                }
                *pCount = leftCount + rightCount;
                if (pure)
                {
                    *pCount = *pCount + 1;
                }
                return pure;
            }
        }
    };
};

using namespace _LEET_COUNT_UNIVALUE_SUBTREES;

int LEET_COUNT_UNIVALUE_SUBTREES()
{
    Solution solution;
    TreeNode a(5);
    TreeNode b(1);
    TreeNode c(5);
    TreeNode d(5);
    TreeNode e(5);
    TreeNode f(5);
    a.left = &b;
    a.right = &c;
    b.left = &d;
    b.right = &e;
    c.right = &f;
    cout << (solution.countUnivalSubtrees(&a) == 4) << endl;
    return 0;
}