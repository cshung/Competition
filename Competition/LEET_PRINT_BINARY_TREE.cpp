#include "stdafx.h"

// https://leetcode.com/problems/print-binary-tree

#include "LEET_PRINT_BINARY_TREE.h"
#include <map>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_PRINT_BINARY_TREE
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
        vector<vector<string>> printTree(TreeNode* root)
        {
            int height;
            getHeight(root, &height);
            int width = 0;
            for (int i = 0; i < height; i++)
            {
                width = 2 * width + 1;
            }
            vector<vector<string>> result;
            result.resize(height);
            for (int i = 0; i < height; i++)
            {
                result[i].resize(width);
            }
            fillTree(root, width, 0, 0, result);
            return result;
        }

        void getHeight(TreeNode* node, int* pHeight)
        {
            if (node == nullptr)
            {
                *pHeight = 0;
            }
            else
            {
                int leftHeight;
                int rightHeight;
                getHeight(node->left, &leftHeight);
                getHeight(node->right, &rightHeight);
                *pHeight = max(leftHeight, rightHeight) + 1;
            }
        }

        void fillTree(TreeNode* node, int width, int height, int offset, vector<vector<string>>& result)
        {
            if (node != nullptr)
            {
                ostringstream sout;
                int mid = width / 2;
                sout << node->val;
                result[height][offset + mid] = sout.str();
                fillTree(node->left, mid, height + 1, offset, result);
                fillTree(node->right, mid, height + 1, mid + 1 + offset, result);
            }
        }
    };
};

using namespace _LEET_PRINT_BINARY_TREE;

int LEET_PRINT_BINARY_TREE()
{
    Solution solution;
    TreeNode a(2);
    TreeNode b(1);
    TreeNode c(3);
    a.left = &b;
    a.right = &c;
    b.left = nullptr;
    b.right = nullptr;
    c.left = nullptr;
    c.right = nullptr;
    vector<vector<string>> result = solution.printTree(&a);
    for (int i = 0; i < result.size(); i++)
    {
        for (int j = 0; j < result[i].size(); j++)
        {
            cout << "'" << result[i][j] << "',";
        }
        cout << endl;
    }
    return 0;
}