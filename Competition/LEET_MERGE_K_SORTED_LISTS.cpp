#include "stdafx.h"

// https://leetcode.com/problems/merge-k-sorted-lists/

#include "LEET_MERGE_K_SORTED_LISTS.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_MERGE_K_SORTED_LISTS
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
        ListNode *mergeKLists(vector<ListNode *> &lists)
        {
            ListNode* head = NULL;
            ListNode* tail = NULL;
            ListNode** heap = new ListNode*[lists.size()];
            int size = 0;
            
            // Step 1: Initialize the heap
            for (unsigned int i = 0; i < lists.size(); i++)
            {
                ListNode* to_insert = lists[i];
                if (to_insert != NULL)
                {
                    heap[size] = to_insert;
                    int current = size;
                    while (true)
                    {
                        if (current == 0)
                        {
                            break;
                        }
                        int parent = (current + 1) / 2 - 1;
                        if (heap[parent]->val > heap[current]->val)
                        {
                            swap(heap[parent], heap[current]);
                            current = parent;
                        }
                        else
                        {
                            break;
                        }
                    }
                    size++;
                }
            }

            // Step 2: Build the result
            while (size > 0)
            {
                // Step 2.1: Get the min
                ListNode* min = heap[0];
                ListNode* to_return = new ListNode(min->val);
                if (head == NULL)
                {
                    head = tail = to_return;
                }
                else
                {
                    tail->next = to_return;
                    tail = to_return;
                }

                // Step 2.2: Delete min
                heap[0] = heap[--size];
                int current = 0;
                while (true)
                {
                    int left_child = (current + 1) * 2 - 1;
                    int right_child = (current + 1) * 2;
                    if (right_child < size)
                    {
                        if (heap[left_child]->val < heap[right_child]->val)
                        {
                            if (heap[current]->val > heap[left_child]->val)
                            {
                                swap(heap[left_child], heap[current]);
                                current = left_child;
                            }
                            else
                            {
                                break;
                            }
                        }
                        else
                        {
                            if (heap[current]->val > heap[right_child]->val)
                            {
                                swap(heap[right_child], heap[current]);
                                current = right_child;
                            }
                            else
                            {
                                break;
                            }
                        }
                    }
                    else if (left_child < size)
                    {
                        if (heap[left_child]->val < heap[current]->val)
                        {
                            swap(heap[left_child], heap[current]);
                            current = left_child;
                        }
                        else
                        {
                            break;
                        }
                    }
                    else
                    {
                        break;
                    }
                }

                // Step 2.3: Add the next element into the heap
                if (min->next != NULL)
                {
                    heap[size] = min->next;
                    current = size;
                    while (true)
                    {
                        if (current == 0)
                        {
                            break;
                        }
                        int parent = (current + 1) / 2 - 1;
                        if (heap[parent]->val > heap[current]->val)
                        {
                            swap(heap[parent], heap[current]);
                            current = parent;
                        }
                        else
                        {
                            break;
                        }
                    }
                    size++;
                }
            }

            delete[] heap;
            return head;
        }
    };
};

using namespace _LEET_MERGE_K_SORTED_LISTS;

int LEET_MERGE_K_SORTED_LISTS()
{
    /*
    [{-8,-7,-7,-5,1,1,3,4},{-2},{-10,-10,-7,0,1,3},{2}]
     */

    ListNode a1(-8);
    ListNode a2(-7);
    ListNode a3(-7);
    ListNode a4(-5);
    ListNode a5(1);
    ListNode a6(1);
    ListNode a7(3);
    ListNode a8(4);

    ListNode b1(-2);

    ListNode c1(-10);
    ListNode c2(-10);
    ListNode c3(-7);
    ListNode c4(0);
    ListNode c5(1);
    ListNode c6(3);

    ListNode d1(2);

    a1.next = &a2;
    a2.next = &a3;
    a3.next = &a4;
    a4.next = &a5;
    a5.next = &a6;
    a6.next = &a7;
    a7.next = &a8;
    a8.next = NULL;

    c1.next = &c2;
    c2.next = &c3;
    c3.next = &c4;
    c4.next = &c5;
    c5.next = &c6;
    c6.next = NULL;

    vector<ListNode*> lists;
    lists.push_back(&a1);
    lists.push_back(&b1);
    lists.push_back(&c1);
    lists.push_back(&d1);
    Solution solution;
    ListNode* sorted = solution.mergeKLists(lists);
    while (sorted != NULL)
    {
        cout << sorted->val << " ";
        sorted = sorted->next;
    }
    cout << endl;
    
    return 0;
}
