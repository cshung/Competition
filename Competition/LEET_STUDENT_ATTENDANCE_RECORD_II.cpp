#include "stdafx.h"

// https://leetcode.com/problems/student-attendance-record-ii

#include "LEET_STUDENT_ATTENDANCE_RECORD_II.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_STUDENT_ATTENDANCE_RECORD_II
{
    class Solution {
    public:
        int add(int x, int y)
        {
            return (x + y) % 1000000007;
        }

        int checkRecord(int n) {
            if (n == 0)
            {
                return 0;
            }

            int a = 1, b = 1, c = 0, d = 1, e = 0, f = 0;

            for (int i = 1; i < n; i++)
            {
                int ta = add(add(a, b), c);
                int tb = a;
                int tc = b;
                int td = add(add(add(add(add(a, b), c), d), e), f);
                int te = d;
                int tf = e;

                a = ta;
                b = tb;
                c = tc;
                d = td;
                e = te;
                f = tf;
            }

            return add(a, add(b, add(c, add(d, add(e, f)))));
        }
    };
};

using namespace _LEET_STUDENT_ATTENDANCE_RECORD_II;

int LEET_STUDENT_ATTENDANCE_RECORD_II()
{
    Solution solution;
    for (int i = 1; i <= 50; i++)
    {
        cout << solution.checkRecord(i) << endl;
    }
    return 0;
}