#include "LEET_MY_CALENDAR_III.h"

#include "stdafx.h"

// https://leetcode.com/problems/my-calendar-iii

#include "LEET_MY_CALENDAR_III.h"
#include <map>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_MY_CALENDAR_III
{

    class Node
    {
    public:
        Node()
        {
            left = right = nullptr;
            answer = lazy = 0;
        }

        Node* left;
        Node* right;
        int answer;
        int lazy;

        void insert(int nodeBegin, int nodeEnd, int intervalBegin, int intervalEnd)
        {
            if (nodeBegin == intervalBegin && nodeEnd == intervalEnd)
            {
                this->answer += 1;
                this->lazy += 1;
            }
            else
            {
                int mid = (nodeBegin + nodeEnd) / 2;
                if (this->left == nullptr)
                {
                    this->left = new Node();
                    this->right = new Node();
                }
                this->left->answer += this->lazy;
                this->right->answer += this->lazy;
                this->left->lazy += this->lazy;
                this->right->lazy += this->lazy;
                this->lazy = 0;
                if (intervalBegin < mid) {
                    left->insert(nodeBegin, mid, intervalBegin, min(mid, intervalEnd));
                }
                if (intervalEnd > mid) {
                    right->insert(mid, nodeEnd, max(mid, intervalBegin), intervalEnd);
                }
                this->answer = max(this->left->answer, this->right->answer);
            }
        }

        void print(int nodeBegin, int nodeEnd, int indent)
        {
            if (this != nullptr)
            {
                for (int i = 0; i < indent; i++) {
                    cout << " ";
                }
                cout << "[" << nodeBegin << ", " << nodeEnd << ")" << answer << ", " << lazy;
                int mid = (nodeBegin + nodeEnd) / 2;
                this->left->print(nodeBegin, mid, indent + 2);
                this->right->print(mid, nodeEnd, indent + 2);
            }
        }
    };


    class MyCalendarThree
    {
    public:
        MyCalendarThree()
        {
            root = nullptr;
        }

        int book(int start, int end)
        {
            if (root == nullptr)
            {
                root = new Node();
            }
            root->insert(0, 1000000001, start, end);
            //root->print(1, 1000000001, 0);
            //cout << "------------------------------------------------------------------------" ;
            return root->answer;
        }
    private:
        Node* root;
    };
};

using namespace _LEET_MY_CALENDAR_III;

int LEET_MY_CALENDAR_III()
{
    MyCalendarThree m;
    cout << m.book(10, 20) << endl; // returns 1
    cout << m.book(50, 60) << endl; // returns 1
    cout << m.book(10, 40) << endl; // returns 2
    cout << m.book(5, 15) << endl; // returns 3
    cout << m.book(5, 10) << endl; // returns 3
    cout << m.book(25, 55) << endl; // returns 3
    return 0;
}