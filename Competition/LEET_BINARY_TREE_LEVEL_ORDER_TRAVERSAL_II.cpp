#include "stdafx.h"

// https://leetcode.com/problems/binary-tree-level-order-traversal-ii/

#include "LEET_BINARY_TREE_LEVEL_ORDER_TRAVERSAL_II.h"

#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <algorithm>

using namespace std;

namespace _LEET_BINARY_TREE_LEVEL_ORDER_TRAVERSAL_II
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
        vector<vector<int> > levelOrderBottom(TreeNode *root)
        {
            vector<vector<int> > result;


            vector<TreeNode*> list1;
            vector<TreeNode*> list2;

            vector<TreeNode*>& this_layer = list1;
            vector<TreeNode*>& next_layer = list2;

            if (root != NULL)
            {
                this_layer.push_back(root);
            }

            while (this_layer.size() != 0)
            {
                vector<int> this_layer_values;
                for (unsigned int i = 0; i < this_layer.size(); i++)
                {
                    this_layer_values.push_back(this_layer[i]->val);
                    TreeNode* left_child = this_layer[i]->left;
                    if (left_child != NULL)
                    {
                        next_layer.push_back(left_child);
                    }
                    TreeNode* right_child = this_layer[i]->right;
                    if (right_child != NULL)
                    {
                        next_layer.push_back(right_child);
                    }
                }

                this_layer.clear();
                swap(this_layer, next_layer);
                result.push_back(this_layer_values);
            }

            reverse(result.begin(), result.end());
            return result;
        }
    };
}

using namespace _LEET_BINARY_TREE_LEVEL_ORDER_TRAVERSAL_II;

int LEET_BINARY_TREE_LEVEL_ORDER_TRAVERSAL_II()
{
    TreeNode a(3);
    TreeNode b(9);
    TreeNode c(20);
    TreeNode d(15);
    TreeNode e(7);

    a.left = &b;
    a.right = &c;
    b.left = NULL;
    b.right = NULL;
    c.left = &d;
    c.right = &e;
    d.left = NULL;
    d.right = NULL;
    e.left = NULL;
    e.right = NULL;

    Solution solution;
    vector<vector<int> > result = solution.levelOrderBottom(&a);
    for (unsigned int i = 0; i < result.size(); i++)
    {
        for (unsigned int j = 0; j < result[i].size(); j++)
        {
            cout << result[i][j] << " ";
        }

        cout << endl;
    }
    return 0;
}
