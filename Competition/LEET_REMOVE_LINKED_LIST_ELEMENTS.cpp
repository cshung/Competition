#include "stdafx.h"

// https://leetcode.com/problems/remove-linked-list-elements/

#include "LEET_REMOVE_LINKED_LIST_ELEMENTS.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_REMOVE_LINKED_LIST_ELEMENTS
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
        ListNode* removeElements(ListNode* head, int val)
        {
            ListNode fakeHead(10086);
            ListNode* last = &fakeHead;
            fakeHead.next = head;
            while (head != NULL)
            {
                if (head->val != val)
                {
                    last->next = head;
                    last = head;
                }
                head = head->next;
            }

            last->next = NULL;

            return fakeHead.next;
        }
    };
};

using namespace _LEET_REMOVE_LINKED_LIST_ELEMENTS;

int LEET_REMOVE_LINKED_LIST_ELEMENTS()
{
    Solution solution;
    ListNode a(1);
    ListNode b(2);
    ListNode c(6);
    ListNode d(3);
    ListNode e(4);
    ListNode f(5);
    ListNode g(6);
    a.next = &b;
    b.next = &c;
    c.next = &d;
    d.next = &e;
    e.next = &f;
    f.next = &g;
    ListNode* deleted = solution.removeElements(&a, 6);
    while (deleted != NULL)
    {
        cout << deleted->val << ", ";
        deleted = deleted->next;
    }
    cout << endl;
    return 0;
}