#include "stdafx.h"

// https://leetcode.com/problems/ugly-number-ii/

#include "LEET_UGLY_NUMBER_II.h"
#include <queue>
#include <iostream>
#include <vector>

using namespace std;

namespace _LEET_UGLY_NUMBER_II
{
    typedef long long int64;

    class Solution
    {
    public:
        int nthUglyNumber(int n)
        {
            if (n == 1)
            {
                return 1;
            }
            int count = 1;
            queue<int64> queue2;
            queue<int64> queue3;
            queue<int64> queue5;
            queue2.push(2);
            queue3.push(3);
            queue5.push(5);
            int64 currentUglyNumber = 1;
            while (count < n)
            {
                int64 front2 = queue2.front();
                int64 front3 = queue3.front();
                int64 front5 = queue5.front();

                if (front2 < front3 && front2 < front5)
                {
                    currentUglyNumber = front2;
                    queue2.pop();
                    queue2.push(currentUglyNumber * 2);
                    queue3.push(currentUglyNumber * 3);
                    queue5.push(currentUglyNumber * 5);
                    count++;
                }
                else if (front3 < front2 && front3 < front5)
                {
                    currentUglyNumber = front3;
                    queue3.pop();
                    queue3.push(currentUglyNumber * 3);
                    queue5.push(currentUglyNumber * 5);
                    count++;
                }
                else if (front5 < front2 && front5 < front3)
                {
                    currentUglyNumber = front5;
                    queue5.pop();
                    queue5.push(currentUglyNumber * 5);
                    count++;
                }
            }

            return (int)currentUglyNumber;
        }
    };
};

using namespace _LEET_UGLY_NUMBER_II;

int LEET_UGLY_NUMBER_II()
{
    Solution s;
    cout << (s.nthUglyNumber(1600) == 1399680000) << endl;
    
    return 0;
}