#include "stdafx.h"

// https://leetcode.com/problems/binary-tree-cameras/

#include "LEET_BINARY_TREE_CAMERAS.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_BINARY_TREE_CAMERAS
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
        int minCameraCover(TreeNode* root)
        {
            int root_taken;
            int root_not_taken_covered;
            int root_not_taken_not_covered;
            minCameraCover(root, &root_taken, &root_not_taken_covered, &root_not_taken_not_covered);
            return safeMin(root_taken, root_not_taken_covered);
        }

        void minCameraCover(TreeNode* root, int* root_taken, int* root_not_taken_covered, int* root_not_taken_not_covered)
        {
            if (root == NULL)
            {
                *root_taken = 0;
                *root_not_taken_covered = 0;
                *root_not_taken_not_covered = 0;
            }
            else
            {
                int left_taken;
                int left_not_taken_covered;
                int left_not_taken_not_covered;
                minCameraCover(root->left, &left_taken, &left_not_taken_covered, &left_not_taken_not_covered);
                int right_taken;
                int right_not_taken_covered;
                int right_not_taken_not_covered;
                minCameraCover(root->right, &right_taken, &right_not_taken_covered, &right_not_taken_not_covered);

                int left_valid = safeMin(left_taken, left_not_taken_covered);
                int left_min = safeMin(left_valid, left_not_taken_not_covered);
                int right_valid = safeMin(right_taken, right_not_taken_covered);
                int right_min = safeMin(right_valid, right_not_taken_not_covered);

                if (root->left == NULL)
                {
                    if (root->right == NULL)
                    {
                        *root_taken = 1;
                        *root_not_taken_covered = -1;
                        *root_not_taken_not_covered = 0;
                    }
                    else
                    {
                        *root_taken = 1 + right_min;
                        *root_not_taken_covered = right_taken;
                        *root_not_taken_not_covered = right_not_taken_covered;
                    }
                }
                else
                {
                    if (root->right == NULL)
                    {
                        *root_taken = 1 + left_min;
                        *root_not_taken_covered = left_taken;
                        *root_not_taken_not_covered = left_not_taken_covered;
                    }
                    else
                    {
                        *root_taken = 1 + left_min + right_min;
                        *root_not_taken_covered = min(left_taken + right_valid, left_valid + right_taken);
                        *root_not_taken_not_covered = safeSum(left_not_taken_covered, right_not_taken_covered);
                    }
                }
            }
        }
    private:
        int safeMin(int x, int y)
        {
            if (x == -1)
            {
                return y;
            }
            else if (y == -1)
            {
                return x;
            }
            else
            {
                return min(x, y);
            }
        }
        int safeSum(int x, int y)
        {
            if (x == -1)
            {
                return -1;
            }
            else if (y == -1)
            {
                return -1;
            }
            else
            {
                return x + y;
            }
        }
    };
};

using namespace _LEET_BINARY_TREE_CAMERAS;

int LEET_BINARY_TREE_CAMERAS()
{
    TreeNode a(1);
    TreeNode b(2);
    TreeNode c(3);
    TreeNode d(4);
    a.left = &b;
    a.right = nullptr;
    b.left = &c;
    b.right = &d;
    c.left = nullptr;
    c.right = nullptr;
    d.left = nullptr;
    d.right = nullptr;
    Solution s;
    cout << s.minCameraCover(&a) << endl;
    return 0;
}