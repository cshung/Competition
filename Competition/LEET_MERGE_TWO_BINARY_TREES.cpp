#include "stdafx.h"

// https://leetcode.com/problems/merge-two-binary-trees

#include "LEET_MERGE_TWO_BINARY_TREES.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_MERGE_TWO_BINARY_TREES
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
        TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2)
        {
            if (t1 == nullptr)
            {
                return t2;
            }
            else if (t2 == nullptr)
            {
                return t1;
            }
            else
            {
                TreeNode* left = mergeTrees(t1->left, t2->left);
                TreeNode* right = mergeTrees(t1->right, t2->right);
                TreeNode* result = new TreeNode(t1->val + t2->val);
                result->left = left;
                result->right = right;
                return result;
            }
        }
    };
};

using namespace _LEET_MERGE_TWO_BINARY_TREES;

int LEET_MERGE_TWO_BINARY_TREES()
{
    Solution solution;
    TreeNode l1(1);
    TreeNode l2(3);
    TreeNode l3(2);
    TreeNode l4(5);

    TreeNode r1(2);
    TreeNode r2(1);
    TreeNode r3(3);
    TreeNode r4(4);
    TreeNode r5(7);

    l1.left = &l2;
    l1.right = &l3;
    l2.left = &l4;
    l2.right = nullptr;
    l3.left = nullptr;
    l3.right = nullptr;
    l4.left = nullptr;
    l4.right = nullptr;

    r1.left = &r2;
    r1.right = &r3;
    r2.left = nullptr;
    r2.right = &r4;
    r3.left = nullptr;
    r3.right = &r5;
    r4.left = nullptr;
    r4.right = nullptr;
    r5.left = nullptr;
    r5.right = nullptr;

    TreeNode* answer = solution.mergeTrees(&l1, &r1);
    cout << answer->val << endl;
    cout << answer->left->val << endl;
    cout << answer->right->val << endl;
    cout << answer->left->left->val << endl;
    cout << answer->left->right->val << endl;
    cout << answer->right->right->val << endl;
    return 0;
}