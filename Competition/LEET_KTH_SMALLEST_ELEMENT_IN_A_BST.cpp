#include "stdafx.h"

// https://leetcode.com/problems/kth-smallest-element-in-a-bst/

#include "LEET_KTH_SMALLEST_ELEMENT_IN_A_BST.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_KTH_SMALLEST_ELEMENT_IN_A_BST
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
        bool kthSmallest(TreeNode* root, int k, int* current, int* result)
        {
            if (root == NULL)
            {
                return false;
            }

            if (kthSmallest(root->left, k, current, result))
            {
                return true;
            }

            (*current)++;
            if (*current == k)
            {
                *result = root->val;
                return true;
            }

            if (kthSmallest(root->right, k, current, result))
            {
                return true;
            }

            return false;
        }
    public:
        int kthSmallest(TreeNode* root, int k)
        {
            int current = 0;
            int result;
            kthSmallest(root, k, &current, &result);
            return result;
        }
    };
};

using namespace _LEET_KTH_SMALLEST_ELEMENT_IN_A_BST;

int LEET_KTH_SMALLEST_ELEMENT_IN_A_BST()
{
    TreeNode a(2);
    TreeNode b(1);
    TreeNode c(3);
    a.left = &b;
    a.right = &c;
    Solution s;
    cout << (s.kthSmallest(&a, 1) == 1) << endl;
    cout << (s.kthSmallest(&a, 2) == 2) << endl;
    cout << (s.kthSmallest(&a, 3) == 3) << endl;
    return 0;
}