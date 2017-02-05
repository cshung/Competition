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
        void findMode(TreeNode* root, vector<int>& result, int& max_count, int& last_node, int& last_count)
        {
            if (root == nullptr)
            {
                return;
            }

            if (root->left != nullptr)
            {
                findMode(root->left, result, max_count, last_node, last_count);
            }

            if (max_count == 0)
            {
                // This is possible only for the very first call
                result.push_back(root->val);
                max_count = 1;
                last_node = root->val;
                last_count = 1;
            }
            else
            {
                if (root->val == last_node)
                {
                    last_count++;
                }
                else
                {
                    last_node = root->val;
                    last_count = 1;
                }

                if (last_count == max_count)
                {
                    result.push_back(last_node);
                }
                else if (last_count > max_count)
                {
                    result.clear();
                    result.push_back(last_node);
                    max_count = last_count;
                }
            }

            if (root->right != nullptr)
            {
                findMode(root->right, result, max_count, last_node, last_count);
            }
        }

        vector<int> findMode(TreeNode* root)
        {
            vector<int> result;
            int max_count = 0;
            int last_node = 0;
            int last_count = 0;
            findMode(root, result, max_count, last_node, last_count);
            return result;
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
        cout << result[i] << endl;
    }
    return 0;
}