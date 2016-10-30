#include "stdafx.h"

// https://leetcode.com/problems/path-sum-ii/

#include "LEET_PATH_SUM_II.h"
#include <queue>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_PATH_SUM_II
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
        vector<vector<int>> pathSum(TreeNode* root, int sum)
        {
            vector<vector<int>> result;
            vector<int> path;
            pathSum(root, sum, 0, path, result);
            return result;
        }
    private:
        void pathSum(TreeNode* root, int target, int sum, vector<int>& path, vector<vector<int>>& result)
        {
            if (root == nullptr)
            {
                return;
            }

            sum = sum + root->val;
            path.push_back(root->val);
            if (root->left == nullptr && root->right == nullptr && sum == target)
            {
                result.push_back(path);
            }
            this->pathSum(root->left, target, sum, path, result);
            this->pathSum(root->right, target, sum, path, result);
            path.pop_back();
        }
    };
};

using namespace _LEET_PATH_SUM_II;

int LEET_PATH_SUM_II()
{
    Solution solution;
    TreeNode a(5);
    TreeNode b(4);
    TreeNode c(8);
    TreeNode d(11);
    TreeNode e(13);
    TreeNode f(4);
    TreeNode g(7);
    TreeNode h(2);
    TreeNode i(5);
    TreeNode j(1);
    a.left = &b;
    a.right = &c;
    b.left = &d;
    c.left = &e;
    c.right = &f;
    d.left = &g;
    d.right = &h;
    f.left = &i;
    f.right = &j;
    vector<vector<int>> answer = solution.pathSum(&a, 22);
    for (auto&& p : answer)
    {
        for (auto&& e : p)
        {
            cout << e << ",";
        }
        cout << endl;
    }
    return 0;
}