#include "stdafx.h"

// https://leetcode.com/problems/evaluate-reverse-polish-notation/

#include "LEET_EVALUATE_REVERSE_POLISH_NOTATION.h"
#include <stack>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_EVALUATE_REVERSE_POLISH_NOTATION
{
    class Solution {
    public:
        int evalRPN(vector<string>& tokens) {
            stack<int> args;
            for (int i = 0; i < tokens.size(); i++)
            {
                if (tokens[i] == "+")
                {
                    int a = args.top(); args.pop();
                    int b = args.top(); args.pop();
                    args.push(a + b);
                }
                else if (tokens[i] == "-")
                {
                    int a = args.top(); args.pop();
                    int b = args.top(); args.pop();
                    args.push(b - a);
                }
                else if (tokens[i] == "*")
                {
                    int a = args.top(); args.pop();
                    int b = args.top(); args.pop();
                    args.push(a * b);
                }
                else if (tokens[i] == "/")
                {
                    int a = args.top(); args.pop();
                    int b = args.top(); args.pop();
                    args.push(b / a);
                }
                else
                {
                    args.push(stoi(tokens[i]));
                }
            }

            return args.top();
        }
    };
};

using namespace _LEET_EVALUATE_REVERSE_POLISH_NOTATION;

int LEET_EVALUATE_REVERSE_POLISH_NOTATION()
{
    Solution solution;
    string input_array[5] = { "4", "13","5","/","+" };
    vector<string> input(input_array, input_array + 5);
    cout << solution.evalRPN(input) << endl;
    return 0;
}