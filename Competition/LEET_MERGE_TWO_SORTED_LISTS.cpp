#include "stdafx.h"

// https://leetcode.com/problems/merge-two-sorted-lists/

#include "LEET_MERGE_TWO_SORTED_LISTS.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_MERGE_TWO_SORTED_LISTS
{
    struct ListNode
    {
        int val;
        ListNode *next;
        ListNode(int x) : val(x), next(NULL) {}
    };

    class Solution {
    public:
        ListNode* mergeTwoLists(ListNode* l1, ListNode* l2)
        {
            if (l1 == NULL)
            {
                return l2;
            } 
            else if (l2 == NULL)
            {
                return l1;
            }
            else
            {
                int v1 = l1->val;
                int v2 = l2->val;
                if (l1->val < l2->val)
                {
                    l1->next = mergeTwoLists(l1->next, l2);
                    return l1;
                }
                else
                {
                    l2->next = mergeTwoLists(l1, l2->next);
                    return l2;
                }
            }
        }
    };
};

using namespace _LEET_MERGE_TWO_SORTED_LISTS;

int LEET_MERGE_TWO_SORTED_LISTS()
{
    Solution solution;
    ListNode a(1);
    ListNode b(4);

    ListNode c(2);
    ListNode d(3);
    ListNode e(5);

    a.next = &b;
    c.next = &d;
    d.next = &e;

    ListNode* head = solution.mergeTwoLists(&a, &c);
    while (head != NULL)
    {
        cout << head->val << ", ";
        head = head->next;
    }
    return 0;
}