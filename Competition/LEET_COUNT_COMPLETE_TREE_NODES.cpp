#include "stdafx.h"

// https://leetcode.com/problems/count-complete-tree-nodes/

#include "LEET_COUNT_COMPLETE_TREE_NODES.h"
#include <stack>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_COUNT_COMPLETE_TREE_NODES
{
    struct TreeNode
    {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int x) : val(x), left(NULL), right(NULL)
        {
        }
    };

    class Solution
    {
    public:
        int leftDepth(TreeNode* node)
        {
            if (node == NULL)
            {
                return 0;
            }
            else
            {
                return 1 + leftDepth(node->left);
            }
        }

        int rightDepth(TreeNode* node)
        {
            if (node == NULL)
            {
                return 0;
            }
            else
            {
                return 1 + rightDepth(node->right);
            }
        }
        int countNodes(TreeNode* root, int leftDepthValue, int rightDepthValue)
        {
            int actualLeftDepthValue = leftDepthValue == -1 ? leftDepth(root) : leftDepthValue;
            int actualRightDepthValue = rightDepthValue == -1 ? rightDepth(root) : rightDepthValue;
            if (actualLeftDepthValue == actualRightDepthValue)
            {
                return (1 << actualLeftDepthValue) - 1;
            }
            else
            {
                return 1 + countNodes(root->left, actualLeftDepthValue - 1, -1) + countNodes(root->right, -1, actualRightDepthValue - 1);
            }
        }

        int countNodes(TreeNode* root)
        {
            return countNodes(root, -1, -1);
        }

    };

    TreeNode* BuildFullTree(int size)
    {
        if (size == 0)
        {
            return NULL;
        }
        else
        {
            TreeNode* leftSubTree = BuildFullTree(size - 1);
            TreeNode* rightSubTree = BuildFullTree(size - 1);
            TreeNode* result = new TreeNode(0);
            result->left = leftSubTree;
            result->right = rightSubTree;
            return result;
        }

    }
};

using namespace _LEET_COUNT_COMPLETE_TREE_NODES;

int LEET_COUNT_COMPLETE_TREE_NODES()
{
    Solution solution;
    int size = 3;
    TreeNode* test = BuildFullTree(size);
    TreeNode* left = test;
    for (int i = 0; i < size - 1; i++)
    {
        left = left->left;
    }
    left->left = new TreeNode(0);
    cout << solution.countNodes(test) << endl;
    return 0;
}