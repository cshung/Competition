#include "stdafx.h"

// https://leetcode.com/problems/flatten-a-multilevel-doubly-linked-list/

#include "LEET_FLATTEN_A_MULTILEVEL_DOUBLY_LINKED_LIST.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_FLATTEN_A_MULTILEVEL_DOUBLY_LINKED_LIST
{
    class Node
    {
    public:
        int val;
        Node* prev;
        Node* next;
        Node* child;
    };

    class Solution
    {
    public:
        Node* flatten(Node* head)
        {
            flatten_helper(head);
            return head;
        }
    private:
        Node* flatten_helper(Node* head)
        {
            if (head == nullptr)
            {
                return nullptr;
            }
            Node* prev = nullptr;
            Node* cursor = head;
            while (cursor != nullptr)
            {
                if (cursor->child != nullptr)
                {
                    Node* child_head = cursor->child;
                    cursor->child = nullptr;
                    Node* next = cursor->next;
                    Node* child_tail = flatten_helper(child_head);
                    cursor->next = child_head;
                    child_head->prev = cursor;
                    if (next != nullptr)
                    {
                        next->prev = child_tail;
                        child_tail->next = next;
                    }
                    prev = child_tail;
                    cursor = next;
                }
                else
                {
                    prev = cursor;
                    cursor = cursor->next;
                }
            }
            return prev;
        }
    };
};

using namespace _LEET_FLATTEN_A_MULTILEVEL_DOUBLY_LINKED_LIST;

int LEET_FLATTEN_A_MULTILEVEL_DOUBLY_LINKED_LIST()
{
    Node n1; n1.val = 1;
    Node n2; n2.val = 2;
    Node n3; n3.val = 3;
    Node n4; n4.val = 4;
    Node n5; n5.val = 5;
    Node n6; n6.val = 6;
    Node n7; n7.val = 7;
    Node n8; n8.val = 8;
    Node n9; n9.val = 9;
    Node n10; n10.val = 10;
    Node n11; n11.val = 11;
    Node n12; n12.val = 12;

    n1.prev = nullptr;
    n1.next = &n2;
    n1.child = nullptr;
    n2.prev = &n1;
    n2.next = &n3;
    n2.child = nullptr;
    n3.prev = &n2;
    n3.next = &n4;
    n3.child = &n7;
    n4.prev = &n3;
    n4.next = &n5;
    n4.child = nullptr;
    n5.prev = &n4;
    n5.next = &n6;
    n5.child = nullptr;
    n6.prev = &n5;
    n6.next = nullptr;
    n6.child = nullptr;
    n7.prev = nullptr;
    n7.next = &n8;
    n7.child = nullptr;
    n8.prev = &n7;
    n8.next = &n9;
    n8.child = &n11;
    n9.prev = &n8;
    n9.next = &n10;
    n9.child = nullptr;
    n10.prev = &n9;
    n10.next = nullptr;
    n10.child = nullptr;
    n11.prev = nullptr;
    n11.next = &n12;
    n11.child = nullptr;
    n12.prev = &n11;
    n12.next = nullptr;
    n12.child = nullptr;
    Solution s;
    Node* answer = s.flatten(&n1);
    Node* cursor = answer;
    while (cursor != nullptr)
    {
        cout << cursor->val << " ";
        cursor = cursor->next;
    }
    return 0;
}