#include "stdafx.h"

// https://leetcode.com/problems/populating-next-right-pointers-in-each-node-ii/

#include "LEET_POPULATING_NEXT_RIGHT_POINTERS_IN_EACH_NODE_II.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_POPULATING_NEXT_RIGHT_POINTERS_IN_EACH_NODE_II
{
    struct TreeLinkNode
    {
        int val;
        TreeLinkNode *left, *right, *next;
        TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
    };

    class Solution
    {
    public:
        void connect(TreeLinkNode *root)
        {
            if (root == NULL)
            {
                return;
            }

            root->next = NULL;

            TreeLinkNode virtualNode(10086);
            virtualNode.next = root;

            while (virtualNode.next != NULL)
            {
                TreeLinkNode* currentLayerCursor = virtualNode.next;
                TreeLinkNode* nextLayerEnds = &virtualNode;
                nextLayerEnds->next = NULL;
                while (currentLayerCursor != NULL)
                {
                    if (currentLayerCursor->left != NULL)
                    {
                        nextLayerEnds->next = currentLayerCursor->left;
                        nextLayerEnds = nextLayerEnds->next;
                    }
                    if (currentLayerCursor->right != NULL)
                    {
                        nextLayerEnds->next = currentLayerCursor->right;
                        nextLayerEnds = nextLayerEnds->next;
                    }
                    currentLayerCursor = currentLayerCursor->next;
                }
            }
        }
    };
};

using namespace _LEET_POPULATING_NEXT_RIGHT_POINTERS_IN_EACH_NODE_II;

int LEET_POPULATING_NEXT_RIGHT_POINTERS_IN_EACH_NODE_II()
{
    TreeLinkNode a(1);
    TreeLinkNode b(2);
    TreeLinkNode c(3);
    TreeLinkNode d(4);
    TreeLinkNode e(5);
    TreeLinkNode g(7);
    a.left = &b;
    a.right = &c;
    b.left = &d;
    b.right = &e;
    c.left = NULL;
    c.right = &g;
    d.left = NULL;
    d.right = NULL;
    e.left = NULL;
    e.right = NULL;
    g.left = NULL;
    g.right = NULL;
    Solution solution;
    solution.connect(&a);
    cout << ((a.next == NULL) ? "Yes" : "No") << endl;
    cout << ((b.next == &c) ? "Yes" : "No") << endl;
    cout << ((c.next == NULL) ? "Yes" : "No") << endl;
    cout << ((d.next == &e) ? "Yes" : "No") << endl;
    cout << ((e.next == &g) ? "Yes" : "No") << endl;
    cout << ((g.next == NULL) ? "Yes" : "No") << endl;
    return 0;
}