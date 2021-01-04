#include "stdafx.h"

// https://leetcode.com/problems/largest-time-for-given-digits/

#include "LEET_LARGEST_TIME_FOR_GIVEN_DIGITS.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_LARGEST_TIME_FOR_GIVEN_DIGITS
{
    class Solution
    {
    public:
        string largestTimeFromDigits(vector<int>& A)
        {
            if (A.size() != 4)
            {
                return "";
            }
            vector<int> counts(10, 0);
            for (int i = 0; i < A.size(); i++)
            {
                counts[A[i]]++;
            }
            for (int hour = 23; hour >= 0; hour--)
            {
                for (int minute = 59; minute >= 0; minute--)
                {
                    int a = hour / 10;
                    int b = hour % 10;
                    int c = minute / 10;
                    int d = minute % 10;
                    if (counts[a] > 0)
                    {
                        counts[a]--;
                        if (counts[b] > 0)
                        {
                            counts[b]--;
                            
                            if (counts[c] > 0)
                            {
                                counts[c]--;
                                if (counts[d] > 0)
                                {
                                    ostringstream oss;
                                    oss << a << b << ":" << c << d;
                                    return oss.str();
                                }
                                counts[c]++;
                            }
                            counts[b]++;
                        }
                        counts[a]++;
                    }
                }
            }
            return "";
        }
    };
};

using namespace _LEET_LARGEST_TIME_FOR_GIVEN_DIGITS;

int LEET_LARGEST_TIME_FOR_GIVEN_DIGITS()
{
    Solution solution;
    int case1_array[] = {1,2,3,4};
    int case2_array[] = {5,5,5,5};
    int case3_array[] = {0,0,0,0};
    int case4_array[] = {0,0,1,0};
    vector<int> case1(case1_array, case1_array + _countof(case1_array));
    vector<int> case2(case2_array, case2_array + _countof(case2_array));
    vector<int> case3(case3_array, case3_array + _countof(case3_array));
    vector<int> case4(case4_array, case4_array + _countof(case4_array));
    cout << solution.largestTimeFromDigits(case1) << endl;
    cout << solution.largestTimeFromDigits(case2) << endl;
    cout << solution.largestTimeFromDigits(case3) << endl;
    cout << solution.largestTimeFromDigits(case4) << endl;
    return 0;
}