#include "stdafx.h"

// https://leetcode.com/problems/implement-queue-using-stacks/

#include "LEET_IMPLEMENT_QUEUE_USING_STACKS.h"
#include <map>
#include <iostream>
#include <stack>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_IMPLEMENT_QUEUE_USING_STACKS
{
    class Queue {
    public:
        // Push element x to the back of queue.
        void push(int x)
        {
            input_stack.push(x);
        }

        // Removes the element from in front of queue.
        void pop(void)
        {
            if (this->output_stack.size() == 0)
            {
                this->flow();
            }
            output_stack.pop();
        }

        // Get the front element.
        int peek(void)
        {
            if (this->output_stack.size() == 0)
            {
                this->flow();
            }
            return output_stack.top();
        }

        // Return whether the queue is empty.
        bool empty(void)
        {
            return this->input_stack.size() == 0 && this->output_stack.size() == 0;
        }
    private:
        stack<int> input_stack;
        stack<int> output_stack;
        void flow()
        {
            while (!this->input_stack.empty())
            {
                this->output_stack.push(this->input_stack.top());
                this->input_stack.pop();
            }
        }
    };
};

using namespace _LEET_IMPLEMENT_QUEUE_USING_STACKS;

int LEET_IMPLEMENT_QUEUE_USING_STACKS()
{
    Queue queue;
    cout << queue.empty() << endl;
    queue.push(1);
    cout << queue.peek() << endl;
    queue.pop();
    cout << queue.empty() << endl;
    queue.push(1);
    queue.push(2);
    cout << queue.peek() << endl;
    queue.pop();
    cout << queue.peek() << endl;
    queue.pop();
    return 0;
}