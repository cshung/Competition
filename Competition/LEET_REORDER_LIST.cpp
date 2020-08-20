#include "stdafx.h"

// https://leetcode.com/problems/reorder-list/

#include "LEET_REORDER_LIST.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_REORDER_LIST
{
    struct ListNode
    {
        int val;
        ListNode* next;
        ListNode() : val(0), next(nullptr) {}
        ListNode(int x) : val(x), next(nullptr) {}
        ListNode(int x, ListNode* next) : val(x), next(next) {}
    };
    class Solution
    {
    public:
        void reorderList(ListNode* head)
        {
            if (head == nullptr)
            {
                return;
            }
            vector<ListNode*> nodes;
            while (head != nullptr)
            {
                nodes.push_back(head);
                head = head->next;
            }
            int p = 1;
            int q = nodes.size() - 1;
            bool back = true;
            ListNode* cur = nodes[0];
            for (int i = 1; i < nodes.size(); i++)
            {
                if (back)
                {
                    cur->next = nodes[q--];
                    cur = cur->next;
                    back = false;
                }
                else
                {
                    cur->next = nodes[p++];
                    cur = cur->next;
                    back = true;
                }
            }
            cur->next = nullptr;
        }
    };
};

using namespace _LEET_REORDER_LIST;

int LEET_REORDER_LIST()
{
    Solution solution;
    ListNode a(1);
    ListNode b(2);
    ListNode c(3);
    ListNode d(4);
    ListNode e(5);
    a.next = &b;
    b.next = &c;
    c.next = &d;
    d.next = &e;
    e.next = nullptr;
    solution.reorderList(&a);
    ListNode* cur = &a;
    while (cur != nullptr)
    {
        cout << cur->val << " ";
        cur = cur->next;
    }
    cout << endl;
    return 0;
}