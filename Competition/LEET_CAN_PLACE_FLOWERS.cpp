#include "stdafx.h"

// https://leetcode.com/problems/can-place-flowers

#include "LEET_CAN_PLACE_FLOWERS.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_CAN_PLACE_FLOWERS
{
    class Solution
    {
    public:
        bool canPlaceFlowers(vector<int>& flowerbed, int n)
        {
            for (size_t i = 0; i < flowerbed.size(); i++)
            {
                if (n == 0)
                {
                    break;
                }
                else
                {
                    if ((i == 0 || flowerbed[i - 1] == 0) && flowerbed[i] == 0 && ((i == flowerbed.size() - 1) || flowerbed[i + 1] == 0))
                    {
                        flowerbed[i] = 1;
                        n--;
                    }
                }
            }
            return n == 0;
        }
    };
};

using namespace _LEET_CAN_PLACE_FLOWERS;

int LEET_CAN_PLACE_FLOWERS()
{
    Solution solution;
    int test_array[] = { 1, 0, 0, 0, 1 };
    vector<int> test(test_array, test_array + _countof(test_array));
    cout << solution.canPlaceFlowers(test, 1) << endl;
    return 0;
}