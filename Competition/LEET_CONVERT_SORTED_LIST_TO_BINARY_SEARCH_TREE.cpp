#include "stdafx.h"

// https://leetcode.com/problems/convert-sorted-list-to-binary-search-tree/

#include "LEET_CONVERT_SORTED_LIST_TO_BINARY_SEARCH_TREE.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_CONVERT_SORTED_LIST_TO_BINARY_SEARCH_TREE
{
    struct ListNode
    {
        int val;
        ListNode *next;
        ListNode(int x) : val(x), next(NULL) {}
    };
    struct TreeNode
    {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };
    class Solution {
    public:
        TreeNode* sortedVectorToBST(vector<int>& result, int begin, int end)
        {
            int length = end - begin;
            if (length == 0)
            {
                return nullptr;
            }
            else
            {
                int c = (begin + end) / 2;
                TreeNode* root = new TreeNode(result[c]);
                root->left = sortedVectorToBST(result, begin, c);
                root->right = sortedVectorToBST(result, c + 1, end);
                return root;
            }
        }
        TreeNode* sortedListToBST(ListNode* head)
        {
            vector<int> result;
            while (head != nullptr)
            {
                result.push_back(head->val);
                head = head->next;
            }
            return sortedVectorToBST(result, 0, result.size());
        }
    };
};

using namespace _LEET_CONVERT_SORTED_LIST_TO_BINARY_SEARCH_TREE;

int LEET_CONVERT_SORTED_LIST_TO_BINARY_SEARCH_TREE()
{
    Solution solution;
    ListNode a(1);
    ListNode b(2);
    ListNode c(3);
    ListNode d(4);
    ListNode e(5);
    ListNode f(6);
    ListNode g(7);
    a.next = &b;
    b.next = &c;
    c.next = &d;
    d.next = &e;
    e.next = &f;
    f.next = &g;
    TreeNode* t = solution.sortedListToBST(&a);
    cout << t->left->left->val << endl;
    cout << t->left->val << endl;
    cout << t->left->right->val << endl;
    cout << t->val << endl;
    cout << t->right->left->val << endl;
    cout << t->right->val << endl;
    cout << t->right->right->val << endl;
    return 0;
}