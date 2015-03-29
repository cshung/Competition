#include "stdafx.h"

// https://leetcode.com/problems/single-number/

#include "LEET_SINGLE_NUMBER.h"
#include <map>
#include <iostream>
#include <vector>

using namespace std;

namespace _LEET_SINGLE_NUMBER
{
    class Solution
    {
    public:
        int singleNumber(int A[], int n)
        {
            int answer = 0;
            for (int i = 0 ; i < n; i++)
            {
                answer = answer ^ A[i];
            }

            return answer;
        }
    };
};

using namespace _LEET_SINGLE_NUMBER;

int LEET_SINGLE_NUMBER()
{
    int A[5];
    A[0] = 1;
    A[1] = 5;
    A[2] = 1;
    A[3] = 4;
    A[4] = 5;
    Solution solution;
    cout << solution.singleNumber(A, 5) << endl;
    return 0;
}