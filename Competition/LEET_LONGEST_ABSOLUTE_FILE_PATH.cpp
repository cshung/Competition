#include "stdafx.h"

// https://leetcode.com/problems/longest-absolute-file-path/

#include "LEET_LONGEST_ABSOLUTE_FILE_PATH.h"
#include <stack>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_LONGEST_ABSOLUTE_FILE_PATH
{
    class Solution
    {
    public:
        int lengthLongestPath(string input)
        {
            int state = 0;
            stack<int> pathLengths;
            size_t i = 0;
            int level = 0;
            int length = 0;
            int longestAbsolutePathLength = 0;
            bool isFile = false;
            while (i < input.size())
            {
                char c = input[i++];
                if (state == 0)
                {
                    if (c == '\t')
                    {
                        level++;
                    }
                    else
                    {
                        i--;
                        state = 1;
                    }
                }
                else if (state == 1)
                {
                    if (c == '.')
                    {
                        isFile = true;
                    }
                    if (c == '\n' || i == input.size())
                    {
                        if (c != '\n')
                        {
                            length++;
                        }
                        if (pathLengths.size() < level)
                        {
                            // Something is wrong with the input in this case
                            return -1;
                        }
                        while (pathLengths.size() > level)
                        {
                            pathLengths.pop();
                        }
                        int parentLength = pathLengths.size() == 0 ? 0 : pathLengths.top();
                        int currentLength = parentLength + length;
                        if (isFile && (currentLength > longestAbsolutePathLength))
                        {
                            longestAbsolutePathLength = currentLength;
                        }
                        pathLengths.push(currentLength + 1);
                        level = 0;
                        length = 0;
                        isFile = false;
                        state = 0;                        
                    }
                    else
                    {
                        length++;
                    }
                }
            }

            return longestAbsolutePathLength;
        }
    };
};

using namespace _LEET_LONGEST_ABSOLUTE_FILE_PATH;

int LEET_LONGEST_ABSOLUTE_FILE_PATH()
{
    Solution solution;
    cout << solution.lengthLongestPath("dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext") << endl;
    cout << string("dir\\subdir1\\subsubdir1").size() << endl;
    return 0;
}