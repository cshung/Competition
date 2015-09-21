#include "stdafx.h"

// https://leetcode.com/problems/gray-code/

#include "LEET_GRAY_CODE.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

namespace _LEET_GRAY_CODE
{
    class Solution
    {
    public:
        vector<int> grayCode(int n)
        {
            unsigned int size = 1 << n;
            vector<int> solution;
            solution.resize(size);
            for (unsigned int i = 0; i < size; i++)
            {
                /*
                 * The fun of this exercies reside in the proof of this formula
                 * The key idea is that the 'mirror' image of a number is the 2^n - 1 - x
                 * 2^n is a bit sequence of all 1, so the subtraction is simply flipping all bits
                 * and if you flip all the bits of both operand of xor, the result is unchanged.
                 */
                solution[i] = (i >> 1) ^ i;
            }
            return solution;
        }
    };
};

using namespace _LEET_GRAY_CODE;

int LEET_GRAY_CODE()
{
    Solution s;
    vector<int> gray = s.grayCode(4);
    for (unsigned int i = 0; i < gray.size(); i++)
    {
        cout << gray[i] << endl;
    }
    return 0;
}