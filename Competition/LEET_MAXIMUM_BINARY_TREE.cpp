#include "stdafx.h"

// https://leetcode.com/problems/maximum-binary-tree

#include "LEET_MAXIMUM_BINARY_TREE.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_MAXIMUM_BINARY_TREE
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
        TreeNode* constructMaximumBinaryTree(vector<int>& nums)
        {
            int n = nums.size();
            if (n == 0)
            {
                return nullptr;
            }

            vector<int> parent;
            vector<TreeNode*> nodes;
            parent.resize(n);
            nodes.resize(n);

            parent[0] = -1;
            nodes[0] = new TreeNode(nums[0]);
            TreeNode* root = nodes[0];
            
            for (int i = 1; i < n; i++)
            {
                nodes[i] = new TreeNode(nums[i]);
                nodes[i]->left = nullptr;
                nodes[i]->right = nullptr;

                int parent_candidate = i - 1;
                int child_candidate = -1;
                while (nums[i] > nums[parent_candidate])
                {
                    child_candidate = parent_candidate;
                    parent_candidate = parent[parent_candidate];

                    if (parent_candidate == -1)
                    {
                        break;
                    }
                }

                if (child_candidate != -1)
                {
                    nodes[i]->left = nodes[child_candidate];
                    parent[child_candidate] = i;
                }
                parent[i] = parent_candidate;
                if (parent_candidate != -1)
                {
                    nodes[parent_candidate]->right = nodes[i];
                }
                else
                {
                    root = nodes[i];
                }

            }

            return root;
        }
    };

    void Dump(TreeNode* node, int indent)
    {
        if (node != nullptr)
        {
            for (int i = 0; i < indent; i++)
            {
                cout << " ";
            }
            cout << node->val << endl;
            Dump(node->left, indent + 2);
            Dump(node->right, indent + 2);
        }
    }
};

using namespace _LEET_MAXIMUM_BINARY_TREE;

int LEET_MAXIMUM_BINARY_TREE()
{
    Solution solution;
    int test1[] = { 3,2,1,6,0,5 };
    TreeNode* answer = solution.constructMaximumBinaryTree(vector<int>(test1, test1 + _countof(test1)));
    Dump(answer, 0);
    return 0;
}