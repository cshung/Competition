#include "stdafx.h"

// https://leetcode.com/problems/number-of-subarrays-with-bounded-maximum

#include "LEET_NUMBER_OF_SUBARRAYS_WITH_BOUNDED_MAXIMUM.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_NUMBER_OF_SUBARRAYS_WITH_BOUNDED_MAXIMUM
{
    struct Result
    {
        int size;
        int answer;
    };

    class Solution {
    public:
        int numSubarrayBoundedMax(vector<int>& arr, int L, int R) {
            size_t n = arr.size();
            // Arrays to hold the index of parent, left-child,
            // right-child of each number in the input array
            vector<int> parent; parent.resize(arr.size());
            vector<int> leftchild; leftchild.resize(arr.size());
            vector<int> rightchild; rightchild.resize(arr.size());

            // Initialize all array values as -1
            for (int i = 0; i < arr.size(); i++)
            {
                parent[i] = -1;
                leftchild[i] = -1;
                rightchild[i] = -1;
            }

            // 'root' and 'last' stores the index of the root and the
            // last processed of the Cartesian Tree.
            // Initially we take root of the Cartesian Tree as the
            // first element of the input array. This can change
            // according to the algorithm
            int root = 0, last;

            // Starting from the second element of the input array
            // to the last on scan across the elements, adding them
            // one at a time.
            for (int i = 1; i <= n - 1; i++)
            {
                last = i - 1;
                rightchild[i] = -1;

                // Scan upward from the node's parent up to
                // the root of the tree until a node is found
                // whose value is greater than the current one
                // This is the same as Step 2 mentioned in the
                // algorithm
                while (arr[last] <= arr[i] && last != root)
                    last = parent[last];

                // arr[i] is the largest element yet; make it
                // new root
                if (arr[last] <= arr[i])
                {
                    parent[root] = i;
                    leftchild[i] = root;
                    root = i;
                }

                // Just insert it
                else if (rightchild[last] == -1)
                {
                    rightchild[last] = i;
                    parent[i] = last;
                    leftchild[i] = -1;
                }

                // Reconfigure links
                else
                {
                    parent[rightchild[last]] = i;
                    leftchild[i] = rightchild[last];
                    rightchild[last] = i;
                    parent[i] = last;
                }

            }

            // Since the root of the Cartesian Tree has no
            // parent, so we assign it -1
            parent[root] = -1;

            Result result = compute(root, arr, parent, leftchild, rightchild, L, R);
            return result.answer;
        }

        Result compute(int node, vector<int>& arr, vector<int>& parent, vector<int>& leftchild, vector<int>& rightchild, int L, int R)
        {
            Result result;
            if (node == -1)
            {
                result.size = 0;
                result.answer = 0;
            }
            else
            {
                Result leftResult = compute(leftchild[node], arr, parent, leftchild, rightchild, L, R);
                Result rightResult = compute(rightchild[node], arr, parent, leftchild, rightchild, L, R);
                result.size = leftResult.size + 1 + rightResult.size;
                result.answer = leftResult.answer + rightResult.answer;
                if (L <= arr[node] && arr[node] <= R)
                {
                    result.answer += ((1 + leftResult.size) * (1 + rightResult.size));
                }
            }

            return result;
        }
    };
};

using namespace _LEET_NUMBER_OF_SUBARRAYS_WITH_BOUNDED_MAXIMUM;

int LEET_NUMBER_OF_SUBARRAYS_WITH_BOUNDED_MAXIMUM()
{
    Solution solution;
    int test_array[] = { 2, 1, 4, 3 };
    cout << solution.numSubarrayBoundedMax(vector<int>(test_array, test_array + _countof(test_array)), 2, 3) << endl;
    return 0;
}