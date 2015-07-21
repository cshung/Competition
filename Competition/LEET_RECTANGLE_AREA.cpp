#include "stdafx.h"

// https://leetcode.com/problems/rectangle-area/

#include "LEET_RECTANGLE_AREA.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

namespace _LEET_RECTANGLE_AREA
{
    class Solution
    {
    private:
        // Do a simple line sweep
        int intersection_length(int p1, int p2, int q1, int q2)
        {
            // Step 1: Sorting
            int coord[4] = { p1, p2, q1, q2 };
            int event[4] = { 1, 1, 2, 2};
            for (int i = 0; i < 4; i++)
            {
                for (int j = i + 1; j < 4; j++)
                {
                    if (coord[j] < coord[i])
                    {
                        swap(coord[j], coord[i]);
                        swap(event[j], event[i]);
                    }
                }
            }
            bool inOne = false;
            bool inTwo = false;
            bool hasIntersection = false;
            int start = 0;
            int end = 0;
            for (int i = 0; i < 4; i++)
            {
                if (event[i] == 1) { inOne = !inOne; }
                if (event[i] == 2) { inTwo = !inTwo; }
                if (inOne && inTwo)
                {
                    hasIntersection = true;
                    start = coord[i];
                }
                else if (hasIntersection)
                {
                    end = coord[i];
                    break;
                }
            }
            if (hasIntersection)
            {
                return end - start;
            }
            else
            {
                return 0;
            }
        }

    public:
        int computeArea(int A, int B, int C, int D, int E, int F, int G, int H)
        {
            int x_intersection = this->intersection_length(A, C, E, G);
            int y_intersection = this->intersection_length(B, D, F, H);
            int rect1_size = (C - A) * (D - B);
            int rect2_size = (G - E) * (H - F);
            int intersect_size = x_intersection * y_intersection;

            return rect1_size + rect2_size - intersect_size;
        }
    };
};

using namespace _LEET_RECTANGLE_AREA;

int LEET_RECTANGLE_AREA()
{
    Solution solution;
    cout << solution.computeArea(-3,0,3,4,0,-1,9,2) << endl;
    return 0;
}