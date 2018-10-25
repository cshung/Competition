#include "stdafx.h"

// https://leetcode.com/problems/minimum-cost-to-hire-k-workers

#include "LEET_MINIMUM_COST_TO_HIRE_K_WORKERS.h"
#include <map>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cassert>

using namespace std;

namespace _LEET_MINIMUM_COST_TO_HIRE_K_WORKERS
{
    class Solution
    {
    public:
        double mincostToHireWorkers(vector<int>& quality, vector<int>& wage, int K)
        {
            int n = quality.size();

            assert(wage.size() == n);
            assert(K <= n);
            assert(K >= 1);

            // A worker is simply represented as its index in the quality array
            vector<int> workers;
            vector<double> wage_per_worker;
            workers.resize(n);
            wage_per_worker.resize(n);
            for (int i = 0; i < n; i++)
            {
                workers[i] = i;
                wage_per_worker[i] = (wage[i] + 0.0) / quality[i];
            }

            // Step 1: Sort them with increasing wage per quality
            sort(workers.begin(), workers.end(), [&](int a, int b) {return wage_per_worker[a] < wage_per_worker[b]; });

            vector<int> low_quality_workers;
            low_quality_workers.resize(K);
            int low_quality_workers_size = 0;
            int quality_sum = 0;

            // Step 2: Prepare a max quality priority queue for that we can keep the workers with lowest quality
            for (int i = 0; i < K; i++)
            {
                heap_insert(low_quality_workers, low_quality_workers_size, quality_sum, quality, workers[i]);
            }
            double best = ((wage[workers[K - 1]] + 0.0) / quality[workers[K - 1]]) * quality_sum;

            // Step 3: Consider higher wage per quality and pick the ones with lowest quality to try
            for (int i = K; i < n; i++)
            {
                heap_delete_max(low_quality_workers, low_quality_workers_size, quality_sum, quality);
                heap_insert(low_quality_workers, low_quality_workers_size, quality_sum, quality, workers[i]);
                double candidate = wage_per_worker[workers[i]] * quality_sum;
                best = min(best, candidate);
            }

            return best;
        }

        void heap_insert(vector<int>& low_quality_workers, int& low_quality_workers_size, int& quality_sum, vector<int>& quality, int worker)
        {
            // Step 1: Add it at the end of the array
            low_quality_workers[low_quality_workers_size++] = worker;
            quality_sum += quality[worker];

            // Step 2: Bubble up
            int bubble_index = low_quality_workers_size - 1;
            while (true)
            {
                if (bubble_index == 0)
                {
                    break;
                }
                int parent_index = (bubble_index + 1) / 2 - 1;
                int bubble_worker = low_quality_workers[bubble_index];
                int parent_worker = low_quality_workers[parent_index];
                int bubble_quality = quality[bubble_worker];
                int parent_quality = quality[parent_worker];
                if (bubble_quality < parent_quality)
                {
                    // TODO: Think, what shall we do if we get a tie in quality?
                    break;
                }
                else
                {
                    swap(low_quality_workers[bubble_index], low_quality_workers[parent_index]);
                    bubble_index = parent_index;
                }
            }
        }
    
        void heap_delete_max(vector<int>& low_quality_workers, int& low_quality_workers_size, int& quality_sum, vector<int>& quality)
        {
            quality_sum -= quality[low_quality_workers[0]];
            low_quality_workers[0] = low_quality_workers[--low_quality_workers_size];
            int stone_index = 0;
            while (true)
            {
                int left = (stone_index + 1) * 2 - 1;
                int right = left + 1;
                int stone_worker = low_quality_workers[stone_index];
                int stone_quality = quality[stone_worker];
                if (right < low_quality_workers_size)
                {
                    int left_worker = low_quality_workers[left];
                    int left_quality = quality[left_worker];
                    int right_worker = low_quality_workers[right];
                    int right_quality = quality[right_worker];
                    if (right_quality < left_quality)
                    {
                        if (stone_quality < left_quality)
                        {
                            swap(low_quality_workers[left], low_quality_workers[stone_index]);
                            stone_index = left;
                        }
                        else
                        {
                            break;
                        }
                    }
                    else
                    {
                        if (stone_quality < right_quality)
                        {
                            swap(low_quality_workers[right], low_quality_workers[stone_index]);
                            stone_index = right;
                        }
                        else
                        {
                            break;
                        }
                    }
                }
                else if (left < low_quality_workers_size)
                {
                    int left_worker = low_quality_workers[left];
                    int left_quality = quality[left_worker];
                    if (stone_quality < left_quality)
                    {
                        swap(low_quality_workers[left], low_quality_workers[stone_index]);
                        stone_index = left;
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
        }
    };
};

using namespace _LEET_MINIMUM_COST_TO_HIRE_K_WORKERS;

int LEET_MINIMUM_COST_TO_HIRE_K_WORKERS()
{
    Solution solution;
    int qual1[] = { 10,20,5 };
    int wage1[] = { 70,50,30 };
    int qual2[] = { 3,1,10,10,1 };
    int wage2[] = { 4,8,2,2,7 };
    int qual3[] = { 4, 4, 4, 5 };
    int wage3[] = { 13, 12, 13, 12 };
    int qual4[] = { 14, 56, 59, 89, 39, 26, 86, 76, 3, 36 };
    int wage4[] = { 90, 217, 301, 202, 294, 445, 473, 245, 415, 487 };
    int qual5[] = { 37, 32, 14, 14, 23, 31, 82, 96, 81, 96, 22, 17, 68, 3, 88, 59, 54, 23, 22, 77, 61, 16, 46, 22, 94, 50, 29, 46, 7, 33, 22, 99, 31, 99, 75, 67, 95, 54, 31, 48, 44, 96, 99, 20, 51, 54, 18, 85, 25, 84 };
    int wage5[] = { 453, 236, 199, 359, 107, 45, 150, 433, 32, 192, 433, 94, 113, 200, 293, 31, 48, 27, 15, 32, 295, 97, 199, 427, 90, 215, 390, 412, 475, 131, 122, 398, 479, 142, 103, 243, 86, 309, 498, 210, 173, 363, 449, 135, 353, 397, 105, 165, 165, 62 };
    
    cout << solution.mincostToHireWorkers(vector<int>(qual1, qual1 + _countof(qual1)), vector<int>(wage1, wage1 + _countof(wage1)), 2) << endl;
    cout << solution.mincostToHireWorkers(vector<int>(qual2, qual2 + _countof(qual2)), vector<int>(wage2, wage2 + _countof(wage2)), 3) << endl;
    cout << solution.mincostToHireWorkers(vector<int>(qual3, qual3 + _countof(qual3)), vector<int>(wage3, wage3 + _countof(wage3)), 2) << endl;
    cout << solution.mincostToHireWorkers(vector<int>(qual4, qual4 + _countof(qual4)), vector<int>(wage4, wage4 + _countof(wage4)), 2) << endl;
    cout << solution.mincostToHireWorkers(vector<int>(qual5, qual5 + _countof(qual5)), vector<int>(wage5, wage5 + _countof(wage5)), 20) << endl;
    return 0;
}
