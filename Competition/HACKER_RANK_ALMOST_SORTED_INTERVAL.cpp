#include "stdafx.h"

// https://www.hackerrank.com/challenges/almost-sorted-interval

#include "HACKER_RANK_ALMOST_SORTED_INTERVAL.h"
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

namespace _HACKER_RANK_ALMOST_SORTED_INTERVAL
{
    int set_union(int set1, int set2, int* set)
    {
        int size1 = -set[set1];
        int size2 = -set[set2];
        int size = size1 + size2;
        if (size1 > size2)
        {
            set[set2] = set1;
            set[set1] = -size;
			return set1;
        }
        else
        {
            set[set1] = set2;
            set[set2] = -size;
			return set2;
        }
    }

    int set_find(int x, int* set)
    {
        if (set[x] < 0)
        {
            return x;
        }
        else
        {
            return (set[x] = set_find(set[x], set));
        }
    }

    int HACKER_RANK_ALMOST_SORTED_INTERVAL()
    {
        int n;
        cin >> n;
        int* input = new int[n];

        int min_stack_size = 0;
        int max_stack_size = 0;
        int* min_stack_elements = new int[n];
        int* max_stack_elements = new int[n];

        int* min_stack_node_set = new int[n + 1];
        int* min_stack_node_pos = new int[n + 1];

        long long result = 0;

        for (int i = 0; i < n; i++)
        {
            cin >> input[i];
        }

        for (int i = 0; i < n + 1; i++)
        {
            min_stack_node_set[i] = -1;
			min_stack_node_pos[i] = -1;
        }
        
        for (int current_position = 0; current_position < n; current_position++)
        {
            int current_value = input[current_position];
            int old_min_stack_size = min_stack_size;
            while (min_stack_size > 0 && input[min_stack_elements[min_stack_size - 1]] > current_value)
            {
                min_stack_size--;
            }
            for (int i = min_stack_size; i < old_min_stack_size; i++)
            {
                int canon = min_stack_size == 0 ? n : min_stack_elements[min_stack_size - 1];
				int left = set_find(canon, min_stack_node_set);
				int right = set_find(min_stack_elements[i], min_stack_node_set);
                int merge = set_union(left, right, min_stack_node_set);
				min_stack_node_pos[merge] = min_stack_node_pos[left];
            }
            while (max_stack_size > 0 && input[max_stack_elements[max_stack_size - 1]] < current_value)
            {
                max_stack_size--;
            }
            min_stack_elements[min_stack_size++] = current_position;
            max_stack_elements[max_stack_size++] = current_position;

            min_stack_node_pos[current_position] = min_stack_size - 1;

            if (max_stack_size == 1)
            {
                result += min_stack_size;
            }
            else
            {
                int after_position = max_stack_elements[max_stack_size - 2];
                int min_node_at_of_before_after_position = set_find(after_position, min_stack_node_set);
                result += min_stack_size - min_stack_node_pos[min_node_at_of_before_after_position] - 1;
            }
        }

		cout << result << endl;
        delete[] input;

        return 0;
    }
}

using namespace _HACKER_RANK_ALMOST_SORTED_INTERVAL;

int HACKER_RANK_ALMOST_SORTED_INTERVAL()
{
    return _HACKER_RANK_ALMOST_SORTED_INTERVAL::HACKER_RANK_ALMOST_SORTED_INTERVAL();
}
