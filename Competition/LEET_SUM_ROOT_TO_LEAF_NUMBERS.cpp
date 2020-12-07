#include "stdafx.h"

// https://leetcode.com/problems/sum-root-to-leaf-numbers/

#include "LEET_SUM_ROOT_TO_LEAF_NUMBERS.h"
#include <map>
#include <iostream>

using namespace std;

namespace _LEET_SUM_ROOT_TO_LEAF_NUMBERS
{
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };

    class Solution {
    private:
        int sumNumbers(int context, TreeNode *root)
        {
            int result = 0;
            bool is_leaf = true;
            if (root->left != NULL)
            {
                is_leaf = false;
                result += sumNumbers((context + root->val) * 10, root->left);
            }
            if (root->right != NULL)
            {
                is_leaf = false;
                result += sumNumbers((context + root->val) * 10, root->right);
            }
            if (is_leaf)
            {
                result += (context + root->val);
            }
            return result;
        }
    public:
        int sumNumbers(TreeNode *root)
        {
            if (root == NULL)
            {
                return 0;
            }
            else
            {
                return this->sumNumbers(0, root);
            }
        }
    };

};

using namespace _LEET_SUM_ROOT_TO_LEAF_NUMBERS;

int LEET_SUM_ROOT_TO_LEAF_NUMBERS()
{
    TreeNode* boot = new TreeNode(4);

    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);

    boot->left = root;
    Solution solution;
    cout << solution.sumNumbers(root) << endl;
    return 0;
}
