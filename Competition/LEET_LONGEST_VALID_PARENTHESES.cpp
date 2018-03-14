#include "stdafx.h"

// https://leetcode.com/problems/longest-valid-parentheses/

#include "LEET_LONGEST_VALID_PARENTHESES.h"
#include <stack>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_LONGEST_VALID_PARENTHESES
{
    class Solution
    {
    public:
        int longestValidParentheses(string s)
        {
            stack<int> st;
            st.push(-1);
            int m = 0;
            for (int i = 0; i < s.size(); i++)
            {
                if (s[i] == '(')
                {
                    if (st.top() == -1)
                    {
                        st.pop();
                        st.push(i);
                    }
                    st.push(-1);
                }
                else
                {
                    st.pop();
                    if (st.size() > 0)
                    {
                        if (st.top() != -1)
                        {
                            m = max(m, i - st.top() + 1);
                        }
                    }
                    else
                    {
                        st.push(-1);
                    }
                }
            }
            return m;
        }
    };
};

using namespace _LEET_LONGEST_VALID_PARENTHESES;

int LEET_LONGEST_VALID_PARENTHESES()
{
    Solution solution;
    cout << solution.longestValidParentheses("(()") << endl;
    cout << solution.longestValidParentheses(")()())") << endl;
    return 0;
}