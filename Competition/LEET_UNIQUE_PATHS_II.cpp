#include "stdafx.h"

// https://leetcode.com/problems/unique-paths-ii/

#include "LEET_UNIQUE_PATHS_II.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_UNIQUE_PATHS_II
{
    class Solution {
    public:
        int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid)
        {
            int height = obstacleGrid.size();
            if (height > 0)
            {
                int width = obstacleGrid[0].size();
                if (width > 0)
                {
                    vector<vector<int>> answer;
                    answer.resize(height);
                    for (int h = 0; h < height; h++)
                    {
                        answer[h].resize(width);
                    }
                    for (int h = 0; h < height; h++)
                    {
                        for (int w = 0; w < width; w++)
                        {
                            if (obstacleGrid[h][w] == 1)
                            {
                                answer[h][w] = 0;
                            }
                            else
                            {
                                int above = h == 0 ? 0 : answer[h - 1][w];
                                int left = w == 0 ? 0 : answer[h][w - 1];
                                int bonus = (h == 0 && w == 0) ? 1 : 0;
                                answer[h][w] = above + left + bonus;
                            }
                        }
                    }
                    return answer[height - 1][width - 1];
                }
            }
            return 0;
        }
    };
};

using namespace _LEET_UNIQUE_PATHS_II;

int LEET_UNIQUE_PATHS_II()
{
    Solution solution;
    vector<vector<int>> obstacleGrid;
    obstacleGrid.resize(3);
    obstacleGrid[0].push_back(0);
    obstacleGrid[0].push_back(0);
    obstacleGrid[0].push_back(0);
    obstacleGrid[1].push_back(0);
    obstacleGrid[1].push_back(1);
    obstacleGrid[1].push_back(0);
    obstacleGrid[2].push_back(0);
    obstacleGrid[2].push_back(0);
    obstacleGrid[2].push_back(0);
    cout << solution.uniquePathsWithObstacles(obstacleGrid) << endl;
    return 0;
}