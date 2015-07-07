#include "stdafx.h"

// https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/

#include "LEET_CONSTRUCT_BINARY_TREE_FROM_PREORDER_AND_INORDER_TRAVERSAL.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_CONSTRUCT_BINARY_TREE_FROM_PREORDER_AND_INORDER_TRAVERSAL
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
        TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder)
        {
            return buildTree(preorder, 0, preorder.size(), inorder, 0, inorder.size());
        }
    private:
        TreeNode* buildTree(vector<int>& preorder, unsigned int preorderStart, unsigned int preorderEnds, vector<int>& inorder, unsigned int inorderStart, unsigned int inorderEnds)
        {
            if (preorderStart >= preorderEnds)
            {
                return NULL;
            }
            unsigned int inorderIndex = inorderStart;             
            for (;inorderIndex < inorderEnds; inorderIndex++)
            {
                if (inorder[inorderIndex] == preorder[preorderStart])
                {
                    break;  
                }
            }
            // inOrder [inorderStart, inorderIndex) is the left subtree.
            // inOrder [inorderIndex + 1, inorderEnds) is the right subtree.
            int leftSubTreeSize = inorderIndex - inorderStart;
            unsigned int preorderIndex = preorderStart + 1 + leftSubTreeSize;

            TreeNode* result = new TreeNode(preorder[preorderStart]);
            result->left = buildTree(preorder, preorderStart + 1, preorderIndex, inorder, inorderStart, inorderIndex);
            result->right = buildTree(preorder, preorderIndex, preorderEnds, inorder, inorderIndex + 1, inorderEnds);
            
            return result;
        }
    };
};

using namespace _LEET_CONSTRUCT_BINARY_TREE_FROM_PREORDER_AND_INORDER_TRAVERSAL;

int LEET_CONSTRUCT_BINARY_TREE_FROM_PREORDER_AND_INORDER_TRAVERSAL()
{
    Solution solution;
    int preorderArray[2] = { 1, 2 };
    int inorderArray[2] = { 2, 1 };
    vector<int> preorder(preorderArray, preorderArray + 2);
    vector<int> inorder(inorderArray, inorderArray + 2);
    TreeNode* result = solution.buildTree(preorder, inorder);
    return 0;
}