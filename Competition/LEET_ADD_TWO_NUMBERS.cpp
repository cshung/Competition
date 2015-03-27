#include "stdafx.h"

// https://leetcode.com/problems/add-two-numbers/

#include "LEET_ADD_TWO_NUMBERS.h"
#include <map>
#include <iostream>
#include <vector>

using namespace std;

namespace _LEET_ADD_TWO_NUMBERS
{
    struct ListNode {
        int val;
        ListNode *next;
        ListNode(int x) : val(x), next(NULL) {}
    };

    class Solution {
    public:
        ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
            ListNode* last_node = NULL;
            ListNode* result = NULL;
            int carry = 0;
            while (true)
            {
                bool should_add_node = false;
                int digit_to_add = -1;
                if (l1 != NULL && l2 != NULL)
                {
                    int sum = l1->val + l2->val + carry;
                    carry = sum / 10;
                    digit_to_add = sum % 10;
                    should_add_node = true;
                    l1 = l1->next;
                    l2 = l2->next;
                }
                else if (l1 == NULL && l2 != NULL)
                {
                    int sum = l2->val + carry;
                    carry = sum / 10;
                    digit_to_add = sum % 10;
                    should_add_node = true;
                    l2 = l2->next;
                }
                else if (l1 != NULL && l2 == NULL)
                {
                    int sum = l1->val + carry;
                    carry = sum / 10;
                    digit_to_add = sum % 10;
                    should_add_node = true;
                    l1 = l1->next;
                }
                else if (l1 == NULL && l2 == NULL)
                {
                    if (carry != 0)
                    {
                        digit_to_add = carry;
                        should_add_node = true;
                        carry = 0;
                    }
                }

                if (should_add_node)
                {
                    ListNode* new_node = new ListNode(digit_to_add);
                    if (last_node != nullptr)
                    {
                        last_node->next = new_node;
                    }
                    else
                    {
                        result = new_node;
                    }

                    last_node = new_node;
                }
                else
                {
                    break;
                }
            }

            return result;
        }
    };
};

using namespace _LEET_ADD_TWO_NUMBERS;

int LEET_ADD_TWO_NUMBERS()
{
    ListNode a(2);
    ListNode b(4);
    ListNode c(3);
    ListNode d(5);
    ListNode e(6);
    ListNode f(4);
    a.next = &b;    b.next = &c;    c.next = NULL;
    d.next = &e;    e.next = &f;    f.next = NULL;
    Solution solution;
    ListNode* result = solution.addTwoNumbers(&a, &b);
    ListNode* cursor = result;
    while (cursor != NULL)
    {
        cout << cursor->val << "->";
        cursor = cursor->next;
        delete result;
        result = cursor;
    }
    cout << endl;
    return 0;
}
