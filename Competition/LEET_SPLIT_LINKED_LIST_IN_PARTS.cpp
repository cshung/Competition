#include "stdafx.h"

// https://leetcode.com/problems/split-linked-list-in-parts

#include "LEET_SPLIT_LINKED_LIST_IN_PARTS.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_SPLIT_LINKED_LIST_IN_PARTS
{
    struct ListNode
    {
        int val;
        ListNode *next;
        ListNode(int x) : val(x), next(NULL) {}
    };
    class Solution {
    public:
        vector<ListNode*> splitListToParts(ListNode* root, int k)
        {
            int size = 0;
            ListNode* cur = root;
            ListNode* prev = nullptr;
            while (cur != NULL)
            {
                size++;
                cur = cur->next;
            }
            int part_size = size / k;
            int part_excess = size % k;
            vector<ListNode*> result;
            result.resize(k);
            cur = root;
            for (int i = 0; i < k; i++)
            {
                result[i] = cur;
                for (int j = 0; j < part_size; j++)
                {
                    if (cur != nullptr)
                    {
                        prev = cur;
                        cur = cur->next;
                    }
                }
                if (part_excess > 0)
                {
                    if (cur != nullptr)
                    {
                        prev = cur;
                        cur = cur->next;
                    }
                    part_excess = part_excess - 1;
                }
                if (prev != nullptr)
                {
                    prev->next = nullptr;
                }
            }
            return result;
        }
    };
};

using namespace _LEET_SPLIT_LINKED_LIST_IN_PARTS;

int LEET_SPLIT_LINKED_LIST_IN_PARTS()
{
    ListNode a(1);
    ListNode b(2);
    ListNode c(3);
    ListNode d(4);
    ListNode e(5);
    a.next = &b;
    b.next = &c;
    c.next = &d;
    d.next = &e;
    Solution s;
    vector<ListNode*> result = s.splitListToParts(&a, 3);
    for (ListNode* r : result)
    {
        ListNode* u = r;
        while (u != nullptr)
        {
            cout << u->val << " -> ";
            u = u->next;
        }
        cout << "nullptr" << endl;
    }
    return 0;
}