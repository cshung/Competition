#include "stdafx.h"

// https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/

#include "LEET_BINARY_TREE_ZIGZAG_LEVEL_ORDER_TRAVERSAL.h"
#include <stack>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_BINARY_TREE_ZIGZAG_LEVEL_ORDER_TRAVERSAL
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
        vector<vector<int>> zigzagLevelOrder(TreeNode* root)
        {
            vector<vector<int>> result;
            stack<TreeNode*> buffer1;
            stack<TreeNode*> buffer2;
            if (root == nullptr)
            {
                return result;
            }
            else
            {
                stack<TreeNode*>* pBuffer1 = &buffer1;
                stack<TreeNode*>* pBuffer2 = &buffer2;
                buffer1.push(root);
                bool flip = true;
                while (true)
                {
                    vector<int> row;
                    stack<TreeNode*>& last_child = *pBuffer1;
                    stack<TreeNode*>& this_child = *pBuffer2;
                    if (last_child.size() == 0)
                    {
                        break;
                    }
                    while (last_child.size() > 0)
                    {
                        TreeNode* current_node = last_child.top();
                        last_child.pop();
                        row.push_back(current_node->val);
                        if (flip)
                        {
                            if (current_node->left != nullptr)
                            {
                                this_child.push(current_node->left);
                            }
                            if (current_node->right != nullptr)
                            {
                                this_child.push(current_node->right);
                            }
                        }
                        else
                        {
                            if (current_node->right != nullptr)
                            {
                                this_child.push(current_node->right);
                            }
                            if (current_node->left != nullptr)
                            {
                                this_child.push(current_node->left);
                            }
                        }
                    }
                    result.push_back(row);
                    flip = !flip;
                    swap(pBuffer1, pBuffer2);
                }

                return result;
            }
        }
    };
};

using namespace _LEET_BINARY_TREE_ZIGZAG_LEVEL_ORDER_TRAVERSAL;

int LEET_BINARY_TREE_ZIGZAG_LEVEL_ORDER_TRAVERSAL()
{
    Solution solution;
    TreeNode a(3);
    TreeNode b(9);
    TreeNode c(20);
    TreeNode d(15);
    TreeNode e(7);
    a.left = &b;
    a.right = &c;
    c.left = &d;
    c.right = &e;
    vector<vector<int>> answer = solution.zigzagLevelOrder(&a);
    for (auto&& row : answer)
    {
        for (auto&& val : row)
        {
            cout << val << " ";
        }
        cout << endl;
    }
    return 0;
}