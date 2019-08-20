#include "stdafx.h"

// https://leetcode.com/problems/two-sum-iii-data-structure-design/

#include "LEET_TWO_SUM_III_DATA_STRUCTURE_DESIGN.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_TWO_SUM_III_DATA_STRUCTURE_DESIGN
{
    class TwoSum
    {
    public:
        TwoSum()
        {

        }

        void add(int number)
        {
            numbers.push_back(number);
        }

        bool find(int value)
        {
            map<int, unsigned int> previous;
            for (unsigned int i = 0; i < numbers.size(); i++)
            {
                if (i == 0)
                {
                    previous.insert(pair<int, unsigned int>(numbers[i], i));
                }
                else
                {
                    map<int, unsigned int>::iterator probe = previous.find(value - numbers[i]);
                    if (probe != previous.end())
                    {
                        return true;
                    }
                    else
                    {
                        previous.insert(pair<int, unsigned int>(numbers[i], i));
                    }
                }
            }
            return false;
        }
    private:
        vector<int> numbers;
    };
};

using namespace _LEET_TWO_SUM_III_DATA_STRUCTURE_DESIGN;

int LEET_TWO_SUM_III_DATA_STRUCTURE_DESIGN()
{
    TwoSum solution;
    solution.add(1);
    solution.add(3);
    solution.add(5);
    cout << solution.find(4) << endl;
    cout << solution.find(7) << endl;
    return 0;
}