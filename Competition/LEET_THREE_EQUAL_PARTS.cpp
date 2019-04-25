#include "stdafx.h"

// https://leetcode.com/problems/three-equal-parts/

#include "LEET_THREE_EQUAL_PARTS.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_THREE_EQUAL_PARTS
{
    class Solution {
    public:
        vector<int> threeEqualParts(vector<int>& A)
        {
            vector<int> result;
            result.push_back(-1);
            result.push_back(-1);
            if (A.size() < 3)
            {
                return result;
            }
            int count = 0;
            for (int i = 0; i < A.size(); i++)
            {
                if (A[i] == 1)
                {
                    count++;
                }
            }
            if (count % 3 != 0)
            {
                return result;
            }
            if (count == 0)
            {
                result[0] = 0;
                result[1] = 2;
                return result;
            }
            int num_trailing_zeros = 0;
            int num_ones = count / 3;
            for (int i = A.size() - 1; i > 0; i--)
            {
                if (A[i] == 1)
                {
                    break;
                }
                else
                {
                    num_trailing_zeros++;
                }
            }
            count = 0;
            int first_end = -1;
            int second_end = -1;
            for (int i = 0; i < A.size(); i++)
            {
                if (A[i] == 1)
                {
                    count++;
                }
                if (count == num_ones && first_end == -1)
                {
                    first_end = i + num_trailing_zeros;
                }
                else if (count == num_ones * 2 && second_end == -1)
                {
                    second_end = i + num_trailing_zeros;
                }
            }
            int p = first_end;
            int q = second_end;
            int r = A.size() - 1;
            while (p != -1 && q != -1 && r != -1)
            {
                bool pass = true;
                int s = -1;
                if (pass && p != -1) { if (s == -1) { s = A[p]; } else if (s != A[p]) { pass = false; } }
                if (pass && q != -1) { if (s == -1) { s = A[q]; } else if (s != A[q]) { pass = false; } }
                if (pass && r != -1) { if (s == -1) { s = A[r]; } else if (s != A[r]) { pass = false; } }
                if (!pass)
                {
                    return result;
                }
                if (p != -1) { if (p == 0) { p = -1; } else { p--; } }
                if (q != -1) { if (q == first_end + 1) { q = -1; } else { q--; } }
                if (r != -1) { if (r == second_end + 1) { r = -1; } else { r--; } }
            }

            result[0] = first_end;
            result[1] = second_end + 1;
            return result;
        }
    };
};

using namespace _LEET_THREE_EQUAL_PARTS;

int LEET_THREE_EQUAL_PARTS()
{
    Solution solution;
    int test1_array[] = { 1,0,1,0,1 };
    vector<int> test1(test1_array, test1_array + _countof(test1_array));
    vector<int> actual1 = solution.threeEqualParts(test1);
    cout << actual1[0] << "," << actual1[1] << endl;
    return 0;
}