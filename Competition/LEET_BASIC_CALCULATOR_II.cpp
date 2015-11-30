#include "stdafx.h"

// https://leetcode.com/problems/basic-calculator-ii/

#include "LEET_BASIC_CALCULATOR_II.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <stack>

using namespace std;

namespace _LEET_BASIC_CALCULATOR_II
{
    class Solution
    {
    public:
        // Scanner states
        unsigned int position;
        char token;
        string* expression;

        void scan()
        {
            while (true)
            {
                if (position < (*expression).size())
                {
                    token = (*expression)[position++];
                }
                else
                {
                    token = '\0';
                }
                if (token != ' ')
                {
                    break;
                }
            }
        }

        // A hand written shift-reduce parser!
        // I could have adapted the previous top-down parsing solution
        // But there is a test case in the judge to stress memory usage, and a top down parser necessarily use up the space because of the recursion
        // A shift-reduce parser can save space by reducing early and not using the stack space
        int calculate(string s)
        {
            const int PLUS = 0;
            const int MINUS = 1;
            const int MULTIPLY = 2;
            const int DIVIDE = 3;

            stack<int> numStack;
            stack<int> sigStack;

            position = 0;
            expression = &s;

            const int EXPECT_DIGIT = 0;
            const int EXPECT_DIGIT_OR_OPERATOR = 1;
            int state = EXPECT_DIGIT;

            int currentNumber = 0;
            while (true)
            {
                scan();
                if (token >= '0' && token <= '9')
                {
                    state = EXPECT_DIGIT_OR_OPERATOR;
                    currentNumber = currentNumber * 10 + (token - '0');
                }
                else
                {
                    if (EXPECT_DIGIT)
                    {
                        throw 1;
                    }
                    numStack.push(currentNumber);
                    currentNumber = 0;
                    if (token == '*' || token == '/')
                    {
                        while (sigStack.size() > 0)
                        {
                            if (sigStack.top() >= MULTIPLY)
                            {
                                int operand2 = numStack.top(); numStack.pop();
                                int operand1 = numStack.top(); numStack.pop();
                                if (sigStack.top() == MULTIPLY)
                                {
                                    numStack.push(operand1 * operand2);
                                }
                                else if (sigStack.top() == DIVIDE)
                                {
                                    numStack.push(operand1 / operand2);
                                }
                                sigStack.pop();
                            }
                            else
                            {
                                break;
                            }
                        }

                        if (token == '*')
                        {
                            sigStack.push(MULTIPLY);
                        }
                        else if (token == '/')
                        {
                            sigStack.push(DIVIDE);
                        }

                        state = EXPECT_DIGIT;
                    }
                    else if (token == '+' || token == '-' || token == '\0')
                    {
                        while (sigStack.size() > 0)
                        {

                            int operand2 = numStack.top(); numStack.pop();
                            int operand1 = numStack.top(); numStack.pop();
                            if (sigStack.top() == PLUS)
                            {
                                numStack.push(operand1 + operand2);
                            }
                            else if (sigStack.top() == MINUS)
                            {
                                numStack.push(operand1 - operand2);
                            }
                            else if (sigStack.top() == MULTIPLY)
                            {
                                numStack.push(operand1 * operand2);
                            }
                            else if (sigStack.top() == DIVIDE)
                            {
                                numStack.push(operand1 / operand2);
                            }
                            sigStack.pop();
                        }
                        if (token == '+')
                        {
                            sigStack.push(PLUS);
                        }
                        else if (token == '-')
                        {
                            sigStack.push(MINUS);
                        }
                        else if (token == '\0')
                        {
                            return numStack.top();
                        }

                        state = EXPECT_DIGIT;
                    }
                }
            }

            return 0;
        }
    };
};

using namespace _LEET_BASIC_CALCULATOR_II;

int LEET_BASIC_CALCULATOR_II()
{
    Solution solution;
    cout << (solution.calculate("3+2*2") == 7) << endl;
    cout << (solution.calculate(" 3/2 ") == 1) << endl;
    cout << (solution.calculate(" 3+5 / 2 ") == 5) << endl;
    return 0;
}