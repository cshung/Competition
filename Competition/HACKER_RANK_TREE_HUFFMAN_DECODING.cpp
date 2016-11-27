#include "stdafx.h"

// https://www.hackerrank.com/challenges/tree-huffman-decoding

#include "HACKER_RANK_TREE_HUFFMAN_DECODING.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _HACKER_RANK_TREE_HUFFMAN_DECODING
{
    typedef struct node
    {
        int freq;
        char data;
        node * left;
        node * right;

    } node;

    void decode_huff(node * root, string s)
    {
        node* cur = root;
        for (size_t i = 0; i < s.length(); i++)
        {
            if (s[i] == '0')
            {
                cur = cur->left;
                if (cur->left == nullptr && cur->right == nullptr)
                {
                    cout << cur->data;
                    cur = root;
                }
            }
            else
            {
                cur = cur->right;
                if (cur->left == nullptr && cur->right == nullptr)
                {
                    cout << cur->data;
                    cur = root;
                }
            }
        }
    }
};

using namespace _HACKER_RANK_TREE_HUFFMAN_DECODING;

int HACKER_RANK_TREE_HUFFMAN_DECODING()
{
    node a;
    node b;
    node c;
    node d;
    node e;
    a.data = '\0';
    b.data = '\0';
    c.data = 'A';
    d.data = 'B';
    e.data = 'C';
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
    decode_huff(&a, "1001011");
    return 0;
}