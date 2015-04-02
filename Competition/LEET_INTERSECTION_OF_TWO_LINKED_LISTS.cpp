#include "stdafx.h"

// https://leetcode.com/problems/intersection-of-two-linked-lists/

#include "LEET_INTERSECTION_OF_TWO_LINKED_LISTS.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_INTERSECTION_OF_TWO_LINKED_LISTS
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
        ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
        {
            int a_length = 0;
            int b_length = 0;
            ListNode* a_cursor = headA;
            ListNode* b_cursor = headB;

            // Step 1: Determine the lengths
            while (a_cursor != NULL)
            {
                a_cursor = a_cursor->next;
                a_length++;
            }
            while (b_cursor != NULL)
            {
                b_cursor = b_cursor->next;
                b_length++;
            }

            // Step 2: Align the lists
            int a_remaining_length = a_length;
            int b_remaining_length = b_length;
            a_cursor = headA;
            b_cursor = headB;

            while (a_remaining_length > b_remaining_length)
            {
                a_cursor = a_cursor->next;
                a_remaining_length--;
            }
            while (a_remaining_length < b_remaining_length)
            {
                b_cursor = b_cursor->next;
                b_remaining_length--;
            }

            // Step 3: Determine the intersection
            while (a_cursor != b_cursor)
            {
                a_cursor = a_cursor->next;
                b_cursor = b_cursor->next;
            }

            return a_cursor;
        }
    };
};

using namespace _LEET_INTERSECTION_OF_TWO_LINKED_LISTS;

int LEET_INTERSECTION_OF_TWO_LINKED_LISTS()
{
    ListNode a1(1); 
    ListNode a2(1);
    ListNode b1(1);
    ListNode b2(1);
    ListNode b3(1);
    ListNode c1(1);
    ListNode c2(1);
    ListNode c3(1);

    a1.next = &a2; a2.next = &c1;
    b1.next = &b2; b2.next = &b3; b3.next = &c1;
    c1.next = &c2; c2.next = &c3; c3.next = NULL;

    Solution solution;
    cout << (solution.getIntersectionNode(&a1, &b1) == &c1) << endl;

    return 0;
}
