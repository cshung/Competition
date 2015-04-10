#include "stdafx.h"

// https://leetcode.com/problems/populating-next-right-pointers-in-each-node/

#include "LEET_POPULATING_NEXT_RIGHT_POINTERS_IN_EACH_NODE.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_POPULATING_NEXT_RIGHT_POINTERS_IN_EACH_NODE
{
    struct TreeLinkNode
    {
        TreeLinkNode *left;
        TreeLinkNode *right;
        TreeLinkNode *next;
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

            TreeLinkNode* nextLayerStart = root;
            while (nextLayerStart != NULL)
            {
                TreeLinkNode* currentLayerCursor = nextLayerStart;
                nextLayerStart = nextLayerStart->left;
                if (nextLayerStart == NULL)
                {
                    break;
                }

                while (currentLayerCursor != NULL)
                {
                    currentLayerCursor->left->next = currentLayerCursor->right;
                    if (currentLayerCursor->next == NULL)
                    {
                        currentLayerCursor->right->next = NULL;
                    }
                    else
                    {
                        currentLayerCursor->right->next = currentLayerCursor->next->left;
                    }

                    currentLayerCursor = currentLayerCursor->next;
                }
            }
        }
    };
};

using namespace _LEET_POPULATING_NEXT_RIGHT_POINTERS_IN_EACH_NODE;

int LEET_POPULATING_NEXT_RIGHT_POINTERS_IN_EACH_NODE()
{
    TreeLinkNode a;
    TreeLinkNode b;
    TreeLinkNode c;
    TreeLinkNode d;
    TreeLinkNode e;
    TreeLinkNode f;
    TreeLinkNode g;
    a.left = &b;
    a.right = &c;
    b.left = &d;
    b.right = &e;
    c.left = &f;
    c.right = &g;
    d.left = NULL;
    d.right = NULL;
    e.left = NULL;
    e.right = NULL;
    f.left = NULL;
    f.right = NULL;
    g.left = NULL;
    g.right = NULL;
    Solution solution;
    solution.connect(&a);
    cout << ((a.next == NULL) ? "Yes" : "No") << endl;
    cout << ((b.next == &c  ) ? "Yes" : "No") << endl;
    cout << ((c.next == NULL) ? "Yes" : "No") << endl;
    cout << ((d.next == &e  ) ? "Yes" : "No") << endl;
    cout << ((e.next == &f  ) ? "Yes" : "No") << endl;
    cout << ((f.next == &g  ) ? "Yes" : "No") << endl;
    cout << ((g.next == NULL) ? "Yes" : "No") << endl;
    return 0;
}