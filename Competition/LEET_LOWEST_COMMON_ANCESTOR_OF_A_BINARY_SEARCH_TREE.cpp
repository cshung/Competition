#include "stdafx.h"

// https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/

#include "LEET_LOWEST_COMMON_ANCESTOR_OF_A_BINARY_SEARCH_TREE.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_LOWEST_COMMON_ANCESTOR_OF_A_BINARY_SEARCH_TREE
{
    struct TreeNode
    {
        int val;
        TreeNode* left;
        TreeNode* right;
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };
    class Solution
    {
    private:
        void lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q, TreeNode** solution)
        {
            if (*solution != NULL)
            {
                return;
            }
            bool pRight = p->val > root->val;
            bool qRight = q->val > root->val;
            bool pMatch = p == root;
            bool qMatch = q == root;
            bool pLeft = p->val < root->val;
            bool qLeft = q->val < root->val;

            if (pRight && qLeft)
            {
                *solution = root;
            }
            if (pLeft && qRight)
            {
                *solution = root;
            }
            if (pMatch || qMatch)
            {
                *solution = root;
            }
            if (pRight && qRight)
            {
                lowestCommonAncestor(root->right, p, q, solution);
            }
            else
            {
                lowestCommonAncestor(root->left, p, q, solution);
            }
        }
    public:
        TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
        {
            TreeNode* solution = NULL;
            lowestCommonAncestor(root, p, q, &solution);
            return solution;
        }
    };
};

using namespace _LEET_LOWEST_COMMON_ANCESTOR_OF_A_BINARY_SEARCH_TREE;

int LEET_LOWEST_COMMON_ANCESTOR_OF_A_BINARY_SEARCH_TREE()
{
    Solution solution;
    TreeNode a(2);
    TreeNode b(1);
    a.left = &b;
    cout << solution.lowestCommonAncestor(&a, &a, &b)->val << endl;
    return 0;
}