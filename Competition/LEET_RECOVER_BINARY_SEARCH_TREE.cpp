#include "stdafx.h"

// https://leetcode.com/problems/recover-binary-search-tree/

#include "LEET_RECOVER_BINARY_SEARCH_TREE.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_RECOVER_BINARY_SEARCH_TREE
{
   struct TreeNode
   {
       int val;
       TreeNode *left;
       TreeNode *right;
       TreeNode(int x) : val(x), left(NULL), right(NULL) {}
   };
    class Solution {
    private:
        TreeNode* last;
        TreeNode* badBig;
        TreeNode* badSmall;
    public:
        void recoverTree(TreeNode* root)
        {
            last = nullptr;
            badBig = nullptr;
            badSmall = nullptr;
            walk(root);
            swap(badBig->val, badSmall->val);
        }
        void walk(TreeNode* root) {
            if (root == nullptr)
            {
                return;
            }
            else
            {
                walk(root->left);
                if (last != nullptr)
                {
                    if (root->val < last->val)
                    {
                        if (badBig == nullptr)
                        {
                            badBig = last;
                            badSmall = root;
                        }
                        else
                        {
                            badSmall = root;
                        }
                    }
                }
                if (root != nullptr)
                {
                    last = root;
                }
                walk(root->right);
            }
        }
    };
};

using namespace _LEET_RECOVER_BINARY_SEARCH_TREE;

int LEET_RECOVER_BINARY_SEARCH_TREE()
{
    Solution solution;
    TreeNode a(4);
    TreeNode b(2);
    TreeNode c(6);
    TreeNode d(7);
    TreeNode e(3);
    TreeNode f(5);
    TreeNode g(1);
    a.left = &b;
    a.right = &c;
    b.left = &d;
    b.right = &e;
    c.left = &f;
    c.right = &g;
    solution.recoverTree(&a);
    cout << a.val;
    cout << b.val;
    cout << c.val;
    cout << d.val;
    cout << e.val;
    cout << f.val;
    cout << g.val;
    return 0;
}