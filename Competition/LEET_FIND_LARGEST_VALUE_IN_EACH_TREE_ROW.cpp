#include "stdafx.h"

// https://leetcode.com/problems/find-largest-value-in-each-tree-row/

#include "LEET_FIND_LARGEST_VALUE_IN_EACH_TREE_ROW.h"
#include <map>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_FIND_LARGEST_VALUE_IN_EACH_TREE_ROW
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
        void largestValues(TreeNode* root, int depth, vector<int>& result)
        {
            if (root == nullptr)
            {
                return;
            }
            if (result.size() > depth)
            {
                result[depth] = max(result[depth], root->val);
            }
            else
            {
                result.push_back(root->val);
            }
            largestValues(root->left, depth + 1, result);
            largestValues(root->right, depth + 1, result);
        }
        vector<int> largestValues(TreeNode* root)
        {
            vector<int> result;
            largestValues(root, 0, result);
            return result;
        }
    };
};

using namespace _LEET_FIND_LARGEST_VALUE_IN_EACH_TREE_ROW;

int LEET_FIND_LARGEST_VALUE_IN_EACH_TREE_ROW()
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
    c.right = &f;
    auto result = solution.largestValues(&a);
    for (auto&& r : result)
    {
        cout << r << endl;
    }
    return 0;
}