#include "stdafx.h"

// https://leetcode.com/problems/asteroid-collision/

#include "LEET_ASTEROID_COLLISION.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <stack>

using namespace std;

namespace _LEET_ASTEROID_COLLISION
{
    class Solution
    {
    public:
        vector<int> asteroidCollision(vector<int>& asteroids)
        {
            stack<int> s;
            for (int i = 0; i < asteroids.size(); i++)
            {
                while (true)
                {
                    if (s.size() == 0)
                    {
                        s.push(asteroids[i]);
                        break;
                    }
                    else
                    {
                        int t = s.top();
                        if (asteroids[i] < 0 && t > 0)
                        {
                            int size1 = -asteroids[i];
                            int size2 = t;
                            if (size1 == size2)
                            {
                                s.pop();
                                break;
                            }
                            else if (size1 > size2)
                            {
                                s.pop();
                            }
                            else
                            {
                                break;
                            }
                        }
                        else
                        {
                            s.push(asteroids[i]);
                            break;
                        }
                    }
                }
            }
            vector<int> result(s.size());
            while (s.size() > 0)
            {
                result[s.size() - 1] = s.top();
                s.pop();
            }
            return result;
        }
    };
};

using namespace _LEET_ASTEROID_COLLISION;

int LEET_ASTEROID_COLLISION()
{
    Solution solution;
    int test_array[] = { 5, 10, -5 };
    vector<int> test(test_array, test_array + _countof(test_array));
    vector<int> answers = solution.asteroidCollision(test);
    for (int answer : answers)
    {
        cout << answer << " ";
    }
    cout << endl;
    return 0;
}