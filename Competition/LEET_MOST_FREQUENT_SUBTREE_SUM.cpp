#include "stdafx.h"

// https://leetcode.com/problems/most-frequent-subtree-sum/

#include "LEET_MOST_FREQUENT_SUBTREE_SUM.h"
#include <map>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

namespace _LEET_MOST_FREQUENT_SUBTREE_SUM
{
    struct TreeNode
    {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };

    class Solution
    {
    public:
        int findFrequentTreeSum(TreeNode* root, map<int, int>& histogram)
        {
            if (root == nullptr)
            {
                return 0;
            }
            int left = findFrequentTreeSum(root->left, histogram);
            int right = findFrequentTreeSum(root->right, histogram);
            int sum = left + right + root->val;
            auto probe = histogram.find(sum);
            if (probe == histogram.end())
            {
                histogram.insert(make_pair(sum, 1));
            }
            else
            {
                probe->second++;
            }

            return sum;
        }
        vector<int> findFrequentTreeSum(TreeNode* root)
        {
            map<int, int> histogram;
            findFrequentTreeSum(root, histogram);
            int max_freq = -1;
            for (auto pair : histogram)
            {
                max_freq = max(max_freq, pair.second);
            }
            vector<int> solution;
            for (auto pair : histogram)
            {
                if (pair.second == max_freq)
                {
                    solution.push_back(pair.first);
                }
            }

            return solution;
        }
    };
};

using namespace _LEET_MOST_FREQUENT_SUBTREE_SUM;

int LEET_MOST_FREQUENT_SUBTREE_SUM()
{
    Solution solution;
    TreeNode a(5);
    TreeNode b(2);
    TreeNode c(-3);
    a.left = &b;
    a.right = &c;
    auto test1 = solution.findFrequentTreeSum(&a);
    for (auto result : test1)
    {
        cout << result << " ";
    }
    cout << endl;

    TreeNode p(5);
    TreeNode q(2);
    TreeNode r(-5);
    p.left = &q;
    p.right = &r;
    auto test2 = solution.findFrequentTreeSum(&p);
    for (auto result : test2)
    {
        cout << result << " ";
    }
    cout << endl;
    return 0;
}