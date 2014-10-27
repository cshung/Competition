#include "stdafx.h"

// https://oj.leetcode.com/problems/longest-consecutive-sequence/

#include "LEET_LONGEST_CONSECUTIVE_SEQUENCE.h"

#include <vector>
#include <set>
#include <map>
#include <iostream>

using namespace std;

namespace _LEET_LONGEST_CONSECUTIVE_SEQUENCE
{
    class Solution {
    public:
        int longestConsecutive(vector<int> &num)
        {
            set<int> 	seen;		// A set keeping track of whether a number is seen or not
            map<int, int>	startChain;	// A map from the starting number to the chain size
            map<int, int>	endChain;	// A map from the ending number to the chain size

            for (unsigned int i = 0; i < num.size(); i++)
            {
                int value = num[i];
                if (seen.find(value) == seen.end())
                {
                    seen.insert(value);

                    map<int, int>::iterator peekStart = startChain.find(value + 1);
                    map<int, int>::iterator peekEnd = endChain.find(value - 1);

                    if (peekStart != startChain.end() && peekEnd != endChain.end())
                    {
                        // Attachable to the start and attachable to the end
                        int newStart = peekEnd->first - peekEnd->second + 1;
                        int newLength = peekEnd->second + 1 + peekStart->second;
                        int newEnd = newStart + newLength - 1;

                        startChain.erase(startChain.find(newStart));
                        endChain.erase(peekEnd);

                        startChain.erase(peekStart);
                        endChain.erase(endChain.find(newEnd));

                        startChain.insert(pair<int, int>(newStart, newLength));
                        endChain.insert(pair<int, int>(newEnd, newLength));
                    }
                    else if (peekStart != startChain.end() && peekEnd == endChain.end())
                    {
                        // Attachable to the start only
                        int newStart = peekStart->first - 1;
                        int newLength = peekStart->second + 1;
                        int newEnd = newStart + newLength - 1;

                        startChain.erase(peekStart);
                        endChain.erase(endChain.find(newEnd));

                        startChain.insert(pair<int, int>(newStart, newLength));
                        endChain.insert(pair<int, int>(newEnd, newLength));
                    }
                    else if (peekStart == startChain.end() && peekEnd != endChain.end())
                    {
                        // Attachable to the end only
                        int newEnd = peekEnd->first + 1;
                        int newLength = peekEnd->second + 1;
                        int newStart = newEnd - newLength + 1;

                        startChain.erase(startChain.find(newStart));
                        endChain.erase(peekEnd);

                        startChain.insert(pair<int, int>(newStart, newLength));
                        endChain.insert(pair<int, int>(newEnd, newLength));
                    }
                    else if (peekStart == startChain.end() && peekEnd == endChain.end())
                    {
                        // Nothing else could be done - create a chain by itself
                        int newStart = value;
                        int newEnd = value;
                        int newLength = 1;

                        startChain.insert(pair<int, int>(newStart, newLength));
                        endChain.insert(pair<int, int>(newEnd, newLength));
                    }
                }
            }

            int max = 0;
            for (map<int, int>::iterator startIterator = startChain.begin(); startIterator != startChain.end(); startIterator++)
            {
                int current = startIterator->second;
                if (current > max)
                {
                    max = current;
                }
            }
            return max;
        }
    };
};

using namespace _LEET_LONGEST_CONSECUTIVE_SEQUENCE;

int LEET_LONGEST_CONSECUTIVE_SEQUENCE()
{
    Solution solution;
    vector<int> nums;
    // 100, 4, 200, 1, 3, 2
    nums.push_back(100);
    nums.push_back(4);
    nums.push_back(200);
    nums.push_back(1);
    nums.push_back(3);
    nums.push_back(2);
    cout << solution.longestConsecutive(nums) << endl;
    return 0;
}