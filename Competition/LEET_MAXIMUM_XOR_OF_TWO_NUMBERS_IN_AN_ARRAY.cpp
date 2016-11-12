// LEET_MAXIMUM_XOR_OF_TWO_NUMBERS_IN_AN_ARRAY
#include "stdafx.h"

// https://leetcode.com/problems/maximum-xor-of-two-numbers-in-an-array/

#include "LEET_MAXIMUM_XOR_OF_TWO_NUMBERS_IN_AN_ARRAY.h"
#include <stack>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_MAXIMUM_XOR_OF_TWO_NUMBERS_IN_AN_ARRAY
{
    struct MyTreeNode
    {
        MyTreeNode* left;
        MyTreeNode* right;
    };
    class Solution
    {
    public:
        int findMaximumXOR(MyTreeNode* p1, MyTreeNode* p2, int level)
        {
            int result = 0;
            if (level == 0)
            {
                return 0;
            }
            if ((p1->left != nullptr && p2->right != nullptr) || (p1->right != nullptr && p2->left != nullptr))
            {
                if (p1->left != nullptr && p2->right != nullptr)
                {
                    result = findMaximumXOR(p1->left, p2->right, level - 1);
                }
                if (p1->right != nullptr && p2->left != nullptr)
                {
                    result = max(result, findMaximumXOR(p1->right, p2->left, level - 1));
                }
                result += 1 << (level - 1);
            }
            else
            { 
                if (p1->left != nullptr && p2->left != nullptr)
                {
                    result = findMaximumXOR(p1->left, p2->left, level - 1);
                }
                if (p1->right != nullptr && p2->right != nullptr)
                {
                    result = max(result, findMaximumXOR(p1->right, p2->right, level - 1));
                }
            }
            return result;
        }
        int findMaximumXOR(vector<int>& nums)
        {
            // Step 1: Build a trie out of the binary digits of the numbers
            int n = nums.size();
            MyTreeNode* root = new MyTreeNode();
            int current_level = -1;
            for (int i = 0; i < n; i++)
            {
                int d = nums[i];
                stack<int> digits;
                while (d > 0)
                {
                    digits.push(d % 2);
                    d /= 2;
                }
                if (current_level == -1)
                {
                    current_level= digits.size();
                }
                else
                {
                    while (digits.size() < current_level)
                    {
                        digits.push(0);
                    }
                    while (current_level < digits.size())
                    {
                        MyTreeNode* newRoot = new MyTreeNode();
                        newRoot->left = root;
                        root = newRoot;
                        current_level++;
                    }
                }
                MyTreeNode* cur = root;
                while (digits.size() > 0)
                {
                    int d = digits.top();
                    digits.pop();
                    if (d == 0)
                    {
                        if (cur->left == nullptr)
                        {
                            cur->left = new MyTreeNode();
                        }
                        cur = cur->left;
                    }
                    else
                    {
                        if (cur->right == nullptr)
                        {
                            cur->right = new MyTreeNode();
                        }
                        cur = cur->right;
                    }
                }
            }
            // Walk the trie with two pointers to find the answer
            return findMaximumXOR(root, root, current_level);
        }
    };
};

using namespace _LEET_MAXIMUM_XOR_OF_TWO_NUMBERS_IN_AN_ARRAY;

int LEET_MAXIMUM_XOR_OF_TWO_NUMBERS_IN_AN_ARRAY()
{
    Solution solution;
    int input_array[] = { 3, 10, 5, 25, 2, 8 };
    vector<int> input(input_array, input_array + _countof(input_array));
    cout << solution.findMaximumXOR(input);
    return 0;
}