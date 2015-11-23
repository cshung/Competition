#include "stdafx.h"

// https://leetcode.com/problems/find-median-from-data-stream/

#include "LEET_FIND_MEDIAN_FROM_DATA_STREAM.h"
#include <functional>
#include <queue>
#include <vector>
#include <iostream>

using namespace std;

namespace _LEET_FIND_MEDIAN_FROM_DATA_STREAM
{
    class MedianFinder
    {
    private:
        priority_queue<int> small;
        priority_queue<int> large;
    public:

        // Adds a number into the data structure.
        void addNum(int num)
        {
            int size = small.size() + large.size();
            if (size == 0)
            {
                small.push(num);
            }
            else if (size == 1)
            {
                int oldValue = small.top();
                if (oldValue < num)
                {
                    large.push(-num);
                }
                else
                {
                    small.pop();
                    small.push(num);
                    large.push(-oldValue);
                }
            }
            else
            {
                int maximal_small = small.top();
                int minimal_large = -large.top();
                if (size % 2 == 0)
                {
                    if (num <= minimal_large)
                    {
                        small.push(num);
                    }
                    else
                    {
                        large.pop();
                        small.push(minimal_large);
                        large.push(-num);
                    }
                }
                else
                {
                    if (num >= maximal_small)
                    {
                        large.push(-num);
                    }
                    else
                    {
                        small.pop();
                        small.push(num);
                        large.push(-maximal_small);
                    }
                }
            }
        }

        // Returns the median of current data stream
        double findMedian()
        {
            int size = small.size() + large.size();
            if (size % 2 == 0)
            {
                return (small.top() - large.top()) / 2.0;
            }
            else
            {
                return small.top();
            }
            return 0;
        }
    };
};

using namespace _LEET_FIND_MEDIAN_FROM_DATA_STREAM;

int LEET_FIND_MEDIAN_FROM_DATA_STREAM()
{
    MedianFinder mf;
    mf.addNum(1);
    mf.addNum(2);
    cout << (mf.findMedian() == 1.5) << endl;
    mf.addNum(3);
    cout << (mf.findMedian() == 2) << endl;
    return 0;
}