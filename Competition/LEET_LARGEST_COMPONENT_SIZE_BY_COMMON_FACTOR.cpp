#include "stdafx.h"

// https://leetcode.com/problems/largest-component-size-by-common-factor/

#include "LEET_LARGEST_COMPONENT_SIZE_BY_COMMON_FACTOR.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_LARGEST_COMPONENT_SIZE_BY_COMMON_FACTOR
{

    class disjoint_set_union_find
    {
    public:
        disjoint_set_union_find(int n) : m_sets(n, -1), m_counts(n, 0)
        {
        }
        int find(int v)
        {
            if (m_sets[v] < 0)
            {
                return v;
            }
            else
            {
                return m_sets[v] = find(m_sets[v]);
            }
        }
        void union_sets(int u, int v)
        {
            int set1 = find(u);
            int set2 = find(v);
            if (set1 != set2)
            {
                int size1 = -m_sets[set1];
                int size2 = -m_sets[set2];
                if (size1 > size2)
                {
                    m_sets[set2] = set1;
                    m_sets[set1] -= size2;
                    m_counts[set1] += m_counts[set2];
                }
                else
                {
                    m_sets[set1] = set2;
                    m_sets[set2] -= size1;
                    m_counts[set2] += m_counts[set1];
                }
            }
        }
        void increase_count(int x)
        {
            m_counts[find(x)]++;
        }
        int get_count(int x)
        {
            return m_counts[find(x)];
        }
    private:
        vector<int> m_sets;
        vector<int> m_counts;
    };

    class Solution
    {
    public:
        int numPrimes;
        vector<int> primes;
        Solution() : primes(100001, -1)
        {
            vector<bool> table(100001, true);
            numPrimes = 0;
            for (int i = 2; i <= 100000; i++)
            {
                if (table[i])
                {
                    int j = i * 2;
                    while (j <= 100000)
                    {
                        table[j] = false;
                        j += i;
                    }
                    primes[i] = numPrimes++;
                }
            }
        }
        int largestComponentSize(vector<int>& A)
        {
            disjoint_set_union_find dsu(primes.size());
            for (int i = 0; i < A.size(); i++)
            {
                int n = A[i];
                if (n == 1)
                {
                    continue;
                }
                int square_root = (int)sqrt(n);
                int last = -1;
                // The biggest learning for this problem is that there are more primes than
                // square root of n, this is a faster way to find out all the prime factors
                for (int p = 1; p <= square_root; p++)
                {
                    if (n % p == 0)
                    {
                        int q = n / p;
                        if (primes[p] != -1)
                        {
                            if (last == -1)
                            {
                                last = primes[p];
                            }
                            else
                            {
                                dsu.union_sets(last, primes[p]);
                            }
                        }
                        if (primes[q] != -1)
                        {
                            if (last == -1)
                            {
                                last = primes[q];
                            }
                            else
                            {
                                dsu.union_sets(last, primes[q]);
                            }
                        }
                    }
                }
                dsu.increase_count(last);
            }
            int answer = 0;
            for (int i = 0; i < numPrimes; i++)
            {
                answer = max(dsu.get_count(i), answer);
            }
            return answer;
        }
    };
};

using namespace _LEET_LARGEST_COMPONENT_SIZE_BY_COMMON_FACTOR;

int LEET_LARGEST_COMPONENT_SIZE_BY_COMMON_FACTOR()
{
    Solution s;
    int test1_array[] = { 4,6,15,35 };
    int test2_array[] = { 20, 50, 9, 63 };
    int test3_array[] = { 2,3,6,7,4,12,21,39 };
    vector<int> test1(test1_array, test1_array + _countof(test1_array));
    vector<int> test2(test2_array, test2_array + _countof(test2_array));
    vector<int> test3(test3_array, test3_array + _countof(test3_array));
    cout << s.largestComponentSize(test1) << endl;
    cout << s.largestComponentSize(test2) << endl;
    cout << s.largestComponentSize(test3) << endl;
    return 0;
}