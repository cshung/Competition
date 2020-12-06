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

            Node virtualNode(10086);
            virtualNode.next = root;

            while (virtualNode.next != NULL)
            {
                Node* currentLayerCursor = virtualNode.next;
                Node* nextLayerEnds = &virtualNode;
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
            return root;
        }
    };
};

using namespace _LEET_POPULATING_NEXT_RIGHT_POINTERS_IN_EACH_NODE_II;

int LEET_POPULATING_NEXT_RIGHT_POINTERS_IN_EACH_NODE_II()
{
    Node a(1);
    Node b(2);
    Node c(3);
    Node d(4);
    Node e(5);
    Node g(7);
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