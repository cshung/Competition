#include "stdafx.h"

// https://leetcode.com/problems/implement-stack-using-queues/

#include "LEET_IMPLEMENT_STACK_USING_QUEUES.h"
#include <queue>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_IMPLEMENT_STACK_USING_QUEUES
{
    class Stack
    {
    private:
        queue<int> data;
    public:
        // Push element x onto stack.
        void push(int x)
        {
            data.push(x);
            for (unsigned int i = 0; i < data.size() - 1; i++)
            {
                data.push(data.front());
                data.pop();
            }
        }

        // Removes the element on top of the stack.
        void pop()
        {
            data.pop();
        }

        // Get the top element.
        int top()
        {
            return data.front();
        }

        // Return whether the stack is empty.
        bool empty()
        {
            return data.empty();
        }
    };
};

using namespace _LEET_IMPLEMENT_STACK_USING_QUEUES;

int LEET_IMPLEMENT_STACK_USING_QUEUES()
{
    Stack stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);
    cout << (stack.top() == 3) << endl;
    stack.pop();
    cout << (stack.top() == 2) << endl;
    stack.pop();
    cout << (stack.top() == 1) << endl;
    stack.pop();
    cout << (stack.empty()) << endl;
    return 0;
}