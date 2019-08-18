#include "stdafx.h"

// https://leetcode.com/problems/range-sum-query-2d-mutable/

#include "LEET_RANGE_SUM_QUERY_2D_MUTABLE.h"
#include <map>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_RANGE_SUM_QUERY_2D_MUTABLE
{
    struct rect
    {
        rect(int row1, int col1, int row2, int col2)
        {
            this->row1 = row1;
            this->col1 = col1;
            this->row2 = row2;
            this->col2 = col2;
        }

        int col1;
        int row1;
        int col2;
        int row2;
    };
    struct quad_tree
    {
        int sum;
        quad_tree* nw;
        quad_tree* ne;
        quad_tree* sw;
        quad_tree* se;
    };
    class NumMatrix
    {
    public:
        NumMatrix(vector<vector<int>>& matrix) : m_matrix(matrix), m_root(nullptr)
        {
            int height = matrix.size();
            if (height == 0)
            {
                return;
            }
            int width = matrix[0].size();
            if (width == 0)
            {
                return;
            }
            this->m_root = this->build_quad_tree(rect(0, 0, height, width));
        }

        void update(int row, int col, int val)
        {
            if (this->m_root == nullptr)
            {
                return;
            }
            int height = this->m_matrix.size();
            int width = this->m_matrix[0].size();
            int delta = val - this->m_matrix[row][col];
            this->update(this->m_root, rect(0, 0, height, width), row, col, delta);
            this->m_matrix[row][col] += delta;
        }

        void verify()
        {
            if (this->m_root == nullptr)
            {
                return;
            }
            int height = this->m_matrix.size();
            int width = this->m_matrix[0].size();
            this->verify(this->m_root, rect(0, 0, height, width));
        }

        int sumRegion(int row1, int col1, int row2, int col2)
        {
            if (this->m_root == nullptr)
            {
                return 0;
            }
            int height = this->m_matrix.size();
            int width = this->m_matrix[0].size();
            return this->sumRegion(this->m_root, rect(0, 0, height, width), rect(row1, col1, row2 + 1, col2 + 1));
        }
    private:
        vector<vector<int>>& m_matrix;
        quad_tree* m_root;

        void verify(quad_tree* node, rect box)
        {
            int height = box.row2 - box.row1;
            int width = box.col2 - box.col1;
            int rowMid = (box.row1 + box.row2) / 2;
            int colMid = (box.col1 + box.col2) / 2;
            int sum = 0;
            for (int row = box.row1; row < box.row2; row++)
            {
                for (int col = box.col1; col < box.col2; col++)
                {
                    sum += this->m_matrix[row][col];
                }
            }
            assert(node->sum == sum);

            if (width == 1 && height == 1)
            {
                
            }
            else if (width == 1 && height != 1)
            {
                rect nw(box.row1, box.col1, rowMid, box.col2);
                rect sw(rowMid, box.col1, box.row2, box.col2);
                this->verify(node->nw, nw);
                this->verify(node->sw, sw);
            }
            else if (width != 1 && height == 1)
            {
                rect nw(box.row1, box.col1, box.row2, colMid);
                rect ne(box.row1, colMid, box.row2, box.col2);
                this->verify(node->nw, nw);
                this->verify(node->ne, ne);
            }
            else
            {
                rect nw(box.row1, box.col1, rowMid, colMid);
                rect ne(box.row1, colMid, rowMid, box.col2);
                rect sw(rowMid, box.col1, box.row2, colMid);
                rect se(rowMid, colMid, box.row2, box.col2);
                this->verify(node->nw, nw);
                this->verify(node->ne, ne);
                this->verify(node->sw, sw);
                this->verify(node->se, se);
            }
        }

        int sumRegion(quad_tree* node, rect box, rect query)
        {
            int height = box.row2 - box.row1;
            int width = box.col2 - box.col1;
            int rowMid = (box.row1 + box.row2) / 2;
            int colMid = (box.col1 + box.col2) / 2;
            int answer = 0;
            if (box.col1 == query.col1 && box.col2 == query.col2 && box.row1 == query.row1 && box.row2 == query.row2)
            {
                return node->sum;
            }
            else if (width == 1 && height == 1)
            {
                answer += node->sum;
            }
            else if (width == 1 && height != 1)
            {
                rect nw(box.row1, box.col1, rowMid, box.col2);
                rect sw(rowMid, box.col1, box.row2, box.col2);
                rect intersection(0, 0, 0, 0);
                if (this->intersects(nw, query, intersection))
                {
                    answer += this->sumRegion(node->nw, nw, intersection);
                }
                if (this->intersects(sw, query, intersection))
                {
                    answer += this->sumRegion(node->sw, sw, intersection);
                }
            }
            else if (width != 1 && height == 1)
            {
                rect nw(box.row1, box.col1, box.row2, colMid);
                rect ne(box.row1, colMid, box.row2, box.col2);
                rect intersection(0, 0, 0, 0);
                if (this->intersects(nw, query, intersection))
                {
                    answer += this->sumRegion(node->nw, nw, intersection);
                }
                if (this->intersects(ne, query, intersection))
                {
                    answer += this->sumRegion(node->ne, ne, intersection);
                }
            }
            else
            {
                rect nw(box.row1, box.col1, rowMid, colMid);
                rect ne(box.row1, colMid, rowMid, box.col2);
                rect sw(rowMid, box.col1, box.row2, colMid);
                rect se(rowMid, colMid, box.row2, box.col2);
                rect intersection(0, 0, 0, 0);
                if (this->intersects(nw, query, intersection))
                {
                    answer += this->sumRegion(node->nw, nw, intersection);
                }
                if (this->intersects(ne, query, intersection))
                {
                    answer += this->sumRegion(node->ne, ne, intersection);
                }
                if (this->intersects(sw, query, intersection))
                {
                    answer += this->sumRegion(node->sw, sw, intersection);
                }
                if (this->intersects(se, query, intersection))
                {
                    answer += this->sumRegion(node->se, se, intersection);
                }
            }
            return answer;
        }

        void update(quad_tree* node, rect box, int row, int col, int delta)
        {
            int height = box.row2 - box.row1;
            int width = box.col2 - box.col1;
            int rowMid = (box.row1 + box.row2) / 2;
            int colMid = (box.col1 + box.col2) / 2;
            node->sum += delta;
            if (width == 1 && height == 1)
            {
                
            }
            else if (width == 1 && height != 1)
            {
                rect nw(box.row1, box.col1, rowMid, box.col2);
                rect sw(rowMid, box.col1, box.row2, box.col2);

                if (contains(nw, row, col))
                {
                    this->update(node->nw, nw, row, col, delta);
                }
                if (contains(sw, row, col))
                {
                    this->update(node->sw, sw, row, col, delta);
                }
            }
            else if (width != 1 && height == 1)
            {
                rect nw(box.row1, box.col1, box.row2, colMid);
                rect ne(box.row1, colMid, box.row2, box.col2);

                if (contains(nw, row, col))
                {
                    this->update(node->nw, nw, row, col, delta);
                }
                if (contains(ne, row, col))
                {
                    this->update(node->ne, ne, row, col, delta);
                }
            }
            else
            {
                rect nw(box.row1, box.col1, rowMid, colMid);
                rect ne(box.row1, colMid, rowMid, box.col2);
                rect sw(rowMid, box.col1, box.row2, colMid);
                rect se(rowMid, colMid, box.row2, box.col2);

                if (contains(nw, row, col))
                {
                    this->update(node->nw, nw, row, col, delta);
                }
                if (contains(ne, row, col))
                {
                    this->update(node->ne, ne, row, col, delta);
                }
                if (contains(sw, row, col))
                {
                    this->update(node->sw, sw, row, col, delta);
                }
                if (contains(se, row, col))
                {
                    this->update(node->se, se, row, col, delta);
                }
            }
        }

        bool contains(rect box, int row, int col)
        {
            return box.row1 <= row && row < box.row2 && box.col1 <= col && col < box.col2;
        }

        bool intersects(rect r1, rect r2, rect& result)
        {
            result.col1 = max(r1.col1, r2.col1);
            result.row1 = max(r1.row1, r2.row1);
            result.col2 = min(r1.col2, r2.col2);
            result.row2 = min(r1.row2, r2.row2);
            return result.col2 > result.col1&& result.row2 > result.row1;
        }

        quad_tree* build_quad_tree(rect box)
        {
            int height = box.row2 - box.row1;
            int width = box.col2 - box.col1;
            int rowMid = (box.row1 + box.row2) / 2;
            int colMid = (box.col1 + box.col2) / 2;
            quad_tree* result = new quad_tree();
            if (width == 1 && height == 1)
            {
                result->sum = this->m_matrix[box.row1][box.col1];
            }
            else if (width == 1 && height != 1)
            {
                rect nw(box.row1, box.col1, rowMid, box.col2);
                rect sw(rowMid, box.col1, box.row2, box.col2);
                result->nw = build_quad_tree(nw);
                result->sw = build_quad_tree(sw);
                result->sum = result->nw->sum + result->sw->sum;
            }
            else if (width != 1 && height == 1)
            {
                rect nw(box.row1, box.col1, box.row2, colMid);
                rect ne(box.row1, colMid, box.row2, box.col2);
                result->nw = build_quad_tree(nw);
                result->ne = build_quad_tree(ne);
                result->sum = result->nw->sum + result->ne->sum;
            }
            else
            {
                rect nw(box.row1, box.col1, rowMid, colMid);
                rect ne(box.row1, colMid, rowMid, box.col2);
                rect sw(rowMid, box.col1, box.row2, colMid);
                rect se(rowMid, colMid, box.row2, box.col2);
                result->nw = build_quad_tree(nw);
                result->ne = build_quad_tree(ne);
                result->sw = build_quad_tree(sw);
                result->se = build_quad_tree(se);
                result->sum = result->nw->sum + result->ne->sum + result->sw->sum + result->se->sum;
            }
            return result;
        }
    };
};

using namespace _LEET_RANGE_SUM_QUERY_2D_MUTABLE;

int LEET_RANGE_SUM_QUERY_2D_MUTABLE()
{
    int row1[] = { 3, 0, 1, 4, 2 };
    int row2[] = { 5, 6, 3, 2, 1 };
    int row3[] = { 1, 2, 0, 1, 5 };
    int row4[] = { 4, 1, 0, 1, 7 };
    int row5[] = { 1, 0, 3, 0, 5 };
    vector<vector<int>> nums;
    nums.push_back(vector<int>(row1, row1 + _countof(row1)));
    nums.push_back(vector<int>(row2, row2 + _countof(row2)));
    nums.push_back(vector<int>(row3, row3 + _countof(row3)));
    nums.push_back(vector<int>(row4, row4 + _countof(row4)));
    nums.push_back(vector<int>(row5, row5 + _countof(row5)));
    NumMatrix n(nums);
    n.verify();
    cout << (n.sumRegion(2, 1, 4, 3) == 8) << endl;
    n.verify();
    n.update(3, 2, 2);
    n.verify();
    cout << (n.sumRegion(2, 1, 4, 3) == 10) << endl;
    n.verify();
    return 0;
}
