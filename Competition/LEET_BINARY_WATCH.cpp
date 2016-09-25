#include "stdafx.h"

// https://leetcode.com/problems/binary-watch/

#include "LEET_BINARY_WATCH.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_BINARY_WATCH
{
    class Solution
    {
    public:
        vector<string> readBinaryWatch(int num)
        {
            vector<string> result;
            for (int h = 0; h < 12; h++)
            {
                for (int m = 0; m < 60; m++)
                {
                    int hour = h;
                    int minute = m;
                    int numHourOnes = 0;
                    int numMinuteOnes = 0;
                    for (int hourDigit = 0; hourDigit < 4; hourDigit++)
                    {
                        numHourOnes += hour & 1;
                        hour = hour >> 1;
                    }
                    for (int minuteDigit = 0; minuteDigit < 6; minuteDigit++)
                    {
                        numMinuteOnes += minute & 1;
                        minute = minute >> 1;
                    }
                    if (numHourOnes + numMinuteOnes == num)
                    {
                        if (h > 9)
                        {
                            char resultString[6];
                            resultString[0] = (h / 10) + '0';
                            resultString[1] = (h % 10) + '0';
                            resultString[2] = ':';
                            resultString[3] = (m / 10) + '0';
                            resultString[4] = (m % 10) + '0';
                            resultString[5] = '\0';
                            result.push_back(string(resultString));
                        }
                        else
                        {
                            char resultString[5];
                            resultString[0] = (h % 10) + '0';
                            resultString[1] = ':';
                            resultString[2] = (m / 10) + '0';
                            resultString[3] = (m % 10) + '0';
                            resultString[4] = '\0';
                            result.push_back(string(resultString));
                        }
                    }
                }
            }
            return result;
        }
    };
}

using namespace _LEET_BINARY_WATCH;

int LEET_BINARY_WATCH()
{
    Solution solution;
    vector<string> result = solution.readBinaryWatch(1);
    for (size_t i = 0; i < result.size(); i++)
    {
        cout << result[i] << endl;
    }
    return 0;
}