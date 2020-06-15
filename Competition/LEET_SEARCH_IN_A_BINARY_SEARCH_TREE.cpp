#include "stdafx.h"

// https://leetcode.com/problems/search-in-a-binary-search-tree/

#include "LEET_SEARCH_IN_A_BINARY_SEARCH_TREE.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_SEARCH_IN_A_BINARY_SEARCH_TREE
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

    class Solution
    {
    public:
        TreeNode* searchBST(TreeNode* root, int val)
        {
            if (root == NULL)
            {
                return NULL;
            }
            else
            {
                if (root->val < val)
                {
                    return searchBST(root->right, val);
                }
                else if (root->val == val)
                {
                    return root;
                }
                else
                {
                    return searchBST(root->left, val);
                }
            }
        }
    };
};

using namespace _LEET_SEARCH_IN_A_BINARY_SEARCH_TREE;

int LEET_SEARCH_IN_A_BINARY_SEARCH_TREE()
{
    Solution solution;
    TreeNode a(4);
    TreeNode b(2);
    TreeNode c(7);
    TreeNode d(1);
    TreeNode e(3);
    a.left = &b;
    a.right = &c;
    b.left = &d;
    b.right = &e;
    c.left = NULL;
    c.right = NULL;
    d.left = NULL;
    d.right = NULL;
    e.left = NULL;
    e.right = NULL;
    cout << (solution.searchBST(&a, 2) == &b) << endl;
    return 0;
}