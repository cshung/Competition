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
    class Node
    {
    public:
        int val;
        Node* left;
        Node* right;
        Node* next;

        Node() : val(0), left(NULL), right(NULL), next(NULL) {}

        Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

        Node(int _val, Node* _left, Node* _right, Node* _next)
            : val(_val), left(_left), right(_right), next(_next) {}
    };
    class Solution
    {
    public:
        Node* connect(Node* root)
        {
            if (root == NULL)
            {
                return NULL;
            }

            root->next = NULL;

            Node* nextLayerStart = root;
            while (nextLayerStart != NULL)
            {
                Node* currentLayerCursor = nextLayerStart;
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
            return root;
        }
    };
};

using namespace _LEET_POPULATING_NEXT_RIGHT_POINTERS_IN_EACH_NODE;

int LEET_POPULATING_NEXT_RIGHT_POINTERS_IN_EACH_NODE()
{
    Node a;
    Node b;
    Node c;
    Node d;
    Node e;
    Node f;
    Node g;
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