#include "stdafx.h"

// https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/

#include "LEET_CONSTRUCT_BINARY_TREE_FROM_INORDER_AND_POSTORDER_TRAVERSAL.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_CONSTRUCT_BINARY_TREE_FROM_INORDER_AND_POSTORDER_TRAVERSAL
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
    public:
        TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder)
        {
            return buildTree(inorder, 0, inorder.size(), postorder, 0, postorder.size());
        }
    private:
        TreeNode* buildTree(vector<int>& inorder, unsigned int inorderStart, unsigned int inorderEnds, vector<int>& postorder, unsigned int postorderStart, unsigned int postorderEnds)
        {
            if (postorderStart >= postorderEnds)
            {
                return NULL;
            }
            unsigned int inorderIndex = inorderStart;
            for (; inorderIndex < inorderEnds; inorderIndex++)
            {
                if (inorder[inorderIndex] == postorder[postorderEnds - 1])
                {
                    break;
                }
            }
            // inOrder [inorderStart, inorderIndex) is the left subtree.
            // inOrder [inorderIndex + 1, inorderEnds) is the right subtree.
            int leftSubTreeSize = inorderIndex - inorderStart;
            unsigned int postorderIndex = postorderStart + leftSubTreeSize;

            TreeNode* result = new TreeNode(postorder[postorderEnds - 1]);
            result->left = buildTree(inorder, inorderStart, inorderIndex, postorder, postorderStart, postorderIndex);
            result->right = buildTree(inorder, inorderIndex + 1, inorderEnds, postorder, postorderIndex, postorderEnds - 1);

            return result;
        }
    };
};

using namespace _LEET_CONSTRUCT_BINARY_TREE_FROM_INORDER_AND_POSTORDER_TRAVERSAL;

int LEET_CONSTRUCT_BINARY_TREE_FROM_INORDER_AND_POSTORDER_TRAVERSAL()
{
    Solution solution;
    int inorderArray[3] = { 1, 2, 3 };
    int postorderArray[3] = { 1, 3, 2 };
    vector<int> inorder(inorderArray, inorderArray + 3);
    vector<int> postorder(postorderArray, postorderArray + 3);
    TreeNode* result = solution.buildTree(inorder, postorder);
    return 0;
}