#include "stdafx.h"

// https://www.hackerrank.com/challenges/s10-quartiles

#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdlib>
using namespace std;

void select(vector<int>& nums, int start, int end, vector<int>& goals, int goalStart, int goalEnd, vector<int>& result)
{
    if (nums.size() == 1)
    {
        result.push_back(nums[0]);
        return;
    }

    int pivotIndex = rand() % (end - start) + start;
    swap(nums[start], nums[pivotIndex]);

    int pivot = nums[start];
    int left = start;
    int right = end;

    // Maintain these variables
    int smallerEnd = left;             // [left, smallerEnd) are strictly smaller than the pivot
    int smallerOrEqualEnd = left + 1;  // [smallerEnd, smallerOrEqualEnd) are smaller or equal to the pivot
    int largerBegin = right;           // [largerBegin, right) are strictly larger than the pivot

    while (true)
    {
        while (smallerOrEqualEnd < nums.size() && nums[smallerOrEqualEnd] <= pivot)
        {
            if (nums[smallerOrEqualEnd] < pivot)
            {
                swap(nums[smallerEnd], nums[smallerOrEqualEnd]);
                smallerEnd++;
            }

            smallerOrEqualEnd++;
        }

        while (largerBegin > 0 && nums[largerBegin - 1] > pivot)
        {
            largerBegin--;
        }

        if (smallerOrEqualEnd == largerBegin)
        {
            break;
        }

        // [left, smallerEnd) are strictly smaller than the pivot
        // [smallerEnd, smallerOrEqualEnd) are equal to the pivot
        // [largerBegin, right) are strictly larger than the pivot

        // nums[smallerEnd] = pivot
        // nums[smallerOrEqualEnd] > pivot
        // nums[largerBegin - 1] <= pivot
        if (nums[largerBegin - 1] == pivot)
        {
            swap(nums[smallerOrEqualEnd], nums[largerBegin - 1]);
            smallerOrEqualEnd++;
            largerBegin--;
        }
        else
        {
            nums[smallerEnd] = nums[largerBegin - 1];
            nums[largerBegin - 1] = nums[smallerOrEqualEnd];
            nums[smallerOrEqualEnd] = pivot;
            smallerEnd++;
            smallerOrEqualEnd++;
            largerBegin--;
        }
    }

    int leftGoalEnd = -1;
    int pivotCount = 0;
    int rightGoalStart = -1;

    for (int i = goalStart; i < goalEnd; i++)
    {
        int k = goals[i] - left;
        int smallPortionLength = smallerEnd - left;
        if (k < smallPortionLength)
        {
        }
        else
        {
            if (leftGoalEnd == -1)
            {
                leftGoalEnd = i;
            }
            k -= smallPortionLength;
            int pivotPortionLength = smallerOrEqualEnd - smallerEnd;
            if (k < pivotPortionLength)
            {
                pivotCount++;
            }
            else
            {
                k -= pivotPortionLength;
                if (rightGoalStart == -1)
                {
                    rightGoalStart = i;
                    break;
                }
            }
        }
    }
    if (leftGoalEnd == -1)
    {
        leftGoalEnd = goalEnd;
    }

    if (leftGoalEnd > goalStart)
    {
        select(nums, left, smallerEnd, goals, goalStart, leftGoalEnd, result);
    }
    for (int i = 0; i < pivotCount; i++)
    {
        result.push_back(pivot);
    }
    if (rightGoalStart != -1)
    {
        select(nums, smallerOrEqualEnd, right, goals, rightGoalStart, goalEnd, result);
    }
}

int HACKER_RANK_S10_QUARTILES()
{
    int n;
    cin >> n;
    vector<int> data;
    data.resize(n);
    for (int i = 0; i < n; i++)
    {
        cin >> data[i];
    }
    vector<int> goals;
    vector<int> result;
    if (n % 4 == 3)
    {
        // [0, n/2) [n/2] [n/2 + 1, n)
        goals.push_back(n / 4);
        goals.push_back(n / 2);
        goals.push_back(n / 2 + 1 + n / 4);
        select(data, 0, n, goals, 0, goals.size(), result);
        cout << result[0] << endl;
        cout << result[1] << endl;
        cout << result[2] << endl;
    }
    else if (n % 4 == 2)
    {
        // [0, n/2) [n/2, n)
        goals.push_back(n / 4);
        goals.push_back(n / 2 - 1);
        goals.push_back(n / 2);
        goals.push_back(n / 2 + n / 4);
        select(data, 0, n, goals, 0, goals.size(), result);
        cout << result[0] << endl;
        cout << (result[1] + result[2]) / 2 << endl;
        cout << result[3] << endl;
    }
    else if (n % 4 == 1)
    {
        // [0, n/2) {n/2}, [n/2 + 1, n]
        goals.push_back(n / 4 - 1);
        goals.push_back(n / 4);
        goals.push_back(n / 2);
        goals.push_back(n / 2 + n / 4);
        goals.push_back(n / 2 + n / 4 + 1);
        select(data, 0, n, goals, 0, goals.size(), result);
        cout << (result[0] + result[1]) / 2 << endl;
        cout << result[2] << endl;
        cout << (result[3] + result[4]) / 2 << endl;
    }
    else if (n % 4 == 0)
    {
        // [0, n/2) [n/2, n]
        goals.push_back(n / 4 - 1);
        goals.push_back(n / 4);
        goals.push_back(n / 2 - 1);
        goals.push_back(n / 2);
        goals.push_back(n / 2 + n / 4 - 1);
        goals.push_back(n / 2 + n / 4);
        select(data, 0, n, goals, 0, goals.size(), result);
        cout << (result[0] + result[1]) / 2 << endl;
        cout << (result[2] + result[3]) / 2 << endl;
        cout << (result[4] + result[5]) / 2 << endl;
    }

    return 0;
}