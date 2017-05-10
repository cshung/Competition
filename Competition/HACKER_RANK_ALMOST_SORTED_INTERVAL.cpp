#include "stdafx.h"

// https://www.hackerrank.com/challenges/almost-sorted-interval

#include "HACKER_RANK_ALMOST_SORTED_INTERVAL.h"
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// I am still debugging this test case

/*
100
64 82 55 36 88 86 6 95 47 49 9 27 3 59 65 5 85 16 83 72 75 97 34 87 22 39 8 35 10 94 58 71 57 14 4 79 43 84 7 48 42 44 37 26 21 93 91 80 23 11 12 92 2 19 96 13 50 68 61 70 60 81 15 54 20 25 40 52 67 53 63 46 76 66 1 38 99 51 17 73 41 56 31 69 28 30 24 32 90 74 62 98 77 18 33 89 29 45 78 100
*/
namespace _HACKER_RANK_ALMOST_SORTED_INTERVAL
{
    void walk(int node, int* left, int* right, int* small, int* large, int* pCount, int* pCountExt)
    {
        int leftCount;
        int leftCountExt;
        int rightCount;
        int rightCountExt;

        if (left[node] == -1 && right[node] == -1)
        {
            *pCount = 1;
            *pCountExt = 1;

            small[node] = node;
            large[node] = node + 1;
        }
        else if (left[node] == -1)
        {
            walk(right[node], left, right, small, large, &rightCount, &rightCountExt);
            *pCount = 1 + rightCount;
            *pCountExt = rightCountExt;

            small[node] = node;
            large[node] = large[right[node]];
        }
        else if (right[node] == -1)
        {
            walk(left[node], left, right, small, large, &leftCount, &leftCountExt);
            *pCount = leftCount + leftCountExt + 1;
            *pCountExt = leftCountExt + leftCountExt + 1;

            small[node] = small[left[node]];
            large[node] = node + 1;
        }
        else
        {
            walk(left[node], left, right, small, large, &leftCount, &leftCountExt);
            walk(right[node], left, right, small, large, &rightCount, &rightCountExt);
            *pCount = leftCount + leftCountExt + 1 + rightCount;
            *pCountExt = rightCountExt;
            small[node] = small[left[node]];
            large[node] = large[right[node]];
        }

        cout << "[" << small[node] << "," << large[node] << ")" << " = " << *pCount << endl;
    }

    bool check(int node, int* input, int* left, int* right, int valueUpperBound, int indexLowerBound, int indexUpperBound)
    {
        if (node == -1)
        {
            return true;
        }
        if (input[node] > valueUpperBound)
        {
            return false;
        }
        if (node < indexLowerBound)
        {
            return false;
        }
        if (node > indexUpperBound)
        {
            return false;
        }
        if (!check(left[node], input, left, right, input[node], indexLowerBound, node))
        {
            return false;
        }
        if (!check(right[node], input, left, right, input[node], node, indexUpperBound))
        {
            return false;
        }
        return true;
    }
}

using namespace _HACKER_RANK_ALMOST_SORTED_INTERVAL;

int HACKER_RANK_ALMOST_SORTED_INTERVAL()
{
    // Step 1: Read the input
    int n;
    cin >> n;
    int* input = new int[n];
    for (int i = 0; i < n; i++)
    {
        cin >> input[i];
    }

    // Step 2: Build a (Max) Cartesian tree
    // A cartesian tree is a tree such that the maximum of the array is at the top
    // The left hand side is recursively a Cartesian tree of the elements on the left of the max element
    // Similarly for the right hand side
    int* left = new int[n];
    int* right = new int[n];
    int* parent = new int[n];

    // For debugging use
    int* small = new int[n];
    int* large = new int[n];

    int root = 0;
    left[0] = -1;
    right[0] = -1;
    parent[0] = -1;
    for (int i = 1; i < n; i++)
    {
        int last = i - 1;
        while (input[last] < input[i] && last != root)
        {
            last = parent[last];
        }
        right[i] = -1;
        if (input[last] < input[i])
        {
            parent[root] = i;
            left[i] = root;
            parent[i] = -1;
            root = i;
        }
        else if (right[last] == -1)
        {
            right[last] = i;
            left[i] = -1;
            parent[i] = last;
        }
        else
        {
            parent[right[last]] = i;
            left[i] = right[last];
            right[last] = i;
            parent[i] = last;
        }
    }

    if (!check(root, input, left, right, n + 1, -1, n))
    {
        cout << "Bad tree!" << endl;
    }

    // Step 3: Walk the tree to find out the answer
    int count;
    int countExt;
    walk(root, left, right, small, large, &count, &countExt);

    cout << count << endl;

    int s = 0;
    int e = 100;

    count = 0;
    for (int i = s; i < e; i++)
    {
        for (int j = i + 1; j <= e; j++)
        {
            bool valid = true;
            for (int k = i; valid && k < j; k++)
            {
                if (input[k] < input[i]) {
                    valid = false;
                }
                if (input[k] > input[j - 1]) {
                    valid = false;
                }
            }
            if (valid)
            {
                count++;
            }
        }
    }
    cout << count << endl;

    delete[] input;
    delete[] left;
    delete[] right;
    delete[] parent;
    return 0;
}
