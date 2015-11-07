#include "stdafx.h"

// https://leetcode.com/problems/serialize-and-deserialize-binary-tree/

#include "LEET_SERIALIZE_AND_DESERIALIZE_BINARY_TREE.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;

namespace _LEET_SERIALIZE_AND_DESERIALIZE_BINARY_TREE
{
    struct TreeNode
    {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };

    class Codec
    {
    public:
        // Encodes a tree to a single string.
        string serialize(TreeNode* root)
        {
            ostringstream result_builder;
            queue<TreeNode*> buffer1;
            queue<TreeNode*> buffer2;

            queue<TreeNode*>& this_level = buffer1;
            queue<TreeNode*>& next_level = buffer2;
            this_level.push(root);
            bool first = true;
            while (this_level.size() > 0)
            {
                bool hasNonNull = false;
                while (this_level.size() > 0)
                {
                    TreeNode* this_node = this_level.front();
                    this_level.pop();
                    if (this_node == NULL)
                    {
                        if (first) { first = false; } else { result_builder << ","; }
                        result_builder << "null";
                    }
                    else
                    {
                        if (first) { first = false; } else { result_builder << ","; }
                        result_builder << this_node->val;
                        next_level.push(this_node->left);
                        next_level.push(this_node->right);
                        if (this_node->left != NULL || this_node->right != NULL)
                        {
                            hasNonNull = true;
                        }
                    }
                }
                if (!hasNonNull)
                {
                    while (next_level.size() > 0)
                    {
                        next_level.pop();
                    }
                }
                swap(this_level, next_level);
            }

            return result_builder.str();
        }

        // Decodes your encoded data to tree.
        TreeNode* deserialize(string data)
        {
            int start = 0;
            int scan = start;
            int len = data.size();



            vector<TreeNode*> nodes;
            while (scan < len)
            {
                if (data[scan] == ',' || scan == len - 1)
                {
                    // Found a token, process it
                    if (scan == len - 1)
                    {
                        // Just in case we reach the end of string, make sure scan point to 
                        // beyond the end of the string (like a virtual comma) 
                        scan++;
                    }
                    string token = data.substr(start, scan - start);
                    TreeNode* tokenNode = NULL;
                    if (token != "null")
                    {
                        int val;
                        istringstream decoder(token);
                        decoder >> val;
                        tokenNode = new TreeNode(val);
                        cout << val << endl;
                    }

                    nodes.push_back(tokenNode);

                    // Start from the next token
                    start = scan + 1;
                }
                scan++;
            }

            unsigned int i = 1;
            TreeNode* root = nodes[0];
            queue<TreeNode*> queue;
            queue.push(root);
            while (i < nodes.size())
            {
                TreeNode* current = queue.front();
                queue.pop();
                TreeNode* leftNode = nodes[i++];
                TreeNode* rightNode = nodes[i++];
                if (leftNode != NULL)
                {
                    current->left = leftNode;
                    queue.push(leftNode);
                }
                if (rightNode != NULL)
                {
                    current->right = rightNode;
                    queue.push(rightNode);
                }
            }

            return root;
        }
    };
};

using namespace _LEET_SERIALIZE_AND_DESERIALIZE_BINARY_TREE;

int LEET_SERIALIZE_AND_DESERIALIZE_BINARY_TREE()
{
    Codec solution;
    TreeNode a(1);
    TreeNode b(2);
    TreeNode c(3);
    a.right = &b;
    b.left = &c;
    TreeNode* as = solution.deserialize(solution.serialize(&a));
    cout << as->val << endl;
    cout << as->right->val << endl;
    cout << as->right->left->val << endl;
    return 0;
}