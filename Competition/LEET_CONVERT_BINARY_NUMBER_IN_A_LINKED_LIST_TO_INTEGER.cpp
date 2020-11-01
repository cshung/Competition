#include "stdafx.h"

// https://leetcode.com/problems/convert-binary-number-in-a-linked-list-to-integer/

#include "LEET_CONVERT_BINARY_NUMBER_IN_A_LINKED_LIST_TO_INTEGER.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_CONVERT_BINARY_NUMBER_IN_A_LINKED_LIST_TO_INTEGER
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
        int getDecimalValue(ListNode* head)
        {
            return getDecimalValue(head, 0);
        }

        int getDecimalValue(ListNode* head, int v)
        {
            if (head == NULL)
            {
                return v;
            }
            else
            {
                return getDecimalValue(head->next, v * 2 + head->val);
            }
        }
    };
};

using namespace _LEET_CONVERT_BINARY_NUMBER_IN_A_LINKED_LIST_TO_INTEGER;

int LEET_CONVERT_BINARY_NUMBER_IN_A_LINKED_LIST_TO_INTEGER()
{
    Solution solution;
    ListNode a(1);
    ListNode b(0);
    ListNode c(1);
    a.next = &b;
    b.next = &c;
    c.next = NULL;
    cout << solution.getDecimalValue(&a) << endl;

    return 0;
}