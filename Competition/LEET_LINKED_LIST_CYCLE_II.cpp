#include "stdafx.h"

// https://leetcode.com/problems/linked-list-cycle-ii/

#include "LEET_LINKED_LIST_CYCLE_II.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_LINKED_LIST_CYCLE_II
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
        ListNode* detectCycle(ListNode *head)
        {
            if (head == NULL)
            {
                return NULL;
            }

            ListNode* slow = head;
            ListNode* fast = head;
            while (true)
            {
                if (slow->next == NULL)
                {
                    return NULL;
                }
                else
                {
                    slow = slow->next;
                }
                if (fast->next == NULL)
                {
                    return NULL;
                }
                else
                {
                    fast = fast->next;
                }
                if (fast->next == NULL)
                {
                    return NULL;
                }
                else
                {
                    fast = fast->next;
                }
                if (slow == fast)
                {
                    break;
                }
            }
            fast = head;
            while (slow != fast)
            {
                slow = slow->next;
                fast = fast->next;
            }
            return slow;
        }
    };
};

using namespace _LEET_LINKED_LIST_CYCLE_II;

int LEET_LINKED_LIST_CYCLE_II()
{
    Solution solution;
    ListNode a(0);
    ListNode b(1);
    ListNode c(2);
    ListNode d(3);
    ListNode e(4);
    a.next = &b;
    b.next = &c;
    c.next = &d;
    d.next = &e;
    e.next = &b;
    cout << (solution.detectCycle(&a) == &b) << endl;
    return 0;
}