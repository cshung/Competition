#include "stdafx.h"

// https://leetcode.com/problems/sum-of-root-to-leaf-binary-numbers/

#include "LEET_SUM_OF_ROOT_TO_LEAF_BINARY_NUMBERS.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_SUM_OF_ROOT_TO_LEAF_BINARY_NUMBERS
{
    struct TreeNode
    {
        int val;
        TreeNode* left;
        TreeNode* right;
        TreeNode() : val(0), left(nullptr), right(nullptr) {}
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
        TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
    };
    class Solution {
    public:
        int sumRootToLeaf(TreeNode* root) {
            if (root == NULL)
            {
                return 0;
            }
            return sumRootToLeaf(0, root);
        }
    private:
        int sumRootToLeaf(int ancestor, TreeNode* root)
        {
            int val = ancestor + root->val;
            if (root->left == NULL && root->right == NULL)
            {
                return val;
            }
            else
            {
                int next = val * 2;
                int result = 0;
                if (root->left != NULL)
                {
                    result += sumRootToLeaf(next, root->left);
                }
                if (root->right != NULL)
                {
                    result += sumRootToLeaf(next, root->right);
                }
                return result;
            }
        }
    };
};

using namespace _LEET_SUM_OF_ROOT_TO_LEAF_BINARY_NUMBERS;

int LEET_SUM_OF_ROOT_TO_LEAF_BINARY_NUMBERS()
{
    Solution solution;
    TreeNode a(1);
    TreeNode b(0);
    TreeNode c(1);
    TreeNode d(0);
    TreeNode e(1);
    TreeNode g(0);
    TreeNode f(1);
    a.left = &b;
    a.right = &c;
    b.left = &d;
    b.right = &e;
    c.left = &f;
    c.right = &g;
    d.left = NULL;
    d.right = NULL;
    e.left = NULL;
    e.right = NULL;
    f.left = NULL;
    f.right = NULL;
    g.left = NULL;
    g.right = NULL;
    cout << solution.sumRootToLeaf(&a) << endl;

    return 0;
}