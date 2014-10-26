#include "stdafx.h"
#pragma warning(disable : 4996)

// http://www.spoj.com/problems/HORRIBLE/

#include "SPOJ_HORRIBLE.h"

#include <iostream>

typedef long long int64;

namespace _SPOJ_HORRIBLE
{
    class SegmentTree
    {
    public:
        SegmentTree(int size);
        void add_constant(int from, int to, int64 value);
        int64 query(int from, int to);
        void print() const;
    private:
        class SegmentTreeNode
        {
        public:
            SegmentTreeNode(int from, int to);

            void add_constant(int from, int to, int64 value);
            int64 query(int from, int to);
            
            void print(int indent) const;

            int from;
            int to;
            SegmentTreeNode* left;
            SegmentTreeNode* right;
            int64 sum;
            int64 pending_to_add_to_children;
        private:
            void perform_pending_add();
        };

        SegmentTreeNode* build_tree(int from, int to) const;

        SegmentTreeNode* root;
    };
};

using namespace _SPOJ_HORRIBLE;
using namespace std;

SegmentTree::SegmentTree(int size)
{
    this->root = this->build_tree(0, size);
}

SegmentTree::SegmentTreeNode* SegmentTree::build_tree(int from, int to) const
{
    SegmentTree::SegmentTreeNode* result = new SegmentTree::SegmentTreeNode(from, to);
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

void SegmentTree::add_constant(int from, int to, int64 value)
{
    this->root->add_constant(from, to, value);
}

int64 SegmentTree::query(int from, int to)
{
    return this->root->query(from, to);
}

void SegmentTree::print() const
{
    this->root->print(0);
}

SegmentTree::SegmentTreeNode::SegmentTreeNode(int from, int to) : from(from), to(to), left(NULL), right(NULL), sum(0), pending_to_add_to_children(0)
{
}

void SegmentTree::SegmentTreeNode::add_constant(int from, int to, int64 value)
{
    if (this->from == from && this->to == to)
    {
        this->sum += value * (to - from);
        this->pending_to_add_to_children += value;
    }
    else
    {
        if (this->pending_to_add_to_children != 0)
        {
            this->perform_pending_add();
        }

        this->sum = 0;

        if (this->left != NULL)
        {
            int left_from = from;
            int left_to = min(this->left->to, to);
            if (left_to - left_from > 0)
            {
                this->left->add_constant(left_from, left_to, value);
            }

            this->sum += this->left->sum;
        }

        if (this->right != NULL)
        {
            int right_from = max(this->right->from, from);
            int right_to = to;
            if (right_to - right_from > 0)
            {
                this->right->add_constant(right_from, right_to, value);
            }

            this->sum += this->right->sum;
        }
    }
}

int64 SegmentTree::SegmentTreeNode::query(int from, int to) 
{
    if (this->from == from && this->to == to)
    {
        return this->sum;
    }
    else
    {
        if (this->pending_to_add_to_children != 0)
        {
            this->perform_pending_add();
        }

        int64 result = 0;

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

void SegmentTree::SegmentTreeNode::perform_pending_add()
{
    if (this->pending_to_add_to_children == 0)
    {
        throw 0;
    }
    if (this->left != NULL)
    {        
        if (this->right == NULL)
        {
            throw 0;
        }

        this->left->add_constant(this->left->from, this->left->to, this->pending_to_add_to_children);
        this->right->add_constant(this->right->from, this->right->to, this->pending_to_add_to_children);
        this->pending_to_add_to_children = 0;
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
    cout << "[" << this->from << ", " << this->to << ") has sum = " << this->sum << " . Children need to add (" << this->pending_to_add_to_children << ")" << endl;
    this->left->print(indent + 2);
    this->right->print(indent + 2);
}

int SPOJ_HORRIBLE()
{
    int num_elements;
    int num_operations;
    scanf("%d %d", &num_elements, &num_operations);
    SegmentTree tree(num_elements);
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
            int value;
            scanf(" %d", &value);
            tree.add_constant(from, to, value);
        }
        else
        {
            int64 query_result = tree.query(from, to);
            printf("%d\n", query_result);
        }
    }

    return 0;
}