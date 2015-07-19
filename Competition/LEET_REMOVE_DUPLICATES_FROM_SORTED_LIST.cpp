#include "stdafx.h"

// https://leetcode.com/problems/remove-duplicates-from-sorted-list/

#include "LEET_REMOVE_DUPLICATES_FROM_SORTED_LIST.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_REMOVE_DUPLICATES_FROM_SORTED_LIST
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
        ListNode* deleteDuplicates(ListNode* head)
        {
            ListNode* cursor = head;
            while (cursor != NULL)
            {
                if (cursor->next != NULL && cursor->next->val == cursor->val)
                {
                    cursor->next = cursor->next->next;
                }
                else
                {
                    cursor = cursor->next;
                }
            }
            return head;
        }
    };
};

using namespace _LEET_REMOVE_DUPLICATES_FROM_SORTED_LIST;

int LEET_REMOVE_DUPLICATES_FROM_SORTED_LIST()
{
    ListNode a(1);
    ListNode b(1);
    ListNode c(2);
    ListNode d(2);
    ListNode e(3);
    a.next = &b;
    b.next = &c;
    c.next = &d;
    d.next = &e;
    Solution s;
    ListNode* soln = s.deleteDuplicates(&a);
    while (soln != NULL)
    {
        cout << soln->val << ",";
        soln = soln->next;
    }
    cout << endl;
    return 0;
}