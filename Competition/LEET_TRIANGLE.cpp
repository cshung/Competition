#include "stdafx.h"

// https://leetcode.com/problems/triangle/

#include "LEET_TRIANGLE.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_TRIANGLE
{
    class Solution
    {
    public:
        int minimumTotal(vector<vector<int>>& triangle)
        {
            int n = triangle.size();
            int answer = ~(1 << 31);
            vector<int> buffer1;
            vector<int> buffer2;
            buffer1.resize(n);
            buffer2.resize(n);
            vector<int>* pBuffer1 = &buffer1;
            vector<int>* pBuffer2 = &buffer2;
            for (int i = 0; i < n; i++)
            {
                vector<int>& last_minimum = *pBuffer1;
                vector<int>& this_minimum = *pBuffer2;
                if (i == 0)
                {
                    this_minimum[0] = triangle[0][0];
                }
                else
                {
                    for (int j = 0; j < i + 1; j++)
                    {
                        if (j == 0)
                        {
                            this_minimum[0] = last_minimum[0];
                        }
                        else if (j == i)
                        {
                            this_minimum[i] = last_minimum[i - 1];
                        }
                        else
                        {
                            this_minimum[j] = min(last_minimum[j - 1], last_minimum[j]);
                        }
                        this_minimum[j] += triangle[i][j];
                    }
                }
                if (i == n - 1)
                {
                    answer = this_minimum[0];
                    for (int j = 1; j < i + 1; j++)
                    {
                        answer = min(answer, this_minimum[j]);
                    }
                }

                swap(pBuffer1, pBuffer2);
            }
            return answer;
        }
    };
};

using namespace _LEET_TRIANGLE;

int LEET_TRIANGLE()
{
    Solution solution;
    vector<int> a;
    vector<int> b;
    vector<int> c;
    vector<int> d;
    vector<vector<int>> triangle;
    a.push_back(2);
    b.push_back(3); b.push_back(4);
    c.push_back(6); c.push_back(5); c.push_back(7);
    d.push_back(4); d.push_back(1); d.push_back(8); d.push_back(3);
    triangle.push_back(a);
    triangle.push_back(b);
    triangle.push_back(c);
    triangle.push_back(d);
    cout << solution.minimumTotal(triangle) << endl;
    return 0;
}