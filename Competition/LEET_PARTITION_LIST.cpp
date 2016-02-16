#include "stdafx.h"

// https://leetcode.com/problems/partition-list/

#include "LEET_PARTITION_LIST.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_PARTITION_LIST
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
        ListNode* partition(ListNode* head, int x)
        {
            ListNode smaller(-1);
            ListNode larger(-1);
            ListNode* smallerTail = &smaller;
            ListNode* largerTail = &larger;
            while (head != NULL)
            {
                ListNode* nextHead = head->next;
                if (head->val < x)
                {
                    smallerTail->next = head;
                    smallerTail = head;
                    smallerTail->next = NULL;
                }
                else
                {
                    largerTail->next = head;
                    largerTail = head;
                    largerTail->next = NULL;
                }
                head = nextHead;
            }

            smallerTail->next = larger.next;
            return smaller.next;
        }
    };
};

using namespace _LEET_PARTITION_LIST;

int LEET_PARTITION_LIST()
{
    Solution solution;
    ListNode a(1);
    ListNode b(4);
    ListNode c(3);
    ListNode d(2);
    ListNode e(5);
    ListNode f(2);
    a.next = &b;
    b.next = &c;
    c.next = &d;
    d.next = &e;
    e.next = &f;
    ListNode* soln = solution.partition(&a, 3);
    while (soln != NULL)
    {
        cout << soln->val << " ";
        soln = soln->next;
    }
    return 0;
}