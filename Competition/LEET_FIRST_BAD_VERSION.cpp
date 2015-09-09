#include "stdafx.h"

// https://leetcode.com/problems/first-bad-version/

#include "LEET_FIRST_BAD_VERSION.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

namespace _LEET_FIRST_BAD_VERSION
{
    // Forward declaration of isBadVersion API.
    bool isBadVersion(int version)
    {
        return version >= 2147483647;
    }

    class Solution {
    private:
        int firstBadVersion(int begin, int end)
        {
            if (begin > end)
            {
                // There is no bad version
                return -1;
            }
            else if (end == begin + 1)
            {
                return end;
            }
            else
            {
                int mid = begin + (end - begin) / 2;
                if (isBadVersion(mid))
                {
                    return firstBadVersion(begin, mid);
                }
                else
                {
                    return firstBadVersion(mid, end);
                }
            }
        }
    public:
        int firstBadVersion(int n)
        {
            if (n == 2147483647)
            {
                if (isBadVersion(2147483646))
                {
                    return this->firstBadVersion(-1, 2147483647);
                }
                else if (isBadVersion(2147483647))
                {
                    return 2147483647;
                }
                else
                {
                    return -1;
                }
            }
            else
            {
                return this->firstBadVersion(-1, n + 1);
            }
        }
    };
};

using namespace _LEET_FIRST_BAD_VERSION;

int LEET_FIRST_BAD_VERSION()
{
    Solution s;
    cout << s.firstBadVersion(2147483647) << endl;
    return 0;
}