#include "stdafx.h"

// https://leetcode.com/problems/rotate-list/

#include "LEET_ROTATE_LIST.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

namespace _LEET_ROTATE_LIST
{
    struct ListNode
    {
        int val;
        ListNode *next;
        ListNode(int x) : val(x), next(NULL) {}
    };
    class Solution
    {
    public:
        ListNode* rotateRight(ListNode* head, int k)
        {
            int length = 0;
            ListNode* cur = head;
            while (cur != nullptr)
            {
                cur = cur->next;
                length++;
            }
            if (length == 0)
            {
                return nullptr;
            }
            k = k % length;
            if (k == 0)
            {
                return head;
            }
            cur = head;
            for (int i = 0; i < length - 1; i++)
            {
                cur = cur->next;
            }
            cur->next = head;
            cur = head;
            for (int i = 0; i < k - 1; i++)
            {
                cur = cur->next;
            }
            head = cur->next;
            cur->next = nullptr;
            return head;
        }
    };
};

using namespace _LEET_ROTATE_LIST;

int LEET_ROTATE_LIST()
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
    ListNode* head = solution.rotateRight(&a, 3);
    while (head != nullptr)
    {
        cout << head->val << " ";
        head = head->next;
    }
    return 0;
}