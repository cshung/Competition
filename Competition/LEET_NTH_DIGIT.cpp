#include "stdafx.h"

// https://leetcode.com/problems/nth-digit/

#include "LEET_NTH_DIGIT.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_NTH_DIGIT
{
    class Solution
    {
    public:
        int findNthDigit(int n)
        {
            // Programmer reasons with 0 based index
            n--;
            long long blockBase = 1;
            int blockValueSize = 1;
            while (true)
            {
                // An exclusive index for the 'value' that is in the block
                long long blockCeil = blockBase * 10;

                // Number of digits in the block
                long long blockSizeLong = (blockCeil - blockBase) * blockValueSize;

                int intMax = ~(1 << 31);

                int blockSize = blockSizeLong > intMax ? intMax : (int)blockSizeLong;

                if (n < blockSize)
                {
                    // We are now within a block

                    // What is the index in the block are we talking about?
                    int index = n / blockValueSize;
                    
                    // Now we get the value of that number
                    long long value = blockBase + index;

                    // Which digit (are we talking about), this is 0 based, counting from most significant digit
                    int digit = n % blockValueSize;

                    // Change it to 1 based
                    digit++;

                    // Counting from the least significant digit instead
                    digit = blockValueSize - digit + 1;

                    // Digit extraction
                    while (digit > 1)
                    {
                        value /= 10;
                        digit--;
                    }
                    return value % 10;
                }
                else
                {
                    // Move to the next block
                    n -= blockSize;
                    blockBase *= 10;
                    blockValueSize++;
                }
            }
        }
    };
};

using namespace _LEET_NTH_DIGIT;

int LEET_NTH_DIGIT()
{
    Solution solution;
    for (int i = 1; i <= 200; i++)
    {
        cout << solution.findNthDigit(i);
    }
    cout << endl;
    return 0;
}