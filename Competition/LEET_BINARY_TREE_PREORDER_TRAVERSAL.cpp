#include "stdafx.h"

// https://leetcode.com/problems/binary-tree-inorder-traversal/

#include "LEET_BINARY_TREE_PREORDER_TRAVERSAL.h"

#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <algorithm>

using namespace std;

namespace _LEET_BINARY_TREE_PREORDER_TRAVERSAL
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
        vector<int> preorderTraversal(TreeNode *root)
        {
            vector<int> result;
            this->preorderTraversal(root, result);
            return result;
        }
    private:
        void preorderTraversal(TreeNode *root, vector<int>& result)
        {
            if (root != NULL)
            {
                result.push_back(root->val);
                this->preorderTraversal(root->left, result);
                this->preorderTraversal(root->right, result);
            }
        }
    };
}

using namespace _LEET_BINARY_TREE_PREORDER_TRAVERSAL;

int LEET_BINARY_TREE_PREORDER_TRAVERSAL()
{
    TreeNode a(1);
    TreeNode b(2);
    TreeNode c(3);
    a.left = NULL;    a.right = &c;
    b.left = NULL;    b.right = NULL;
    c.left = &b;      c.right = NULL;
    Solution solution;
    vector<int> result = solution.preorderTraversal(&a);
    for (vector<int>::iterator ri = result.begin(); ri != result.end(); ri++)
    {
        cout << *ri << endl;
    }

    return 0;
}
