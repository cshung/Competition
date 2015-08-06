#include "stdafx.h"

// https://leetcode.com/problems/reverse-linked-list/

#include "LEET_REVERSE_LINKED_LIST.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_REVERSE_LINKED_LIST
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
        ListNode* reverseList(ListNode* head)
        {
            ListNode* cursor = head;
            ListNode* prev = NULL;
            while (cursor != NULL)
            {
                ListNode* next = cursor->next;
                cursor->next = prev;
                prev = cursor;
                cursor = next;
            }
            return prev;
        }
    };
};

using namespace _LEET_REVERSE_LINKED_LIST;

int LEET_REVERSE_LINKED_LIST()
{
    Solution solution;
    ListNode a(1);
    ListNode b(1);
    ListNode c(2);
    ListNode d(2);
    ListNode e(3);
    a.next = &b;
    b.next = &c;
    c.next = &d;
    d.next = &e;

    ListNode* result = solution.reverseList(&a);
    while (result != NULL)
    {
        cout << result->val;
        cout << ", ";
        result = result->next;
    }
    cout << endl;

    return 0;
}