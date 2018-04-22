#include "stdafx.h"

// https://leetcode.com/problems/reverse-nodes-in-k-group

#include "LEET_REVERSE_NODES_IN_K_GROUP.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_REVERSE_NODES_IN_K_GROUP
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
        ListNode* reverseKGroup(ListNode* head, int k)
        {
            if (k < 2)
            {
                return head;
            }
            ListNode* first_segment_head = head;
            ListNode* last_segment_head = nullptr;
            ListNode* last_segment_tail = nullptr;
            ListNode* current_segment_head = nullptr;
            ListNode* current_segment_tail = nullptr;
            ListNode* unexamined = head;
            int count = 0;
            while (true)
            {
                if (count == k)
                {
                    if (last_segment_tail != nullptr)
                    {
                        last_segment_tail->next = current_segment_head;
                    }
                    if (last_segment_head == nullptr)
                    {
                        first_segment_head = current_segment_head;
                    }
                    last_segment_head = current_segment_head;
                    last_segment_tail = current_segment_tail;
                    current_segment_head = current_segment_tail = nullptr;
                    count = 0;
                }
                else
                {
                    if (current_segment_head == nullptr)
                    {
                        if (unexamined == nullptr)
                        {
                            return first_segment_head;
                        }
                        else
                        {
                            // a -> b
                            // u
                            //
                            // translate to
                            //
                            // null <- a b 
                            //         h u
                            //         t
                            current_segment_head = current_segment_tail = unexamined;
                            unexamined = unexamined->next;
                            current_segment_tail->next = nullptr;
                            count++;
                        }
                    }
                    else
                    {
                        if (unexamined == nullptr)
                        {
                            while (current_segment_head != nullptr)
                            {
                                //    a -> b -> c
                                // u  h
                                //
                                // translate to
                                //
                                // null <- a b->c
                                //         u h
                                ListNode* current_segment_head_copy = current_segment_head;
                                current_segment_head = current_segment_head->next;
                                current_segment_head_copy->next = unexamined;
                                unexamined = current_segment_head_copy;
                            }
                            if (last_segment_tail != nullptr)
                            {
                                last_segment_tail->next = current_segment_tail;
                            }

                            return first_segment_head;
                        }
                        else
                        {
                            // a <- b c -> d
                            //      h u
                            //
                            // translate to
                            //
                            // a <- b <- c d
                            //           h u
                            ListNode* next_current_segment_head = unexamined;
                            unexamined = unexamined->next;
                            next_current_segment_head->next = current_segment_head;
                            current_segment_head = next_current_segment_head;
                            count++;
                        }
                    }
                }
            }
        }
    };
};

using namespace _LEET_REVERSE_NODES_IN_K_GROUP;

int LEET_REVERSE_NODES_IN_K_GROUP()
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
    ListNode* p = solution.reverseKGroup(&a, 7);
    while (p != nullptr)
    {
        cout << p->val << ",";
        p = p->next;
    }

    return 0;
}
