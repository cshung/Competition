#include "stdafx.h"

// https://leetcode.com/contest/2/problems/perfect-rectangle/

#include "LEET_PERFECT_RECTANGLE.h"
#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_PERFECT_RECTANGLE
{
    struct Range
    {
        Range(int from, int to)
        {
            this->from = from;
            this->to = to;
        }
        int from;
        int to;
    };

    class Ranges
    {
    public:
        Ranges(int from, int to)
        {
            Range* range = new Range(from, to);
            fromIndex.insert(make_pair(from, range));
            toIndex.insert(make_pair(to, range));
        }

        void add_range(int from, int to)
        {
            auto leftFind = toIndex.find(from);
            auto rightFind = fromIndex.find(to);
            if (leftFind != toIndex.end())
            {
                Range* leftRange = leftFind->second;
                fromIndex.erase(leftRange->from);
                toIndex.erase(leftRange->to);
                from = leftRange->from;
                delete leftRange;
            }
            if (rightFind != fromIndex.end())
            {
                Range* rightRange = rightFind->second;
                fromIndex.erase(rightRange->from);
                toIndex.erase(rightRange->to);
                to = rightRange->to;
                delete rightRange;
            }

            Range* range = new Range(from, to);
            fromIndex.insert(make_pair(from, range));
            toIndex.insert(make_pair(to, range));
        }

        unordered_map<int, Range*> fromIndex;
        unordered_map<int, Range*> toIndex;

    };

    void AddEdge(unordered_map<int, Ranges*>& allRanges, int key, int from, int to)
    {
        auto iter = allRanges.find(key);
        if (iter == allRanges.end())
        {
            Ranges* ranges = new Ranges(from, to);
            allRanges.insert(make_pair(key, ranges));
        }
        else
        {
            Ranges* ranges = iter->second;
            ranges->add_range(from, to);
        }
    }

    class Solution
    {
    public:
        int area(vector<int>& rectangle)
        {
            return (rectangle[2] - rectangle[0]) * (rectangle[3] - rectangle[1]);
        }
        bool isRectangleCover(vector<vector<int>>& rectangles)
        {
            int total_area = 0;
            int min_x = rectangles[0][0];
            int min_y = rectangles[0][1];
            int max_x = rectangles[0][2];
            int max_y = rectangles[0][3];
            for (size_t i = 0; i < rectangles.size(); i++)
            {
                total_area += area(rectangles[i]);
                min_x = min(min_x, rectangles[i][0]);
                min_y = min(min_y, rectangles[i][1]);
                max_x = max(max_x, rectangles[i][2]);
                max_y = max(max_y, rectangles[i][3]);
            }
            int expected_area = (max_x - min_x) * (max_y - min_y);
            if (total_area != expected_area)
            {
                return false;
            }
            
            unordered_map<int, Ranges*> topEdges;
            unordered_map<int, Ranges*> bottomEdges;
            unordered_map<int, Ranges*> leftEdges;
            unordered_map<int, Ranges*> rightEdges;

            // Imagine the min box is actually adjacent to four big boxes (so all edges have their 'other' sides)
            topEdges.insert(make_pair(min_y, new Ranges(min_x, max_x)));
            bottomEdges.insert(make_pair(max_y, new Ranges(min_x, max_x)));
            rightEdges.insert(make_pair(min_x, new Ranges(min_y, max_y)));
            leftEdges.insert(make_pair(max_x, new Ranges(min_y, max_y)));

            for (size_t i = 0; i < rectangles.size(); i++)
            {
                int x1 = rectangles[i][0];
                int y1 = rectangles[i][1];
                int x2 = rectangles[i][2];
                int y2 = rectangles[i][3];
                AddEdge(topEdges, y2, x1, x2);
                AddEdge(bottomEdges, y1, x1, x2);
                AddEdge(leftEdges, x1, y1, y2);
                AddEdge(rightEdges, x2, y1, y2);
            }

            for (auto topEdgeKeyValuePair : topEdges)
            {
                auto topEdgeKey = topEdgeKeyValuePair.first;
                
                auto bottomEdgeIter = bottomEdges.find(topEdgeKey);
                if (bottomEdgeIter == bottomEdges.end())
                {
                    return false;
                }

                auto topEdgeRanges = topEdgeKeyValuePair.second;
                auto bottomEdgeRanges = bottomEdgeIter->second;

                if (topEdgeRanges->fromIndex.size() != bottomEdgeRanges->fromIndex.size())
                {
                    return false;
                }

                for (auto topEdgeRangeKeyValuePair : topEdgeRanges->fromIndex)
                {
                    auto& topEdgeRange = topEdgeRangeKeyValuePair.second;

                    auto bottomEdgeRange = bottomEdgeRanges->fromIndex.find(topEdgeRange->from);
                    if (bottomEdgeRange == bottomEdgeRanges->fromIndex.end())
                    {
                        return false;
                    }
                    else if (bottomEdgeRange->second->to != topEdgeRange->to)
                    {
                        return false;
                    }
                }
            }
            for (auto rightEdgeKeyValuePair : rightEdges)
            {
                auto rightEdgeKey = rightEdgeKeyValuePair.first;

                auto leftEdgeIter = leftEdges.find(rightEdgeKey);
                if (leftEdgeIter == leftEdges.end())
                {
                    return false;
                }

                auto rightEdgeRanges = rightEdgeKeyValuePair.second;
                auto leftEdgeRanges = leftEdgeIter->second;

                if (rightEdgeRanges->fromIndex.size() != leftEdgeRanges->fromIndex.size())
                {
                    return false;
                }

                for (auto rightEdgeRangeKeyValuePair : rightEdgeRanges->fromIndex)
                {
                    auto& rightEdgeRange = rightEdgeRangeKeyValuePair.second;

                    auto leftEdgeRange = leftEdgeRanges->fromIndex.find(rightEdgeRange->from);
                    if (leftEdgeRange == leftEdgeRanges->fromIndex.end())
                    {
                        return false;
                    }
                    else if (leftEdgeRange->second->to != rightEdgeRange->to)
                    {
                        return false;
                    }
                }
            }
            return true;
        }
    };
};

using namespace _LEET_PERFECT_RECTANGLE;

int LEET_PERFECT_RECTANGLE()
{
    // Better, but now the judge bitches on memory consumption
    // After all I am using linear memory, maybe we can get there with compact encoding
    Solution solution;
    int r[5][4] = { {1, 1, 3, 3},{3, 1, 4, 2},{3, 2, 4, 4},{1, 3, 2, 4},{2, 3, 3, 4} };
    vector<vector<int>> rectangles;
    rectangles.push_back(vector<int>(r[0], r[0] + 4));
    rectangles.push_back(vector<int>(r[1], r[1] + 4));
    rectangles.push_back(vector<int>(r[2], r[2] + 4));
    rectangles.push_back(vector<int>(r[3], r[3] + 4));
    rectangles.push_back(vector<int>(r[4], r[4] + 4));
    cout << solution.isRectangleCover(rectangles) << endl;
    return 0;
}
