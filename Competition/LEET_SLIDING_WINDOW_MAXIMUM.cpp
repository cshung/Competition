#include "stdafx.h"

// https://leetcode.com/problems/climbing-stairs/

#include "LEET_SLIDING_WINDOW_MAXIMUM.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

namespace _LEET_SLIDING_WINDOW_MAXIMUM
{
    class Solution
    {
    private:
        vector<int> max_queues_val;
        vector<int> max_queues_max;
        int size;
        int stack1_top;
        int stack2_top;

        void initialize_queues(int size)
        {
            this->size = size;
            this->stack1_top = 0;
            this->stack2_top = size - 1;
            this->max_queues_max.resize(size);
            this->max_queues_val.resize(size);
        }

        void enqueue(int val)
        {
            push1(val);
        }

        int queue_max()
        {
            if (this->size1() == 0)
            {
                return this->max2();
            }
            else if (this->size2() == 0)
            {
                return this->max1();
            }
            else
            {
                return max(this->max1(), this->max2());
            }
        }

        int dequeue()
        {
            if (this->size2() == 0)
            {
                while (this->size1() > 0)
                {
                    this->push2(this->pop1());
                }
            }
            return this->pop2();
        }

        int size1()
        {
            return this->stack1_top;
        }

        void push1(int val)
        {
            this->max_queues_val[this->stack1_top] = val;
            if (this->stack1_top == 0)
            {
                this->max_queues_max[this->stack1_top] = val;
            }
            else
            {
                this->max_queues_max[this->stack1_top] = max(val, max1());
            }
            this->stack1_top++;
        }

        int pop1()
        {
            this->stack1_top--;
            return this->max_queues_val[this->stack1_top];
        }

        int max1()
        {
            return this->max_queues_max[this->stack1_top - 1];
        }

        int size2()
        {
            return this->size - 1 - this->stack2_top;
        }

        void push2(int val)
        {
            this->max_queues_val[this->stack2_top] = val;
            if (this->stack2_top == this->size - 1)
            {
                this->max_queues_max[this->stack2_top] = val;
            }
            else
            {
                this->max_queues_max[this->stack2_top] = max(val, max2());
            }
            this->stack2_top--;
        }

        int pop2()
        {
            this->stack2_top++;
            return this->max_queues_val[this->stack2_top];
        }

        int max2()
        {
            return this->max_queues_max[this->stack2_top + 1];
        }

    public:
        vector<int> maxSlidingWindow(vector<int>& nums, int k)
        {
            vector<int> result;
            if (nums.size() == 0)
            {
                return result;
            }
            initialize_queues(k);
            for (int i = 0; i < k; i++)
            {
                this->enqueue(nums[i]);
            }

            for (unsigned int i = k; i < nums.size(); i++)
            {
                result.push_back(this->queue_max());
                this->dequeue();
                this->enqueue(nums[i]);
            }
            result.push_back(this->queue_max());
            return result;
        }
    };
};

using namespace _LEET_SLIDING_WINDOW_MAXIMUM;

int LEET_SLIDING_WINDOW_MAXIMUM()
{
    Solution solution;
    int case1[] = { 1,3,-1,-3,5,3,6,7 };
    vector<int> case1_result = solution.maxSlidingWindow(vector<int>(case1, case1 + _countof(case1)), 3);
    for (unsigned int i = 0; i < case1_result.size(); i++) { cout << case1_result[i] << ", "; } cout << endl;
    return 0;
}