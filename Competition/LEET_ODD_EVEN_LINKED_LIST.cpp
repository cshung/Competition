#include "stdafx.h"

// https://leetcode.com/problems/odd-even-linked-list/

#include "LEET_ODD_EVEN_LINKED_LIST.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_ODD_EVEN_LINKED_LIST
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
        ListNode* oddEvenList(ListNode* head)
        {
            if (head == NULL)
            {
                return head;
            }
            if (head->next == NULL)
            {
                return head;
            }
            ListNode* o_head = head;
            ListNode* e_head = head->next;

            ListNode* o_tail = o_head;
            ListNode* e_tail = e_head;

            ListNode* current = head->next->next;

            o_head->next = NULL;
            e_head->next = NULL;

            int state = 0;

            while (current != NULL)
            {
                ListNode* next = current->next;
                if (state == 0)
                {
                    o_tail->next = current;
                    current->next = NULL;
                    o_tail = current;
                    state = 1;
                }
                else if (state == 1)
                {
                    e_tail->next = current;
                    current->next = NULL;
                    e_tail = current;
                    state = 0;
                }
                current = next;
            }

            o_tail->next = e_head;
            return o_head;
        }
    };
};

using namespace _LEET_ODD_EVEN_LINKED_LIST;

int LEET_ODD_EVEN_LINKED_LIST()
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
    ListNode* soln = s.oddEvenList(&a);
    while (soln != NULL)
    {
        cout << soln->val;
        soln = soln->next;
    }
    return 0;
}