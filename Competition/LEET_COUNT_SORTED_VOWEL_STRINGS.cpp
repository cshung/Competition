#include "stdafx.h"

// https://leetcode.com/problems/count-sorted-vowel-strings/

#include "LEET_COUNT_SORTED_VOWEL_STRINGS.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_COUNT_SORTED_VOWEL_STRINGS
{
    /*
     * My solution:
     * ============
     * Define A(n) to be the number of sorted string starting with 'a', E(n) to be the number of sorted string starting with 'e', and so on
     * We have the matrix equation:
     * 
     * / 1 1 1 1 1 \ A(n)   A(n+1)
     * | 0 1 1 1 1 | E(n)   E(n+1)
     * | 0 0 1 1 1 | I(n) = I(n+1)
     * | 0 0 0 1 1 | O(n)   O(n+1)
     * \ 0 0 0 0 1 / U(n)   U(n+1)
     * 
     * Therefore we can use matrix power to solve this problem.
     * 
     * The matrix is not diagonalizable, it has a Jordan canonical form. Using the Jordan canonical form, I derived that the solution is a 
     * 4th degree polynomial, we could either use that, our use interpolation to find a 4th degree polynomial. 
     * 
     * Community solution:
     * ===================
     * We can consider the problem as placing four bars in n + 4 slots, and therefore the answer is C(n + 4, 4).
     */
    class Solution
    {
    public:
        int countVowelStrings(int n)
        {
            return (n + 1) * (n + 2) * (n + 3) * (n + 4) / 24;
        }
    };
};

using namespace _LEET_COUNT_SORTED_VOWEL_STRINGS;

int LEET_COUNT_SORTED_VOWEL_STRINGS()
{
    Solution solution;
    for (int i = 1; i <= 50; i++)
    {
        cout << solution.countVowelStrings(i) << endl;
    }
    return 0;
}