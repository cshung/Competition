#include "stdafx.h"

// https://leetcode.com/problems/symmetric-tree/

#include "LEET_SYMMETRIC_TREE.h"
#include <map>
#include <queue>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_SYMMETRIC_TREE
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
    private:
        bool isMirror(TreeNode* left, TreeNode* right)
        {
            if (left == NULL)
            {
                if (right == NULL)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else if (right == NULL)
            {
                return false;
            }
            else
            {
                if (left->val != right->val)
                {
                    return false;
                }

                if (!isMirror(left->left, right->right))
                {
                    return false;
                }

                if (!isMirror(left->right, right->left))
                {
                    return false;
                }

                return true;
            }
        }
    public:
        bool isSymmetric(TreeNode* root)
        {
            if (root == NULL)
            {
                return true;
            }

            return isMirror(root->left, root->right);
        }
    };

    TreeNode* ToTree(vector<int> serialized)
    {
        if (serialized.size() == 0)
        {
            return NULL;
        }
        unsigned int i = 1;
        TreeNode* root = new TreeNode(serialized[0]);
        queue<TreeNode*> queue;
        queue.push(root);
        while (i < serialized.size())
        {
            TreeNode* current = queue.front();
            queue.pop();
            int leftValue = serialized[i++];
            int rightValue = serialized[i++];
            if (leftValue != 10086) // 10086 represents #
            {
                TreeNode* leftNode = new TreeNode(leftValue);
                current->left = leftNode;
                queue.push(leftNode);
            }
            if (rightValue != 10086) // 10086 represents #
            {
                TreeNode* rightNode = new TreeNode(rightValue);
                current->right = rightNode;
                queue.push(rightNode);
            }
        }

        return root;
    }
};

using namespace _LEET_SYMMETRIC_TREE;

int LEET_SYMMETRIC_TREE()
{
    Solution solution;
    int case1Array[] = { 1, 2, 2, 3, 4, 4, 3, 10086, 10086, 10086, 10086, 10086, 10086, 10086, 10086 };
    TreeNode* case1 = ToTree(vector<int>(case1Array, case1Array + _countof(case1Array)));
    cout << solution.isSymmetric(case1) << endl;

    int case2Array[] = { 1, 2, 2, 10086, 3, 10086, 3, 10086, 10086, 10086, 10086 };
    TreeNode* case2 = ToTree(vector<int>(case2Array, case2Array + _countof(case2Array)));
    cout << !solution.isSymmetric(case2) << endl;

    return 0;
}