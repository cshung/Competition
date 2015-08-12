#include "stdafx.h"

// https://leetcode.com/problems/count-primes/

#include "LEET_COUNT_PRIMES.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_COUNT_PRIMES
{
    class Solution {
    public:
        int countPrimes(int n)
        {
            
            bool* sieve = new bool[n];
            for (int i = 0; i < n; i++)
            {
                // Initially all numbers are considered prime
                sieve[i] = true;
            }
            for (int i = 2; i * i < n; i++)
            {
                if (sieve[i])
                {
                    
                    for (int j = i * i; j < n; j = j + i)
                    {
                        sieve[j] = false;
                    }
                }
            }
            int prime_count = 0;
            for (int i = 2; i < n; i++)
            {
                if (sieve[i])
                {
                    prime_count++;
                }
            }
            delete[] sieve;
            return prime_count;
        }
    };
};

using namespace _LEET_COUNT_PRIMES;

int LEET_COUNT_PRIMES()
{
    Solution solution;
    cout << solution.countPrimes(100) << endl;
    return 0;
}