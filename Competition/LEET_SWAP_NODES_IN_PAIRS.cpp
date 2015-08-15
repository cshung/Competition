#include "stdafx.h"

// https://leetcode.com/problems/swap-nodes-in-pairs/

#include "LEET_SWAP_NODES_IN_PAIRS.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_SWAP_NODES_IN_PAIRS
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
        ListNode* swapPairs(ListNode* head)
        {
            ListNode fakeHead(10086); 
            ListNode* last = &fakeHead;
            ListNode* unprocessed = head;
            while (true)
            {
                if (unprocessed == NULL)
                {
                    break;
                }
                else if (unprocessed->next == NULL)
                {
                    last->next = unprocessed;
                    break;
                }
                else
                {
                    ListNode* a = unprocessed;
                    ListNode* b = unprocessed->next;
                    unprocessed = b->next;
                    last->next = b;
                    b->next = a;
                    a->next = NULL;
                    last = a;
                }
            }
            return fakeHead.next;
        }
    };

    ListNode* ToList(vector<int> data)
    {
        ListNode fakeHead(10086);
        ListNode* last = &fakeHead;
        for (unsigned int i = 0; i < data.size(); i++)
        {
            ListNode* newNode = new ListNode(data[i]);
            last->next = newNode;
            last = newNode;
        }
        return fakeHead.next;
    }

    void Print(ListNode* node)
    {
        while (node != NULL)
        {
            cout << node->val;
            cout << ", ";
            node = node->next;
        }
        cout << endl;
    }
};

using namespace _LEET_SWAP_NODES_IN_PAIRS;

int LEET_SWAP_NODES_IN_PAIRS()
{
    Solution s;
    int case2[] = { 1, 2, 3, 4 };
    int case3[] = { 1, 2, 3 };
    Print(s.swapPairs(ToList(vector<int>())));
    Print(s.swapPairs(ToList(vector<int>(case2, case2 + _countof(case2)))));
    Print(s.swapPairs(ToList(vector<int>(case3, case3 + _countof(case3)))));
    return 0;
}