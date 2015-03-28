#include "stdafx.h"

// https://leetcode.com/problems/majority-element/

#include "LEET_MAJORITY_ELEMENT.h"
#include <map>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

namespace _LEET_MAJORITY_ELEMENT
{
    class Solution {
    public:
        int majorityElement(vector<int> &num) {
            sort(num.begin(), num.end());
            return num[num.size() / 2];
        }
    };
};

using namespace _LEET_MAJORITY_ELEMENT;

int LEET_MAJORITY_ELEMENT()
{
    vector<int> odd;
    odd.push_back(1);
    odd.push_back(2);
    odd.push_back(1);
    
    vector<int> even;
    even.push_back(1);
    even.push_back(2);
    even.push_back(1);
    even.push_back(1);
    Solution solution;
    cout << solution.majorityElement(odd) << endl;
    cout << solution.majorityElement(even) << endl;
    return 0;
}
