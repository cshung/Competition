#include "stdafx.h"

// https://leetcode.com/problems/pascals-triangle/

#include "LEET_PASCAL_TRIANGLE.h"

#include <vector>
#include <set>
#include <map>
#include <iostream>

using namespace std;

namespace _LEET_PASCAL_TRIANGLE
{
    class Solution {
    public:
        vector<vector<int> > generate(int numRows) {
            vector<vector<int> > answer;
            answer.resize(numRows);
            for (int i = 0; i < numRows; i++)
            {
                int rowLength = i + 1;
                answer[i].resize(rowLength);
                if (i == 0)
                {
                    answer[i][0] = 1;
                }
                else
                {
                    answer[i][0] = 1;
                    for (int j = 1; j < rowLength - 1; j++)
                    {
                        answer[i][j] = answer[i - 1][j - 1] + answer[i -1][j];
                    }
                    answer[i][rowLength - 1] = 1;
                }
            }

            return answer;
        }
    };
};

using namespace _LEET_PASCAL_TRIANGLE;

int LEET_PASCAL_TRIANGLE()
{
    Solution solution;
    vector<vector<int> > answer = solution.generate(5);
    for (unsigned int i = 0; i < 5; i++)
    {
        for (unsigned int j = 0; j < answer[i].size(); j++)
        {
            cout << answer[i][j] << " ";
        }

        cout << endl;
    }
    return 0;
}