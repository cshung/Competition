#include "stdafx.h"

// https://leetcode.com/problems/flatten-binary-tree-to-linked-list/

#include "LEET_FLATTEN_BINARY_TREE_TO_LINKED_LIST.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_FLATTEN_BINARY_TREE_TO_LINKED_LIST
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
        TreeNode* flattenWithLast(TreeNode* root)
        {
            TreeNode* left = root->left;
            TreeNode* right = root->right;
            root->left = NULL;
            root->right = NULL;
            TreeNode* last = root;
            if (left != NULL)
            {
                last->right = left;
                last = flattenWithLast(left);
            }
            if (right != NULL)
            {
                last->right = right;
                last = flattenWithLast(right);
            }
            return last;
        }
    public:
        void flatten(TreeNode* root) {
            if (root == NULL)
            {
                return;
            }
            flattenWithLast(root);
        }
    };
};

using namespace _LEET_FLATTEN_BINARY_TREE_TO_LINKED_LIST;

int LEET_FLATTEN_BINARY_TREE_TO_LINKED_LIST()
{
    Solution solution;
    TreeNode a(1);
    TreeNode b(2);
    TreeNode c(3);
    TreeNode d(4);
    TreeNode e(5);
    TreeNode f(6);
    a.left = &b;
    b.left = &c;
    b.right = &d;
    a.right = &e;
    e.right = &f;
    solution.flatten(&a);
    TreeNode* curr = &a;
    while (curr != NULL)
    {
        cout << curr->val;
        curr = curr->right;
    }
    cout << endl;
    return 0;
}