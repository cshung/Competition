#include "stdafx.h"

// https://leetcode.com/problems/palindrome-linked-list/

#include "LEET_PALINDROME_LINKED_LIST.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_PALINDROME_LINKED_LIST
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
        bool isPalindrome(ListNode* head)
        {
            unsigned int length = 0;
            ListNode* cursor = head;
            while (cursor != NULL)
            {
                cursor = cursor->next;
                length++;
            }
            if (length < 2)
            {
                return true;
            }

            int pointerWalkCount = length / 2; 
            cursor = head;
            ListNode* cursorPrev = NULL;
            for (int i = 0; i < pointerWalkCount; i++)
            {
                ListNode* next = cursor->next;
                cursor->next = cursorPrev;
                cursorPrev = cursor;
                cursor = next;
            }

            ListNode* left = cursorPrev;
            ListNode* leftNext = cursor;
            ListNode* right = cursor;
            if (length % 2 == 1)
            {
                right = right->next;
            }

            bool match = true;
            for (int i = 0; i < pointerWalkCount; i++)
            {
                match = match && (left->val == right->val);
                ListNode* leftPrev = left->next;
                left->next = leftNext;
                leftNext = left;
                left = leftPrev;
                right = right->next;
            }

            return match;
        }
    };

    void test(vector<int> data)
    {
        Solution solution;
        ListNode* head = NULL;
        ListNode* tail = NULL;
        for (unsigned int i = 0; i < data.size(); i++)
        {
            ListNode* newNode = new ListNode(data[i]);
            if (tail == NULL)
            {
                head = tail = newNode;
            }
            else
            {
                tail->next = newNode;
                tail = newNode;
            }
        }
        cout << solution.isPalindrome(head) << endl;
        ListNode* cursor = head;
        while (cursor != NULL)
        {
            ListNode* temp = cursor->next;
            delete cursor;
            cursor = temp;
        }
    }
};

using namespace _LEET_PALINDROME_LINKED_LIST;

int LEET_PALINDROME_LINKED_LIST()
{
    int case1[] = { 1, 2, 3 };
    int case2[] = { 1, 2, 2, 1 };
    test(vector<int>(case1, case1 + _countof(case1)));
    test(vector<int>(case2, case2 + _countof(case2)));
    return 0;
}