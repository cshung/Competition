#include "stdafx.h"

// https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/

#include "LEET_LOWEST_COMMON_ANCESTOR_OF_A_BINARY_TREE.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_LOWEST_COMMON_ANCESTOR_OF_A_BINARY_TREE
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
        void lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q, bool* pFound, bool* qFound, TreeNode** solution)
        {
            bool lpFound = false;
            bool lqFound = false;
            bool rpFound = false;
            bool rqFound = false;
            if (root == NULL)
            {
                return;
            }
            lowestCommonAncestor(root->left, p, q, &lpFound, &lqFound, solution);
            if (*solution != NULL)
            {
                return;
            }
            lowestCommonAncestor(root->right, p, q, &rpFound, &rqFound, solution);
            if (*solution != NULL)
            {
                return;
            }
            *pFound = lpFound || rpFound || (root == p);
            *qFound = lqFound || rqFound || (root == q);
            if (*pFound && *qFound)
            {
                *solution = root;
            }
        }
    public:
        TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
        {
            bool pFound = false;
            bool qFound = false;
            TreeNode* solution = NULL;
            lowestCommonAncestor(root, p, q, &pFound, &qFound, &solution);
            return solution;
        }
    };
};

using namespace _LEET_LOWEST_COMMON_ANCESTOR_OF_A_BINARY_TREE;

int LEET_LOWEST_COMMON_ANCESTOR_OF_A_BINARY_TREE()
{
    Solution s;
    TreeNode a(3);
    TreeNode b(5);
    TreeNode c(1);
    TreeNode d(6);
    TreeNode e(2);
    TreeNode f(0);
    TreeNode g(8);
    TreeNode h(7);
    TreeNode i(4);
    a.left = &b;
    a.right = &c;
    b.left = &d;
    b.right = &e;
    c.left = &f;
    c.right = &g;
    e.left = &h;
    e.right = &i;

    cout << (s.lowestCommonAncestor(&a, &b, &c) == &a) << endl;
    cout << (s.lowestCommonAncestor(&a, &b, &i) == &b) << endl;

    return 0;
}