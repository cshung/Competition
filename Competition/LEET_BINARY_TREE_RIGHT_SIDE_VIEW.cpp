#include "stdafx.h"

// https://leetcode.com/problems/climbing-stairs/

#include "LEET_BINARY_TREE_RIGHT_SIDE_VIEW.h"
#include <map>
#include <iostream>
#include <queue>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_BINARY_TREE_RIGHT_SIDE_VIEW
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
        vector<int> rightSideView(TreeNode* root)
        {
            vector<int> result;
            int recording_depth = -1;
            int recording_value = -1;

            queue<pair<TreeNode*, int>> bfs_queue;
            bfs_queue.push(pair<TreeNode*, int>(root, 0));
            while (bfs_queue.size() > 0)
            {
                pair<TreeNode*, int> visiting = bfs_queue.front();
                bfs_queue.pop();

                TreeNode* visiting_node = visiting.first;
                if (visiting_node != NULL)
                {
                    int visiting_value = visiting_node->val;
                    int visiting_depth = visiting.second;
                    if (visiting_depth > recording_depth && recording_depth != -1)
                    {
                        result.push_back(recording_value);
                    }
                    recording_value = visiting_value;
                    recording_depth = visiting_depth;

                    bfs_queue.push(pair<TreeNode*, int>(visiting_node->left, visiting_depth + 1));
                    bfs_queue.push(pair<TreeNode*, int>(visiting_node->right, visiting_depth + 1));
                }
            }

            if (recording_depth != -1)
            {
                result.push_back(recording_value);
            }

            return result;
        }
    };
};

using namespace _LEET_BINARY_TREE_RIGHT_SIDE_VIEW;

int LEET_BINARY_TREE_RIGHT_SIDE_VIEW()
{
    Solution s;
    TreeNode a(1);
    TreeNode b(2);
    TreeNode c(3);
    TreeNode d(5);
    TreeNode e(4);
    a.left = &b;
    a.right = &c;
    b.right = &d;
    c.right = &e;
    vector<int> result = s.rightSideView(&a);
    for (unsigned int i = 0; i < result.size(); i++)
    {
        cout << result[i];
    }
    cout << endl;
    return 0;
}