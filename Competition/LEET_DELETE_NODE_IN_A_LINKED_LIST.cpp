#include "stdafx.h"

// 

#include "LEET_DELETE_NODE_IN_A_LINKED_LIST.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_DELETE_NODE_IN_A_LINKED_LIST
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
        void deleteNode(ListNode* node) 
        {
            if (node->next == NULL)
            {
                return;
            }
            node->val = node->next->val;
            node->next = node->next->next;
        }
    };
};

using namespace _LEET_DELETE_NODE_IN_A_LINKED_LIST;

int LEET_DELETE_NODE_IN_A_LINKED_LIST()
{
    Solution s;
    ListNode a(1);
    ListNode b(2);
    ListNode c(3);
    ListNode d(4);
    a.next = &b;
    b.next = &c;
    c.next = &d;
    s.deleteNode(&c);
    ListNode* cur = &a;
    while (cur != NULL)
    {
        cout << cur->val;
        cur = cur->next;
    }

    cout << endl;
    return 0;
}