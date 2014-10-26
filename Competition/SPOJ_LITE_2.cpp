#include "stdafx.h"
#pragma warning(disable : 4996)

// http://www.spoj.com/problems/LITE/

#include "SPOJ_LITE_2.h"
#include <stdio.h>
#include <iostream>
#include <algorithm>

namespace _SPOJ_LITE_2
{
    using namespace std;

    class SegmentTree
    {
    public:
        SegmentTree(int size);
        void flip_lights(int from, int to);
        int query(int from, int to);
        void print() const;
    private:
        class SegmentTreeNode
        {
        public:
            SegmentTreeNode(int from, int to);
            void flip_children();
            void flip_lights(int from, int to);
            int query(int from, int to) ;
            void print(int indent) const;

            int from;
            int to;
            SegmentTreeNode* left;
            SegmentTreeNode* right;
            int on_count;
            bool children_flipped;
        };

        SegmentTreeNode* build_tree(int from, int to) const;
        SegmentTreeNode* root;
    };
}

using namespace _SPOJ_LITE_2;
using namespace std;

SegmentTree::SegmentTree(int size)
{
    this->root = this->build_tree(0, size);
}

void SegmentTree::flip_lights(int from, int to)
{
    this->root->flip_lights(from, to);
}

int SegmentTree::query(int from, int to) 
{
    return this->root->query(from, to);
}

void SegmentTree::print() const
{
    this->root->print(0);
}

SegmentTree::SegmentTreeNode::SegmentTreeNode(int from, int to) : from(from), to(to), left(NULL), right(NULL), on_count(0), children_flipped(false)
{
}

void SegmentTree::SegmentTreeNode::flip_children()
{
    if (this->left == NULL)
    {
        if (this->right != NULL)
        {
            throw 0;
        }
    }
    else
    {
        this->left->flip_lights(this->left->from, this->left->to);
        this->right->flip_lights(this->right->from, this->right->to);
        this->on_count = this->left->on_count + this->right->on_count;
        this->children_flipped = false;
    }
}

void SegmentTree::SegmentTreeNode::flip_lights(int from, int to)
{
    if (from == this->from && to == this->to)
    {
        this->on_count = (this->to - this->from) - this->on_count;
        this->children_flipped = !this->children_flipped;
    }
    else
    {
        if (children_flipped)
        {
            this->flip_children();
        }
                    
        this->on_count = 0;

        if (this->left != NULL)
        {
            int left_from = from;
            int left_to = min(this->left->to, to);
            if (left_to - left_from > 0)
            {
                this->left->flip_lights(left_from, left_to);
            }

            this->on_count += this->left->on_count;
        }

        if (this->right != NULL)
        {
            int right_from = max(this->right->from, from);
            int right_to = to;
            if (right_to - right_from > 0)
            {
                this->right->flip_lights(right_from, right_to);
            }

            this->on_count += this->right->on_count;
        }
    }
}

int SegmentTree::SegmentTreeNode::query(int from, int to) 
{
    if (this->from == from && this->to == to)
    {
        return this->on_count;
    }
    else
    {
        if (children_flipped)
        {
            this->flip_children();
        }

        int result = 0;

        if (this->left != NULL)
        {
            int left_from = from;
            int left_to = min(this->left->to, to);
            if (left_to - left_from > 0)
            {
                result += this->left->query(left_from, left_to);
            }
        }

        if (this->right != NULL)
        {
            int right_from = max(this->right->from, from);
            int right_to = to;
            if (right_to - right_from > 0)
            {
                result += this->right->query(right_from, right_to);
            }
        }

        return result;
    }
}

void SegmentTree::SegmentTreeNode::print(int indent) const
{
    if (this == NULL)
    {
        return;
    }

    for (int i = 0; i < indent; i++)
    {
        cout << ' ';
    }
    cout << "[" << this->from << ", " << this->to << ") has " << this->on_count << " lights on. (" << this->children_flipped << ")" << endl;
    this->left->print(indent + 2);
    this->right->print(indent + 2);
}

SegmentTree::SegmentTreeNode* SegmentTree::build_tree(int from, int to) const
{
    SegmentTree::SegmentTreeNode* result = new SegmentTree::SegmentTreeNode(from, to);
    result->from = from;
    result->to = to;
    int size = to - from;
    if (size == 1)
    {
        // no-op, children are NULL already
    }
    else if (size > 1)
    {
        int left_size = size / 2;
        int right_size = size - left_size;
        int split = from + left_size;
        result->left = this->build_tree(from, split);
        result->right = this->build_tree(split, to);
    }
    else
    {
        throw 0;
    }

    return result;
}

int SPOJ_LITE_2()
{
    int num_lights;
    int num_operations;
    scanf("%d %d", &num_lights, &num_operations);
    SegmentTree tree(num_lights);
    for (int q = 0; q < num_operations; q++)
    {
        int operation_id;
        int from;
        int to;
        scanf("%d %d %d", &operation_id, &from, &to);

        // Converting the input one base inclusive/inclusive index to zero base inclusive/exclusive index
        from--;

        if (operation_id == 0)
        {
            tree.flip_lights(from, to); 
        }
        else
        {
            int query_result = tree.query(from, to);
            printf("%d\n", query_result);
        }
    }

    return 0;
}