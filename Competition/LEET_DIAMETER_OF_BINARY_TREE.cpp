#include "stdafx.h"

// https://leetcode.com/problems/diameter-of-binary-tree

#include "LEET_DIAMETER_OF_BINARY_TREE.h"
#include <map>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_DIAMETER_OF_BINARY_TREE
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
        void diameterOfBinaryTree(TreeNode* node, int* pSolution, int* pHeight)
        {
            if (node == nullptr)
            {
                *pSolution = 0;
                *pHeight = 0;
            }
            else
            {
                int leftSolution;
                int leftHeight;
                int rightSolution;
                int rightHeight;

                diameterOfBinaryTree(node->left, &leftSolution, &leftHeight);
                diameterOfBinaryTree(node->right, &rightSolution, &rightHeight);

                *pHeight = 1 + max(leftHeight, rightHeight);
                *pSolution = max(max(leftHeight + 1 + rightHeight, leftSolution), rightSolution);
            }
        }
        int diameterOfBinaryTree(TreeNode* root)
        {
            if (root == nullptr)
            {
                return 0;
            }
            int solution;
            int height;
            diameterOfBinaryTree(root, &solution, &height);
            return solution - 1;
        }
    };
};

using namespace _LEET_DIAMETER_OF_BINARY_TREE;

int LEET_DIAMETER_OF_BINARY_TREE()
{
    Solution s;
    TreeNode a(1);
    TreeNode b(2);
    TreeNode c(3);
    TreeNode d(4);
    TreeNode e(5);
    a.left = &b;
    a.right = &c;
    b.left = &d;
    b.right = &e;
    c.left = nullptr;
    c.right = nullptr;
    d.left = nullptr;
    d.right = nullptr;
    e.left = nullptr;
    e.right = nullptr;
    cout << s.diameterOfBinaryTree(&a) << endl;
    return 0;
}