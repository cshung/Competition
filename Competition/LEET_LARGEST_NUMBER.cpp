#include "stdafx.h"

// https://leetcode.com/problems/count-and-say/

#include "LEET_LARGEST_NUMBER.h"
#include <list>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

namespace _LEET_LARGEST_NUMBER
{
    bool isBefore(string a, string b)
    {
        for (unsigned int i = 0; i < a.length() && i < b.length(); i++)
        {
            if (a[i] < b[i])
            {
                return false;
            }
            else if (a[i] > b[i])
            {
                return true;
            }
        }

        if (a.length() == b.length())
        {
            // True or false doesn't really matter here, they are the same
            return false;
        }
        else if (a.length() > b.length())
        {
            return isBefore(a.substr(b.length(), a.length() - b.length()), b);
        }
        else
        {
            return isBefore(a, b.substr(a.length(), b.length() - a.length()));
        }
    }

    class Solution
    {
    public:
        string largestNumber(vector<int> &num)
        {
            int n = num.size();
            vector<string> nums;
            vector<bool> free;

            for (int i = 0; i < n; i++)
            {
                stringstream iss;
                iss << num[i];
                nums.push_back(iss.str());
                free.push_back(true);
            }

            sort(nums.begin(), nums.end(), isBefore);

            stringstream oss;
            for (int i = 0; i < n; i++)
            {
                oss << nums[i];
            }

            string s = oss.str();

            if (s[0] == '0')
            {
                return "0";
            }
            else
            {
                return s;
            }
        }
    };
};

using namespace _LEET_LARGEST_NUMBER;

int LEET_LARGEST_NUMBER()
{
    Solution solution;
    // int data[] = {41,23,87,55,50,53,18,9,39,63,35,33,54,25,26,49,74,61,32,81,97,99,38,96,22,95,35,57,80,80,16,22,17,13,89,11,75,98,57,81,69,8,10,85,13,49,66,94,80,25,13,85,55,12,87,50,28,96,80,43,10,24,88,52,16,92,61,28,26,78,28,28,16,1,56,31,47,85,27,30,85,2,30,51,84,50,3,14,97,9,91,90,63,90,92,89,76,76,67,55};
    int data[] = {3, 30, 34, 5, 9};
    vector<int> input (data, data + sizeof(data) / sizeof(data[0]) );
    //input.push_back(34);
    //input.push_back(5);
    //input.push_back(9);
    cout << solution.largestNumber(input) << endl;
    return 0;
}