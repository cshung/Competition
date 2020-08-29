#include "stdafx.h"

// https://leetcode.com/problems/pancake-sorting/

#include "LEET_PANCAKE_SORTING.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_PANCAKE_SORTING
{
    class Solution {
    public:
        vector<int> pancakeSort(vector<int>& A)
        {
            vector<int> answer;
            int i = A.size() - 1;
            while (i > 0)
            {
                int maxIndex = 0;
                int maxValue = 0;
                for (int j = 0; j <= i; j++)
                {
                    if (A[j] > maxValue)
                    {
                        maxValue = A[j];
                        maxIndex = j;
                    }
                }
                if (maxIndex != i)
                {
                    int left;
                    int right;
                    if (maxIndex != 0)
                    {
                        left = 0;
                        right = maxIndex;
                        answer.push_back(maxIndex + 1);
                        while (left < right)
                        {
                            swap(A[left], A[right]);
                            left++;
                            right--;
                        }
                    }
                    left = 0;
                    right = i;
                    answer.push_back(i + 1);
                    while (left < right)
                    {
                        swap(A[left], A[right]);
                        left++;
                        right--;
                    }
                }
                i--;
            }
            return answer;
        }
    };
};

using namespace _LEET_PANCAKE_SORTING;

int LEET_PANCAKE_SORTING()
{
    Solution solution;
    int problem_array[] = { 3,2,4,1 };
    vector<int> problem(problem_array, problem_array + _countof(problem_array));
    auto answers = solution.pancakeSort(problem);
    for (auto value : problem)
    {
        cout << value << " ";
    }
    cout << endl;
    for (auto answer : answers)
    {
        cout << answer << " ";
    }
    cout << endl;
    return 0;
}