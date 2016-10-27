#include "stdafx.h"

// https://leetcode.com/problems/path-sum-iii/

#include "LEET_PATH_SUM_III.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_PATH_SUM_III
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
        int pathSum(TreeNode* root, int sum)
        {
            int offset = 0;
            map<int, int> targets;
            return pathSum(root, sum, targets, offset, 0);
        }
    private:
        int pathSum(TreeNode* root, int sum, map<int, int>& targets, int& offset, int indent)
        {
            if (root == nullptr)
            {
                return 0;
            }
            /*
            for (int i = 0; i < indent; i++) { cout << " "; }
            cout << "Processing " << root->val << endl;
            for (int i = 0; i < indent; i++) { cout << " "; }
            for (auto t : targets)
            {
                cout << "(" << (t.first + offset) << ", " << t.second << "), ";
            }
            cout << endl;
            */
            int count = 0;
            if (root->val == sum)
            {
                // Special case, this is a sum of 1 value
                count++;
            }
            map<int, int>::iterator probe1 = targets.find(root->val - offset);
            if (probe1 != targets.end())
            {
                count += probe1->second;
            }

            offset -= root->val;
            int entry = sum - offset - root->val;
            map<int, int>::iterator probe2 = targets.find(entry);
            bool foundEntry = false;
            if (probe2 == targets.end())
            {
                targets.insert(pair<int, int>(entry, 1));
            }
            else
            {
                foundEntry = true;
                probe2->second++;
            }
            
            count += this->pathSum(root->left, sum, targets, offset, indent + 2);
            count += this->pathSum(root->right, sum, targets, offset, indent + 2);

            if (foundEntry)
            {
                targets[entry]--;
            }
            else
            {
                targets.erase(entry);
            }
            offset += root->val;

            return count;
        }
    };
};

using namespace _LEET_PATH_SUM_III;

int LEET_PATH_SUM_III()
{
    Solution solution;
    TreeNode a(10);
    TreeNode b(5);
    TreeNode c(-3);
    TreeNode d(3);
    TreeNode e(2);
    TreeNode f(11);
    TreeNode g(3);
    TreeNode h(-2);
    TreeNode i(1);
    a.left = &b;
    a.right = &c;
    b.left = &d;
    b.right = &e;
    c.right = &f;
    d.left = &g;
    d.right = &h;
    e.right = &i;

    cout << solution.pathSum(&a, 8) << endl;

    return 0;
}