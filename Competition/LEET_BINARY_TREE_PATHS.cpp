#include "stdafx.h"

// https://leetcode.com/problems/binary-tree-paths/

#include "LEET_BINARY_TREE_PATHS.h"

#include <stack>
#include <queue>
#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

namespace _LEET_BINARY_TREE_PATHS
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
    private:
        void binaryTreePathsImpl(stack<int>& path, TreeNode* root, vector<string>& solution)
        {
            path.push(root->val);
            if (root->left == NULL && root->right == NULL)
            {
                stack<int> currentPath;
                while (path.size() > 0)
                {
                    currentPath.push(path.top());
                    path.pop();
                }
                ostringstream buffer;
                while (currentPath.size() > 1)
                {
                    buffer << currentPath.top();
                    buffer << "->";
                    path.push(currentPath.top());                    
                    currentPath.pop();
                }
                buffer << currentPath.top();
                path.push(currentPath.top());
                currentPath.pop();
                solution.push_back(buffer.str());
            }
            else
            {
                if (root->left != NULL)
                {
                    binaryTreePathsImpl(path, root->left, solution);
                }
                if (root->right != NULL)
                {
                    binaryTreePathsImpl(path, root->right, solution);
                }
            }
            path.pop();
        }
    public:
        vector<string> binaryTreePaths(TreeNode* root)
        {
            stack<int> path;
            vector<string> solution;
            if (root != NULL)
            {
                binaryTreePathsImpl(path, root, solution);
            }
            return solution;
        }
    };

    TreeNode* ToTree(vector<int> serialized)
    {
        if (serialized.size() == 0)
        {
            return NULL;
        }
        unsigned int i = 1;
        TreeNode* root = new TreeNode(serialized[0]);
        queue<TreeNode*> queue;
        queue.push(root);
        while (i < serialized.size())
        {
            TreeNode* current = queue.front();
            queue.pop();
            int leftValue = serialized[i++];
            int rightValue = serialized[i++];
            if (leftValue != 10086) // 10086 represents #
            {
                TreeNode* leftNode = new TreeNode(leftValue);
                current->left = leftNode;
                queue.push(leftNode);
            }
            if (rightValue != 10086) // 10086 represents #
            {
                TreeNode* rightNode = new TreeNode(rightValue);
                current->right = rightNode;
                queue.push(rightNode);
            }
        }

        return root;
    }
}

using namespace _LEET_BINARY_TREE_PATHS;

int LEET_BINARY_TREE_PATHS()
{
    int case1[] = { 1, 2, 3, 10086, 5, 10086, 10086 };
    Solution s;
    vector<string> case1_solution = s.binaryTreePaths(ToTree(vector<int>(case1, case1 + _countof(case1))));
    for (unsigned int i = 0; i < case1_solution.size(); i++)
    {
        cout << case1_solution[i] << endl;
    }
    return 0;
}
