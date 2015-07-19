#include "stdafx.h"

// https://leetcode.com/problems/binary-search-tree-iterator/

#include "LEET_BINARY_SEARCH_TREE_ITERATOR.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <stack>

using namespace std;

namespace _LEET_BINARY_SEARCH_TREE_ITERATOR
{
    struct TreeNode
    {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };

    class BSTIterator
    {
    private:
        stack<TreeNode *> unvisited_parents;
        TreeNode* will_visit;
    public:
        BSTIterator(TreeNode *root)
        {
            if (root != NULL)
            {
                while (root != NULL)
                {
                    this->unvisited_parents.push(root);
                    root = root->left;
                }
                this->will_visit = this->unvisited_parents.top();
            }
            else
            {
                this->will_visit = NULL;
            }
        }

        /** @return whether we have a next smallest number */
        bool hasNext()
        {
            return this->will_visit != NULL;
        }

        /** @return the next smallest number */
        int next()
        {
            TreeNode* should_return = this->will_visit;
            TreeNode* current = this->will_visit;
            this->unvisited_parents.pop();
            if (current->right != NULL)
            {
                current = current->right;
                while (current != NULL)
                {
                    this->unvisited_parents.push(current);
                    current = current->left;
                }
            }
            this->will_visit = this->unvisited_parents.size() == 0 ? NULL : this->unvisited_parents.top();

            return should_return->val;
        }
    };
};

using namespace _LEET_BINARY_SEARCH_TREE_ITERATOR;

int LEET_BINARY_SEARCH_TREE_ITERATOR()
{
    TreeNode a(3);
    TreeNode b(5);
    TreeNode c(1);
    TreeNode d(6);
    TreeNode e(2);
    TreeNode f(0);
    TreeNode g(8);
    TreeNode h(7);
    TreeNode i(4);
    a.left = &b;
    a.right = &c;
    b.left = &d;
    b.right = &e;
    c.left = &f;
    c.right = &g;
    e.left = &h;
    e.right = &i;
    BSTIterator iter(&a);
    while (iter.hasNext())
    {
        cout << iter.next() << ",";
    }
    cout << endl;
    return 0;
}