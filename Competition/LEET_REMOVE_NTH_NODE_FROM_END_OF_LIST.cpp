#include "stdafx.h"

// https://leetcode.com/problems/remove-nth-node-from-end-of-list/

#include "LEET_REMOVE_NTH_NODE_FROM_END_OF_LIST.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_REMOVE_NTH_NODE_FROM_END_OF_LIST
{
    struct ListNode
    {
        int val;
        ListNode *next;
        ListNode(int x) : val(x), next(NULL) {}
    };

    class Solution
    {
    private:
        ListNode* removeNthFromEnd(ListNode* head, int n, int count, int& length)
        {
            if (head == NULL)
            {
                length = count;
            }
            else
            {
                head->next = removeNthFromEnd(head->next, n, count + 1, length);
            }

            if (count == length - n)
            {
                return head->next;
            }
            else
            {
                return head;
            }
        }
    public:
        ListNode* removeNthFromEnd(ListNode* head, int n)
        {
            int length = -1;
            return this->removeNthFromEnd(head, n, 0, length);
        }
    };
};

using namespace _LEET_REMOVE_NTH_NODE_FROM_END_OF_LIST;

int LEET_REMOVE_NTH_NODE_FROM_END_OF_LIST()
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
    ListNode* cursor = solution.removeNthFromEnd(&a, 2);
    while (cursor != NULL)
    {
        cout << cursor->val << ",";
        cursor = cursor->next;
    }
    cout << endl;
    return 0;
}