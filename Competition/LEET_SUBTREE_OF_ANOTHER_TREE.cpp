#include "stdafx.h"

// https://leetcode.com/problems/subtree-of-another-tree

#include "LEET_SUBTREE_OF_ANOTHER_TREE.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_SUBTREE_OF_ANOTHER_TREE
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
        void ToString(TreeNode* s, ostringstream& sout)
        {
            if (s == nullptr)
            {
                sout << "#" << ",";
            }
            else
            {
                sout << "(";
                ToString(s->left, sout);
                sout << s->val;
                sout << ",";
                ToString(s->right, sout);
                sout << ")";
            }
        }
        bool isSubtree(TreeNode* s, TreeNode* t)
        {
            ostringstream sout;
            ostringstream tout;
            ToString(s, sout);
            ToString(t, tout);
            string sstr = sout.str();
            string tstr = tout.str();
            const char* x = strstr(sstr.c_str(), tstr.c_str());
            return (x != nullptr);
        }
    };
};

using namespace _LEET_SUBTREE_OF_ANOTHER_TREE;

int LEET_SUBTREE_OF_ANOTHER_TREE()
{
    TreeNode a(3);
    TreeNode b(4);
    TreeNode c(5);
    TreeNode d(1);
    TreeNode e(2);
    a.left = &b;
    a.right = &c;
    b.left = &d;
    b.right = &e;
    c.left = nullptr;
    c.right = nullptr;
    d.left = nullptr;
    d.right = nullptr;
    e.left = nullptr;
    e.right = nullptr;

    TreeNode p(4);
    TreeNode q(1);
    TreeNode r(2);
    p.left = &q;
    p.right = &r;
    q.left = nullptr;
    q.right = nullptr;
    r.left = nullptr;
    r.right = nullptr;

    Solution s;
    cout << (s.isSubtree(&a, &p) ? "True" : "False") << endl;
    return 0;
}