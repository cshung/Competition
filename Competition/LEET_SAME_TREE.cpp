#include "stdafx.h"

// https://leetcode.com/problems/same-tree/

#include "LEET_SAME_TREE.h"

#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <algorithm>

using namespace std;

namespace _LEET_SAME_TREE
{
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };
    class Solution {
    public:
        bool isSameTree(TreeNode *p, TreeNode *q) {
            if (p == NULL)
            {
                if (q == NULL)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            } 
            else
            {
                if (q == NULL)
                {
                    return false;
                }
                else
                {
                    return p->val == q->val && isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
                }
            }
        }
    };
}

using namespace _LEET_SAME_TREE;

int LEET_SAME_TREE()
{
    TreeNode a(1);
    TreeNode b(1);
    TreeNode c(1);
    TreeNode d(1);
    a.left = &b;    a.right = NULL;
    b.left = &c;    b.right = &d;
    c.left = NULL;    c.right = NULL;
    d.left = NULL;    d.right = NULL;
    Solution solution;
    cout << solution.isSameTree(&a, &a) << endl;
    cout << solution.isSameTree(&a, &b) << endl;

    return 0;
}
