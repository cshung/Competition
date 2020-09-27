#include "stdafx.h"

// https://leetcode.com/problems/all-elements-in-two-binary-search-trees/

#include "LEET_ALL_ELEMENTS_IN_TWO_BINARY_SEARCH_TREES.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_ALL_ELEMENTS_IN_TWO_BINARY_SEARCH_TREES
{
    struct TreeNode
    {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode() : val(0), left(nullptr), right(nullptr) {}
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
        TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };
    class Solution
    {
    public:
        vector<int> getAllElements(TreeNode* root1, TreeNode* root2) {
            vector<int> buffer;
            int start1 = 0;
            collect(root1, buffer);
            int start2 = buffer.size();
            collect(root2, buffer);
            vector<int> result;
            int end1 = start2;
            int end2 = buffer.size();
            int p = start1;
            int q = start2;
            while (p < end1 || q < end2)
            {
                if (p == end1)
                {
                    result.push_back(buffer[q++]);
                }
                else if (q == end2)
                {
                    result.push_back(buffer[p++]);
                }
                else
                {
                    int bp = buffer[p];
                    int bq = buffer[q];
                    if (bp < bq)
                    {
                        result.push_back(buffer[p++]);
                    }
                    else
                    {
                        result.push_back(buffer[q++]);
                    }
                }
            }
            return result;
        }

        void collect(TreeNode* n, vector<int>& buffer)
        {
            if (n != nullptr)
            {
                collect(n->left, buffer);
                buffer.push_back(n->val);
                collect(n->right, buffer);
            }
        }
    };
};

using namespace _LEET_ALL_ELEMENTS_IN_TWO_BINARY_SEARCH_TREES;

int LEET_ALL_ELEMENTS_IN_TWO_BINARY_SEARCH_TREES()
{
    Solution solution;
    TreeNode a(2);
    TreeNode b(1);
    TreeNode c(4);
    TreeNode d(1);
    TreeNode e(0);
    TreeNode f(3);
    a.left = &b;
    a.right = &c;
    b.left = nullptr;
    b.right = nullptr;
    c.left = nullptr;
    c.right = nullptr;
    d.left = &e;
    d.right = &f;
    e.left = nullptr;
    e.right = nullptr;
    f.left = nullptr;
    f.right = nullptr;
    auto answers = solution.getAllElements(&a, &d);
    for (auto answer : answers)
    {
        cout << answer << " ";
    }
    return 0;
}