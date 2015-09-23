#include "stdafx.h"

// https://leetcode.com/problems/validate-binary-search-tree/

#include "LEET_VALIDATE_BINARY_SEARCH_TREE.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

namespace _LEET_VALIDATE_BINARY_SEARCH_TREE
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
    private:
        bool isValidBST(TreeNode* root, bool hasLowerBound, int lowerBound, bool hasUpperBound, int upperBound)
        {
            if (hasLowerBound && root->val <= lowerBound)
            {
                return false;
            }
            if (hasUpperBound && root->val >= upperBound)
            {
                return false;
            }
            if (root->left != NULL)
            {
                if (!isValidBST(root->left, hasLowerBound, lowerBound, true, root->val))
                {
                    return false;
                }
            }
            if (root->right != NULL)
            {
                if (!isValidBST(root->right, true, root->val, hasUpperBound, upperBound))
                {
                    return false;
                }
            }

            return true;
        }
    public:
        bool isValidBST(TreeNode* root)
        {
            if (root == NULL)
            {
                return true;
            }
            return isValidBST(root, false, 0, false, 0);
        }
    };
};

using namespace _LEET_VALIDATE_BINARY_SEARCH_TREE;

int LEET_VALIDATE_BINARY_SEARCH_TREE()
{
    Solution s;
    TreeNode a(2);
    TreeNode b(1);
    TreeNode c(3);
    a.left = &b;
    a.right = &c;
    cout << s.isValidBST(&a) << endl;
    return 0;
}