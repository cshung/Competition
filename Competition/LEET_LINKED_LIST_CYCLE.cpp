#include "stdafx.h"

// https://leetcode.com/problems/add-two-numbers/

#include "LEET_LINKED_LIST_CYCLE.h"
#include <map>
#include <iostream>
#include <vector>

using namespace std;

namespace _LEET_LINKED_LIST_CYCLE
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
        bool hasCycle(ListNode *head)
        {
            if (head == NULL)
            {
                return false;
            }

            ListNode* fast = head;
            ListNode* slow = head;
            while (true)
            {
                fast = fast->next;
                if (fast == NULL)
                {
                    return false;
                }
                fast = fast->next;
                if (fast == NULL)
                {
                    return false;
                }
                slow = slow->next;
                if (fast == slow)
                {
                    return true;
                }
            }
        }
    };
};

using namespace _LEET_LINKED_LIST_CYCLE;

int LEET_LINKED_LIST_CYCLE()
{
    ListNode a(0);
    ListNode b(1);
    ListNode c(2);
    ListNode d(3);
    a.next = &b;
    b.next = &c;
    c.next = &d;
    d.next = &a;
    Solution solution;
    cout << (solution.hasCycle(&a) ? "Yes" : "No") << endl;
    return 0;
}
