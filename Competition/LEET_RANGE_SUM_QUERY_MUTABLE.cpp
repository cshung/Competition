#include "stdafx.h"

// https://leetcode.com/problems/range-sum-query-mutable/

#include "LEET_RANGE_SUM_QUERY_MUTABLE.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_RANGE_SUM_QUERY_MUTABLE
{
    class NumArray
    {
        struct SegmentTreeNode
        {
            int sum;
            SegmentTreeNode* left;
            SegmentTreeNode* right;
        };

        vector<int>& m_nums;
        SegmentTreeNode* m_root;

        SegmentTreeNode* build_segment_tree(int lower, int upper)
        {
            SegmentTreeNode* result = new SegmentTreeNode();
            if (upper - lower == 1)
            {
                result->sum = this->m_nums[lower];
                result->left = NULL;
                result->right = NULL;
            }
            else
            {
                int mid = (lower + upper) / 2;
                result->left = build_segment_tree(lower, mid);
                result->right = build_segment_tree(mid, upper);
                result->sum = result->left->sum + result->right->sum;
            }

            return result;
        }

        int get_sum(SegmentTreeNode* node, int treeLower, int treeUpper, int queryLower, int queryUpper)
        {
            // case 1: query range match exactly the node range, just return the sum
            if (queryLower <= treeLower && queryUpper >= treeUpper)
            {
                return node->sum;
            }

            int treeMid = (treeLower + treeUpper) / 2;
            int result = 0;
            if (queryLower < treeMid)
            {
                result += get_sum(node->left, treeLower, treeMid, queryLower, queryUpper);
            }
            if (queryUpper > treeMid)
            {
                result += get_sum(node->right, treeMid, treeUpper, queryLower, queryUpper);
            }
            return result;
        }

        void update_tree(SegmentTreeNode* node, int lower, int upper, int index, int delta)
        {
            node->sum += delta;
            if (upper - lower != 1)
            {
                int mid = (lower + upper) / 2;
                if (index < mid)
                {
                    update_tree(node->left, lower, mid, index, delta);
                }
                else
                {
                    update_tree(node->right, mid, upper, index, delta);
                }
            }
        }
    public:
        NumArray(vector<int>& nums) : m_nums(nums), m_root(NULL)
        {
            if (nums.size() > 0)
            {
                m_root = build_segment_tree(0, nums.size());
            }
        }

        ~NumArray()
        {
            if (this->m_root != NULL)
            {
                delete this->m_root;
            }
        }

        void update(int i, int val)
        {
            int delta = val - m_nums[i];
            m_nums[i] = val;
            return update_tree(this->m_root, 0, this->m_nums.size(), i, delta);
        }

        int sumRange(int i, int j)
        {
            // j + 1 so that we follow convention [)
            return get_sum(this->m_root, 0, this->m_nums.size(), i, j + 1);
        }
    };
};

using namespace _LEET_RANGE_SUM_QUERY_MUTABLE;

int LEET_RANGE_SUM_QUERY_MUTABLE()
{
    int dataArray[] = { 7, 2, 7, 2, 0 };
    vector<int> data(dataArray, dataArray + _countof(dataArray));
    NumArray nums(data);
    nums.update(4, 6);
    nums.update(0, 2);
    nums.update(0, 9);
    cout << (nums.sumRange(4, 4) == 6) << endl;
    nums.update(3, 8);
    cout << (nums.sumRange(0, 4) == 32) << endl;
    nums.update(4, 1);
    cout << (nums.sumRange(0, 3) == 26) << endl;
    cout << (nums.sumRange(0, 4) == 27) << endl;
    return 0;
} 