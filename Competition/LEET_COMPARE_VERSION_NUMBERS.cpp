#include "stdafx.h"

// https://leetcode.com/problems/compare-version-numbers/

#include "LEET_COMPARE_VERSION_NUMBERS.h"
#include <map>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

namespace _LEET_COMPARE_VERSION_NUMBERS
{
    class Solution
    {
    public:
        int compareVersion(string version1, string version2)
        {
            int v1s = 0;
            int v2s = 0;
            int v1e = 0;
            int v2e = 0;
            while (true)
            {
                while (v1e < (int)version1.size() && version1[v1e] != '.')
                {
                    v1e++;
                }

                while (v2e < (int)version2.size() && version2[v2e] != '.')
                {
                    v2e++;
                }

                int len1 = v1e - v1s;
                int len2 = v2e - v2s;

                int length = max(len1, len2);

                if (length == 0)
                {
                    return 0;
                }

                for (int i = 0; i < length; i++)
                {
                    int v1ci = v1e - length + i;
                    int v2ci = v2e - length + i;
                    char v1c = v1ci < v1s ? '0' : version1[v1ci];
                    char v2c = v2ci < v2s ? '0' : version2[v2ci];
                    if (v1c > v2c)
                    {
                        return 1;
                    }
                    else if (v2c > v1c)
                    {
                        return -1;
                    }
                }

                v1e = v1s = v1e + 1;
                v2e = v2s = v2e + 1;
            }
        }
    };
};

using namespace _LEET_COMPARE_VERSION_NUMBERS;

int LEET_COMPARE_VERSION_NUMBERS()
{
    Solution s;
    cout << (s.compareVersion("1.0.1", "1.01") == -1) << endl;
    return 0;
}