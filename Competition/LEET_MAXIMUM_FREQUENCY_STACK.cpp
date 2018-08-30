#include "stdafx.h"

// https://leetcode.com/problems/maximum-frequency-stack/

#include "LEET_MAXIMUM_FREQUENCY_STACK.h"
#include <unordered_map>
#include <cassert>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_MAXIMUM_FREQUENCY_STACK
{
    class FreqStack {
    public:
        FreqStack() {

        }

        void push(int x)
        {
            auto probe = m_valueToNodeMap.find(x);
            if (probe == m_valueToNodeMap.end())
            {
                if (m_bottom == nullptr)
                {
                    assert(m_top == nullptr);
                    m_top = m_bottom = new MyStack();
                    m_top->m_prev = m_top->m_next = nullptr;
                }
                MyStackNode* newNode = new MyStackNode();
                newNode->m_stack = m_bottom;
                newNode->m_val = x;
                newNode->m_from = nullptr;
                newNode->m_next = m_bottom->m_m_top;
                m_bottom->m_m_top = newNode;
                m_valueToNodeMap.insert(make_pair(x, newNode));
            }
            else
            {
                MyStackNode* oldNode = probe->second;
                MyStack* myStack = oldNode->m_stack;
                if (myStack->m_next == nullptr)
                {
                    m_top = new MyStack();
                    m_top->m_m_top = nullptr;
                    m_top->m_prev = myStack;
                    m_top->m_next = nullptr;
                    myStack->m_next = m_top;
                }
                MyStackNode* newNode = new MyStackNode();
                newNode->m_stack = myStack->m_next;
                newNode->m_val = x;
                newNode->m_from = oldNode;
                newNode->m_next = myStack->m_next->m_m_top;
                myStack->m_next->m_m_top = newNode;
                m_valueToNodeMap[x] = newNode;
            }
        }

        int pop()
        {
            assert(m_top != nullptr);
            assert(m_top->m_m_top != nullptr);
            MyStackNode* toRemoveNode = m_top->m_m_top;
            int result = toRemoveNode->m_val;
            if (toRemoveNode->m_from == nullptr)
            {
                m_valueToNodeMap.erase(result);
            }
            else
            {
                m_valueToNodeMap[result] = toRemoveNode->m_from;
            }

            m_top->m_m_top = toRemoveNode->m_next;
            if (m_top->m_m_top == nullptr)
            {
                MyStack* toRemoveStack = m_top;
                m_top = toRemoveStack->m_prev;
                if (m_top == nullptr)
                {
                    m_bottom = nullptr;
                }
                else
                {
                    m_top->m_next = nullptr;
                }
                delete toRemoveStack;
            }
            delete toRemoveNode;
            return result;
        }

    private:

        struct MyStack;

        struct MyStackNode
        {
            MyStack*            m_stack;
            MyStackNode*		m_from;
            int			        m_val;
            MyStackNode*		m_next;
        };

        struct MyStack
        {
            MyStackNode*	m_m_top;
            MyStack*        m_prev;
            MyStack*	    m_next;
        };

        MyStack* m_bottom = nullptr;
        MyStack* m_top = nullptr;
        unordered_map<int, MyStackNode*> m_valueToNodeMap;
    };

};

using namespace _LEET_MAXIMUM_FREQUENCY_STACK;

int LEET_MAXIMUM_FREQUENCY_STACK()
{
    FreqStack freqStack;
    freqStack.push(5);
    freqStack.push(7);
    freqStack.push(5);
    freqStack.push(7);
    freqStack.push(4);
    freqStack.push(5);
    cout << freqStack.pop() << endl;
    cout << freqStack.pop() << endl;
    cout << freqStack.pop() << endl;
    cout << freqStack.pop() << endl;
    cout << freqStack.pop() << endl;
    cout << freqStack.pop() << endl;
    return 0;
}