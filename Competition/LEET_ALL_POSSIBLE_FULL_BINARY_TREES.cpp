#include "stdafx.h"

// https://leetcode.com/problems/all-possible-full-binary-trees

#include "LEET_ALL_POSSIBLE_FULL_BINARY_TREES.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_ALL_POSSIBLE_FULL_BINARY_TREES
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
        vector<TreeNode*> allPossibleFBT(int N)
        {
            vector<TreeNode*> solution;
            if (N == 0)
            {
                solution.push_back(nullptr);
            }
            else if (N == 1)
            {
                solution.push_back(new TreeNode(0));
            }
            else
            {
                for (int left = 1; left < N - 1; left++)
                {
                    int right = N - 1 - left;
                    vector<TreeNode*> leftTrees = this->allPossibleFBT(left);
                    vector<TreeNode*> rightTrees = this->allPossibleFBT(right);
                    for (auto leftTree : leftTrees)
                    {
                        for (auto rightTree : rightTrees)
                        {
                            TreeNode* root = new TreeNode(0);
                            root->left = leftTree;
                            root->right = rightTree;
                            solution.push_back(root);
                        }
                    }
                }
            }
            return solution;
        }
    };
};

using namespace _LEET_ALL_POSSIBLE_FULL_BINARY_TREES;

int LEET_ALL_POSSIBLE_FULL_BINARY_TREES()
{
    Solution solution;
    for (int i = 0; i < 10; i++)
    {
        cout << solution.allPossibleFBT(i).size() << endl;
    }
    return 0;
}