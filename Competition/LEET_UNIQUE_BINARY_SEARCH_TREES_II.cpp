#include "stdafx.h"

// https://leetcode.com/problems/unique-binary-search-trees-ii/

#include "LEET_UNIQUE_BINARY_SEARCH_TREES_II.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_UNIQUE_BINARY_SEARCH_TREES_II
{
    struct TreeNode
    {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };

    class Solution {
    public:
        vector<TreeNode*> generateTrees(int min, int max)
        {
            vector<TreeNode*> result;
            if (max < min)
            {
                result.push_back(NULL);
                return result;
            }
            for (int i = min; i <= max; i++)
            {
                vector<TreeNode*> leftSubtrees = generateTrees(min, i - 1);
                vector<TreeNode*> rightSubtrees = generateTrees(i + 1, max);

                for (size_t j = 0; j < leftSubtrees.size(); j++)
                {
                    for (size_t k = 0; k < rightSubtrees.size(); k++)
                    {
                        TreeNode* root = new TreeNode(i);
                        root->left = leftSubtrees[j];
                        root->right = rightSubtrees[k];
                        result.push_back(root);
                    }
                }
            }
            return result;
        }
        vector<TreeNode*> generateTrees(int n)
        {
            if (n == 0)
            {
                vector<TreeNode*> result;
                return result;
            }
            return generateTrees(1, n);
        }
    };

    void ShowTree(TreeNode* tree)
    {
        if (tree == NULL)
        {
            cout << "#";
        }
        else
        {
            cout << "(" << tree->val;
            cout << ", ";
            ShowTree(tree->left);
            cout << ", ";
            ShowTree(tree->right);
            cout << ")";
        }
    }
};

using namespace _LEET_UNIQUE_BINARY_SEARCH_TREES_II;

int LEET_UNIQUE_BINARY_SEARCH_TREES_II()
{
    Solution solution;
    vector<TreeNode*> trees = solution.generateTrees(3);
    for (size_t i = 0; i < trees.size(); i++)
    {
        ShowTree(trees[i]);
        cout << endl;
    }
    return 0;
}