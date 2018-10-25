#include "stdafx.h"

// https://leetcode.com/problems/maximum-width-of-binary-tree

#include "LEET_MAXIMUM_WIDTH_OF_BINARY_TREE.h"
#include <map>
#include <queue>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_MAXIMUM_WIDTH_OF_BINARY_TREE
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
        int widthOfBinaryTree(TreeNode* root)
        {
            vector<int> min_by_layer;
            vector<int> max_by_layer;
            helper(root, 0, 0, min_by_layer, max_by_layer);
            int answer = -1;
            for (int i = 0; i < min_by_layer.size(); i++)
            {
                answer = max(answer, max_by_layer[i] - min_by_layer[i] + 1);
            }
            return answer;
        }

        void helper(TreeNode* root, int value, int layer, vector<int>& min_by_layer, vector<int>& max_by_layer)
        {
            if (root == nullptr)
            {
                return;
            }
            if (layer < min_by_layer.size())
            {
                min_by_layer[layer] = min(min_by_layer[layer], value);
                max_by_layer[layer] = max(max_by_layer[layer], value);
            }
            else
            {
                min_by_layer.push_back(value);
                max_by_layer.push_back(value);
            }
            helper(root->left, value * 2, layer + 1, min_by_layer, max_by_layer);
            helper(root->right, value * 2 + 1, layer + 1, min_by_layer, max_by_layer);
        }
    };
};

using namespace _LEET_MAXIMUM_WIDTH_OF_BINARY_TREE;

int LEET_MAXIMUM_WIDTH_OF_BINARY_TREE()
{
    Solution solution;
    TreeNode a(1);
    TreeNode b(3);
    TreeNode c(2);
    TreeNode d(5);
    TreeNode e(3);
    TreeNode f(9);
    a.left = &b;
    a.right = &c;
    b.left = &d;
    b.right = &e;
    c.left = nullptr;
    c.right = &f;
    cout << solution.widthOfBinaryTree(&a) << endl;
    return 0;
}