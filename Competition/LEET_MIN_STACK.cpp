#include "stdafx.h"

// https://leetcode.com/problems/min-stack/

#include "LEET_MIN_STACK.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>

using namespace std;

namespace _LEET_MIN_STACK
{
    class MinStack
    {
    private:
        stack<int> val_stack;
        stack<int> min_stack;
    public:
        void push(int x)
        {
            int minimum = val_stack.empty() ? x : min(x, this->getMin());
            val_stack.push(x);
            min_stack.push(minimum);
        }

        void pop()
        {
            val_stack.pop();
            min_stack.pop();
        }

        int top()
        {
            return val_stack.top();
        }

        int getMin()
        {
            return min_stack.top();
        }
    };
};

using namespace _LEET_MIN_STACK;

int LEET_MIN_STACK()
{
    MinStack s;
    s.push(2);
    s.push(0);
    s.push(3);
    s.push(0);
    cout << s.getMin() << endl;
    s.pop();
    cout << s.getMin() << endl;
    s.pop();
    cout << s.getMin() << endl;
    s.pop();
    cout << s.getMin() << endl;
    return 0;
}