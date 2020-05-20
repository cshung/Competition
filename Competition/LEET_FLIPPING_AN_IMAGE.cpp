#include "stdafx.h"

// https://leetcode.com/problems/flipping-an-image

#include "LEET_FLIPPING_AN_IMAGE.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_FLIPPING_AN_IMAGE
{
    class Solution
    {
    public:
        vector<vector<int>> flipAndInvertImage(vector<vector<int>>& A)
        {
            vector<vector<int>> answer = A;
            int height = A.size();
            if (height == 0)
            {
                return answer;
            }
            int width = A[0].size();
            for (int r = 0; r < height; r++)
            {
                for (int c = 0; c < width; c++)
                {
                    answer[r][c] = 1 - A[r][width - c - 1];
                }
            }
            return answer;
        }
    };
};

using namespace _LEET_FLIPPING_AN_IMAGE;

int LEET_FLIPPING_AN_IMAGE()
{
    int test11_array[] = { 1, 1, 0 };
    int test12_array[] = { 1, 0, 1};
    int test13_array[] = { 0, 0, 0};
    vector<vector<int>> test1;
    vector<int> test11(test11_array, test11_array + _countof(test11_array));
    vector<int> test12(test12_array, test12_array + _countof(test12_array));
    vector<int> test13(test13_array, test13_array + _countof(test13_array));
    test1.push_back(test11);
    test1.push_back(test12);
    test1.push_back(test13);
    Solution solution;
    vector<vector<int>> answer = solution.flipAndInvertImage(test1);
    for (int r = 0; r < answer.size(); r++)
    {
        for (int c = 0; c < answer[0].size(); c++)
        {
            cout << answer[r][c];
        }
        cout << endl;
    }
    return 0;
}