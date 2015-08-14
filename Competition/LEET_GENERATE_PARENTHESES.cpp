#include "stdafx.h"

// https://leetcode.com/problems/generate-parentheses/

#include "LEET_GENERATE_PARENTHESES.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_GENERATE_PARENTHESES
{
    class Solution {
    private:
        void generateParenthesis(string prefix, int nOpen, int nClose, vector<string>& solution)
        {
            if (nOpen == 0 && nClose == 0)
            {
                solution.push_back(prefix);
            }
            if (nOpen > 0)
            {
                generateParenthesis(prefix + "(", nOpen - 1, nClose + 1, solution);
            }
            if (nClose > 0)
            {
                generateParenthesis(prefix + ")", nOpen, nClose - 1, solution);
            }
        }
    public:
        vector<string> generateParenthesis(int n) {
            vector<string> solution;
            generateParenthesis("", n, 0, solution);
            return solution;
        }
    };
};

using namespace _LEET_GENERATE_PARENTHESES;

int LEET_GENERATE_PARENTHESES()
{
    Solution solution;
    vector<string> set = solution.generateParenthesis(3);
    for (vector<string>::iterator si = set.begin(); si != set.end(); si++)
    {
        cout << *si << endl;
    }
    return 0;
}