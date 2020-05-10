#include "stdafx.h"

// https://leetcode.com/problems/cousins-in-binary-tree/

#include "LEET_COUSINS_IN_BINARY_TREE.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_COUSINS_IN_BINARY_TREE
{
    struct TreeNode
    {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode() : val(0), left(nullptr), right(nullptr) {}
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
        TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };

    class Solution {
    public:
        bool isCousins(TreeNode* root, int x, int y) {
            int xParent;
            int yParent;
            int xDepth;
            int yDepth;
            find(root, x, -1, 0, &xParent, &xDepth);
            find(root, y, -1, 0, &yParent, &yDepth);
            return (xParent != yParent) && (xDepth == yDepth);
        }
    private:
        bool find(TreeNode* root, int x, int parent, int depth, int* foundParent, int* foundDepth)
        {
            if (root == NULL)
            {
                return false;
            }
            if (root->val == x)
            {
                *foundParent = parent;
                *foundDepth = depth;
                return true;
            }
            if (find(root->left, x, root->val, depth + 1, foundParent, foundDepth))
            {
                return true;
            }
            else
            {
                return find(root->right, x, root->val, depth + 1, foundParent, foundDepth);
            }
        }
    };
};

using namespace _LEET_COUSINS_IN_BINARY_TREE;

int LEET_COUSINS_IN_BINARY_TREE()
{
    TreeNode a(1);
    TreeNode b(2);
    TreeNode c(3);
    TreeNode d(4);
    TreeNode e(5);
    a.left = &b;
    a.right = &c;
    b.left = NULL;
    b.right = &d;
    c.left = NULL;
    c.right = &e;
    d.left = NULL;
    d.right = NULL;
    e.left = NULL;
    e.right = NULL;
    Solution s;
    cout << s.isCousins(&a, 5, 4) << endl;
    return 0;
}