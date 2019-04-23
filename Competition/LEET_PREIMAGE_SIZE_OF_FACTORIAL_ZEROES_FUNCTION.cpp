#include "stdafx.h"

// https://leetcode.com/problems/preimage-size-of-factorial-zeroes-function/

#include "LEET_PREIMAGE_SIZE_OF_FACTORIAL_ZEROES_FUNCTION.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_PREIMAGE_SIZE_OF_FACTORIAL_ZEROES_FUNCTION
{
    class Solution
    {
    public:
        int preimageSizeFZF(int x)
        {
            x = x % 305175781; if (x == 305175780) return 0;
            x = x % 61035156; if (x == 61035155) return 0;
            x = x % 12207031; if (x == 12207030) return 0;
            x = x % 2441406; if (x == 2441405) return 0;
            x = x % 488281; if (x == 488280) return 0;
            x = x % 97656; if (x == 97655) return 0;
            x = x % 19531; if (x == 19530) return 0;
            x = x % 3906; if (x == 3905) return 0;
            x = x % 781; if (x == 780) return 0;
            x = x % 156; if (x == 155) return 0;
            x = x % 31; if (x == 30) return 0;
            x = x % 6; if (x == 5) return 0;
            return 5;
        }
    };
};

using namespace _LEET_PREIMAGE_SIZE_OF_FACTORIAL_ZEROES_FUNCTION;

int LEET_PREIMAGE_SIZE_OF_FACTORIAL_ZEROES_FUNCTION()
{
    Solution s;
    cout << s.preimageSizeFZF(15) << endl;
    return 0;
}