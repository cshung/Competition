#include "stdafx.h"

// https://leetcode.com/problems/vertical-order-traversal-of-a-binary-tree/

#include "LEET_VERTICAL_ORDER_TRAVERSAL_OF_A_BINARY_TREE.h"
#include <map>
#include <iostream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_VERTICAL_ORDER_TRAVERSAL_OF_A_BINARY_TREE
{
    struct TreeNode
    {
        int val;
        TreeNode* left;
        TreeNode* right;
        TreeNode() : val(0), left(nullptr), right(nullptr) {}
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
        TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
    };
    class Solution
    {
    public:
        vector<vector<int> > verticalTraversal(TreeNode* root)
        {
            vector<vector<int> > answer;
            if (root == NULL)
            {
                return answer;
            }
            unordered_map<int, vector<pair<int, int> > > records;
            queue<int> x;
            queue<int> y;
            queue<TreeNode*> bfs;
            x.push(0);
            y.push(0);
            bfs.push(root);
            int minX = 0;
            int maxX = 0;
            while (!bfs.empty())
            {
                TreeNode* current = bfs.front();
                int cv = current->val;
                int cx = x.front();
                int cy = y.front();
                bfs.pop();
                x.pop();
                y.pop();
                minX = min(minX, cx);
                maxX = max(maxX, cx);
                auto probe = records.find(cx);
                if (probe == records.end())
                {
                    records.insert(make_pair(cx, vector<pair<int, int> >()));
                }
                vector<pair<int, int> >& list = records[cx];
                list.push_back(make_pair(cy, cv));
                int i = list.size() - 1;
                while (true)
                {
                    if (i == 0)
                    {
                        break;
                    }
                    if (list[i - 1].first != list[i].first)
                    {
                        break;
                    }
                    if (list[i - 1].second < list[i].second)
                    {
                        break;
                    }
                    swap(list[i - 1], list[i]);
                    i--;
                }
                if (current->left != nullptr)
                {
                    x.push(cx - 1);
                    y.push(cy - 1);
                    bfs.push(current->left);
                }
                if (current->right != nullptr)
                {
                    x.push(cx + 1);
                    y.push(cy - 1);
                    bfs.push(current->right);
                }
            }
            for (int x = minX; x <= maxX; x++)
            {
                vector<int> row;
                for (auto record : records[x])
                {
                    row.push_back(record.second);
                }
                answer.push_back(row);
            }
            return answer;
        }
    };

};

using namespace _LEET_VERTICAL_ORDER_TRAVERSAL_OF_A_BINARY_TREE;

int LEET_VERTICAL_ORDER_TRAVERSAL_OF_A_BINARY_TREE()
{
    TreeNode a(3);
    TreeNode b(9);
    TreeNode c(20);
    TreeNode d(15);
    TreeNode e(7);
    a.left = &b;
    a.right = &c;
    b.left = nullptr;
    b.right = nullptr;
    c.left = &d;
    c.right = &e;
    d.left = nullptr;
    d.right = nullptr;
    e.left = nullptr;
    e.right = nullptr;
    Solution s;
    for (auto list : s.verticalTraversal(&a))
    {
        for (auto val : list)
        {
            cout << val << " ";
        }
        cout << endl;
    }
    return 0;
}