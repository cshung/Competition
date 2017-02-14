#include "stdafx.h"

// https://leetcode.com/problems/find-bottom-left-tree-value/

#include "LEET_FIND_BOTTOM_LEFT_TREE_VALUE.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_FIND_BOTTOM_LEFT_TREE_VALUE
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
        void findBottomLeftValue(TreeNode* root, int depth, int& max_layer, int& answer)
        {
            if (root == nullptr)
            {
                return;
            }
            findBottomLeftValue(root->left, depth + 1, max_layer, answer);
            if (depth > max_layer)
            {
                max_layer = depth;
                answer = root->val;
            }
            findBottomLeftValue(root->right, depth + 1, max_layer, answer);
        }
        int findBottomLeftValue(TreeNode* root)
        {
            int max_layer = -1;
            int answer = 0;
            findBottomLeftValue(root, 0, max_layer, answer);
            return answer;
        }
    };
};

using namespace _LEET_FIND_BOTTOM_LEFT_TREE_VALUE;

int LEET_FIND_BOTTOM_LEFT_TREE_VALUE()
{
    Solution solution;
    TreeNode a(2);
    TreeNode b(1);
    TreeNode c(3);
    a.left = &b;
    a.right = &c;
    cout << solution.findBottomLeftValue(&a) << endl;

    TreeNode p(1);
    TreeNode q(2);
    TreeNode r(3);
    TreeNode s(4);
    TreeNode t(5);
    TreeNode u(6);
    TreeNode v(7);
    p.left = &q;
    p.right = &r;
    q.left = &s;
    r.left = &t;
    r.right = &u;
    t.left = &v;
    cout << solution.findBottomLeftValue(&p) << endl;
    return 0;
}