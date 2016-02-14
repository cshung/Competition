#include "stdafx.h"

// https://leetcode.com/problems/verify-preorder-serialization-of-a-binary-tree/

#include "LEET_VERIFY_PREORDER_SERIALIZATION_OF_A_BINARY_TREE.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_VERIFY_PREORDER_SERIALIZATION_OF_A_BINARY_TREE
{
    class Solution
    {
    public:
        int next(string& preorder, size_t start)
        {
            int end = start;
            while (end < preorder.size())
            {
                if (preorder[end++] == ',')
                {
                    break;
                }
            }
            return end;
        }

        size_t verify(string& preorder, size_t start)
        {
            if (start == preorder.length())
            {
                return -1;
            }
            if (preorder[start] == '#')
            {
                return next(preorder, start);
            }
            else
            {
                int leftStart = next(preorder, start);
                int rightStart = verify(preorder, leftStart);
                if (rightStart == -1)
                {
                    return -1;
                }
                else
                {
                    return verify(preorder, rightStart);
                }
            }
        }

        bool isValidSerialization(string preorder)
        {
            int end = verify(preorder, 0);
            return end == preorder.length();
        }
    };
};

using namespace _LEET_VERIFY_PREORDER_SERIALIZATION_OF_A_BINARY_TREE;

int LEET_VERIFY_PREORDER_SERIALIZATION_OF_A_BINARY_TREE()
{
    Solution solution;
    cout << (solution.isValidSerialization("9,3,4,#,#,1,#,#,2,#,6,#,#") == true) << endl;
    return 0;
}