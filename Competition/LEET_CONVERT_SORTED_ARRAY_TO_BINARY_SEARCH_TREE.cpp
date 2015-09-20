#include "stdafx.h"

// https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/

#include "LEET_CONVERT_SORTED_ARRAY_TO_BINARY_SEARCH_TREE.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

namespace _LEET_CONVERT_SORTED_ARRAY_TO_BINARY_SEARCH_TREE
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
        TreeNode* sortedArrayToBST(vector<int>& nums)
        {
            int size = nums.size();
            if (size == 0)
            {
                return NULL;
            }

            /* allocate nodes and index them */
            TreeNode** all_nodes = new TreeNode*[size];
            for (int i = 0; i < size; i++)
            {
                all_nodes[i] = new TreeNode(-1);
            }

            all_nodes = all_nodes - 1;

            /* build the tree structure */
            TreeNode* root = all_nodes[1];
            for (int i = 1; i <= size; i++)
            {
                int left = i * 2;
                int right = left + 1;
                if (left <= size)
                {
                    all_nodes[i]->left = all_nodes[left];
                }
                else
                {
                    all_nodes[i]->left = NULL;
                }
                if (right <= size)
                {
                    all_nodes[i]->right = all_nodes[right];
                }
                else
                {
                    all_nodes[i]->right = NULL;
                }
            }

            /* build the tree values */
            int t = 1;
            int j = 0;
            while (t * 2 <= size)
            {
                t = t * 2;
            }

            while (t != 0)
            {
                all_nodes[t]->val = nums[j++];
                if (t * 2 + 1 <= size)
                {
                    t = t * 2 + 1;
                    while (t * 2 <= size)
                    {
                        t = t * 2;
                    }
                }
                else
                {
                    while (t % 2 == 1)
                    {
                        t = t / 2;
                    }
                    t = t / 2;
                }
            }

            all_nodes = all_nodes + 1;
            delete[] all_nodes;
            return root;
        }
    };
};

using namespace _LEET_CONVERT_SORTED_ARRAY_TO_BINARY_SEARCH_TREE;

int LEET_CONVERT_SORTED_ARRAY_TO_BINARY_SEARCH_TREE()
{
    int case1[] = { 1, 2, 3, 4, 5, 6, 7, 8 };

    Solution s;
    TreeNode* root = s.sortedArrayToBST(vector<int>(case1, case1 + _countof(case1)));
    return 0;
}