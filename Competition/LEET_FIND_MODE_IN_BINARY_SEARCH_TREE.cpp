#include "stdafx.h"

// https://leetcode.com/problems/find-mode-in-binary-search-tree/

#include "LEET_FIND_MODE_IN_BINARY_SEARCH_TREE.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_FIND_MODE_IN_BINARY_SEARCH_TREE
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
        vector<int> findMode(TreeNode* root)
        {
            vector<int> result;
            // TODO: Implementation
        }
    };
};

using namespace _LEET_FIND_MODE_IN_BINARY_SEARCH_TREE;

int LEET_FIND_MODE_IN_BINARY_SEARCH_TREE()
{
    Solution solution;
    TreeNode a(1);
    TreeNode b(2);
    TreeNode c(2);
    a.left = nullptr;
    a.right = &b;
    b.left = &c;
    b.right = nullptr;
    c.left = nullptr;
    c.right = nullptr;
    vector<int> result = solution.findMode(&a);
    for (int i = 0; i < result.size(); i++)
    {
        cout << result[i];
    }
    return 0;
}