#include "stdafx.h"

// https://leetcode.com/problems/binary-tree-postorder-traversal/

#include "LEET_BINARY_TREE_POSTORDER_TRAVERSAL.h"
#include <stack>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_BINARY_TREE_POSTORDER_TRAVERSAL
{
    struct TreeNode
    {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };
    class Solution {
    private:
        class Frame
        {
        public:
            TreeNode* root;
            int returnAddress;
        };

        vector<int> result;
        stack<Frame> callstack;

        void postorderTraversalImpl(TreeNode* root)
        {   
            int addressToGo = 0;
            while (true)
            {
                if (addressToGo == -1)
                {
                    break;
                }
                Frame current = callstack.top();
                if (addressToGo == 0)
                {
                    if (current.root == NULL)
                    {
                        // return;
                        addressToGo = current.returnAddress;
                        callstack.pop();
                    }
                    else
                    {
                        Frame newFrame;
                        newFrame.root = current.root->left;
                        newFrame.returnAddress = 1;
                        callstack.push(newFrame);
                        addressToGo = 0;
                        // this->postorderTraversalImpl(root->left);
                    }
                }
                else if (addressToGo == 1)
                {
                    Frame newFrame;
                    newFrame.root = current.root->right;
                    newFrame.returnAddress = 2;
                    callstack.push(newFrame);
                    addressToGo = 0;
                    // this->postorderTraversalImpl(root->right);
                }
                else if (addressToGo == 2)
                {
                    result.push_back(current.root->val);
                    // return
                    addressToGo = current.returnAddress;
                    callstack.pop();
                }
            }
        }
    public:
        vector<int> postorderTraversal(TreeNode* root)
        {
            this->result.clear();
            Frame initialFrame;
            initialFrame.root = root;
            initialFrame.returnAddress = -1;
            callstack.push(initialFrame);
            this->postorderTraversalImpl(root);
            return result;
        }
    };
};

using namespace _LEET_BINARY_TREE_POSTORDER_TRAVERSAL;

int LEET_BINARY_TREE_POSTORDER_TRAVERSAL()
{
    Solution solution;
    TreeNode a(1);
    TreeNode b(2);
    TreeNode c(3);
    a.right = &b;
    b.left = &c;
    vector<int> result = solution.postorderTraversal(&a);
    for (unsigned int i = 0; i < result.size(); i++)
    {
        cout << result[i] << " ";
    }
    cout << endl;
    return 0;
}