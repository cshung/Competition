#include "stdafx.h"

// https://leetcode.com/problems/distribute-candies-to-people/

#include "LEET_DISTRIBUTE_CANDIES_TO_PEOPLE.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_DISTRIBUTE_CANDIES_TO_PEOPLE
{
    class Solution
    {
    public:
        vector<int> distributeCandies(int candies, int num_people)
        {
            vector<int> answer(num_people);
            int k = (int)(sqrt(2 * candies + 0.25) - 0.5);
            int round = k / num_people;
            int extra = k % num_people;
            for (int i = 0; i < num_people; i++)
            {
                int my_round = round + (i < extra ? 1 : 0);
                answer[i] = (2 * (i + 1) + (my_round - 1) * num_people) * my_round / 2;
            }
            answer[extra] += candies - (k * (k + 1) / 2);
            return answer;
        }
    };
};

using namespace _LEET_DISTRIBUTE_CANDIES_TO_PEOPLE;

int LEET_DISTRIBUTE_CANDIES_TO_PEOPLE()
{
    Solution solution;
    auto result = solution.distributeCandies(7, 4);
    for (auto entry : result)
    {
        cout << entry << " ";
    }
    cout << endl;
    return 0;
}