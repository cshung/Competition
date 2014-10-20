#include "stdafx.h"

// TODO

#include "SPOJ_LITE.h"

#include <iostream>
#include <map>

using namespace std;

const int left_too_heavy = 2;
const int left_heavy = 1;
const int balance = 0;
const int right_heavy = -1;
const int right_too_heavy = -2;

const int bias_left = 1;
const int bias_right = -1;

class SegmentTree
{
public:
    SegmentTree();
    ~SegmentTree();
    // Should be private
    void insert_elementary_interval(int from, int to);
    // Should be private
    void delete_containing_interval(int value);
    // Debug only
    void print();
private:
    class SegmentTreeNode
    {
    public:
        SegmentTreeNode(int from, int to);
        ~SegmentTreeNode();
        int get_from() const;
        int get_to() const;
        void set_interval(int from, int to);
        SegmentTreeNode* get_left() const;
        SegmentTreeNode* get_right() const;
        void set_left(SegmentTreeNode* left);
        void set_right(SegmentTreeNode* right);

        // Debug only
        void print(int indent);

        // Encapsulation is meaningless for this
        int balance;
    private:
        void summarize();

    private:
        SegmentTreeNode* left;
        SegmentTreeNode* right;
        SegmentTreeNode* parent;
        int from;
        int to;

        int subtree_from;
        int subtree_to;
    };


    pair<SegmentTreeNode*, int> insert_elementary_interval(SegmentTreeNode* current_node, int from, int to);
    SegmentTreeNode* find_containing_interval(int value);
    pair<SegmentTreeNode*, int> delete_leaf_node(SegmentTreeNode* current_node, SegmentTreeNode* toDelete);

    pair<SegmentTree::SegmentTreeNode*, int> rotate_left(SegmentTreeNode* current_node);
    pair<SegmentTree::SegmentTreeNode*, int> rotate_right(SegmentTreeNode* current_node);

    SegmentTreeNode* root;
};

SegmentTree::SegmentTreeNode::SegmentTreeNode(int from, int to) : from(from), to(to), left(NULL), right(NULL), balance(0)
{
    this->summarize();
}

SegmentTree::SegmentTreeNode::~SegmentTreeNode()
{
    if (this->left != NULL)
    {
        delete this->left;
        this->left = NULL;
    }
    if (this->right != NULL)
    {
        delete this->right;
        this->right = NULL;
    }
}

int SegmentTree::SegmentTreeNode::get_from() const
{
    return this->from;
}

int SegmentTree::SegmentTreeNode::get_to() const
{
    return this->to;
}

void SegmentTree::SegmentTreeNode::set_interval(int from, int to)
{
    this->from = from;
    this->to = to;
    this->summarize();
    if (this->parent != NULL)
    {
        this->parent->summarize();
    }
}

SegmentTree::SegmentTreeNode* SegmentTree::SegmentTreeNode::get_left() const
{
    return this->left;
}

SegmentTree::SegmentTreeNode* SegmentTree::SegmentTreeNode::get_right() const
{
    return this->right;
}

void SegmentTree::SegmentTreeNode::set_left(SegmentTree::SegmentTreeNode* left) 
{
    this->left = left;
    if (this->left != NULL)
    {
        this->left->parent = this;
    }
    this->summarize();
}

void SegmentTree::SegmentTreeNode::set_right(SegmentTree::SegmentTreeNode* right)
{
    this->right = right;
    if (this->right != NULL)
    {
        this->right->parent = this;
    }
    this->summarize();
}

void SegmentTree::SegmentTreeNode::summarize()
{
    this->subtree_from = this->from;
    this->subtree_to = this->to;
}

void SegmentTree::SegmentTreeNode::print(int indent)
{
    for (int i = 0; i < indent; i++)
    {
        cout << " ";
    }
    if (this != NULL)
    {
        cout << "[" << this->from << ", " << this->to << ")" << endl;
        this->left->print(indent + 2);
        this->right->print(indent + 2);
    }
    else
    {
        cout << "(null)" << endl;
    }
}

SegmentTree::SegmentTree() : root(NULL)
{
}

SegmentTree::~SegmentTree()
{
    if (this->root != NULL)
    {
        delete this->root;
        this->root = NULL;
    }
}

void SegmentTree::insert_elementary_interval(int from, int to)
{
    this->root = this->insert_elementary_interval(this->root, from, to).first;
}

pair<SegmentTree::SegmentTreeNode*, int> SegmentTree::insert_elementary_interval(SegmentTree::SegmentTreeNode* current_node, int from, int to)
{
    if (current_node == NULL)
    {
        return pair<SegmentTree::SegmentTreeNode*, int>(new SegmentTree::SegmentTreeNode(from, to), 1);
    }
    else
    {
        if (to <= current_node->get_from())
        {
            pair<SegmentTree::SegmentTreeNode*, int> left_result = insert_elementary_interval(current_node->get_left(), from, to);
            SegmentTree::SegmentTreeNode* left_subtree_root = left_result.first;
            int left_height_change = left_result.second;
            current_node->set_left(left_result.first);
            if (left_height_change == 1)
            {
                int result_height_change = 1;
                current_node->balance += bias_left;
                if (current_node->balance == left_too_heavy)
                {
                    if (left_subtree_root->balance == right_heavy)
                    {
                        pair<SegmentTree::SegmentTreeNode*, int> left_rotation_result = this->rotate_left(left_subtree_root);
                        if (left_rotation_result.second != 0)
                        {
                            throw 1;
                        }
                        current_node->set_left(left_rotation_result.first);
                    }
                    pair<SegmentTree::SegmentTreeNode*, int> left_rotation_result = this->rotate_right(current_node);
                    result_height_change += left_rotation_result.second;
                    current_node = left_rotation_result.first;
                }

                return pair<SegmentTree::SegmentTreeNode*, int>(current_node, result_height_change);
            }
            else
            {
                return pair<SegmentTree::SegmentTreeNode*, int>(current_node, 1);
            }
        }
        else if (from >= current_node->get_to())
        {
            pair<SegmentTree::SegmentTreeNode*, int> right_result = insert_elementary_interval(current_node->get_right(), from, to);
            SegmentTree::SegmentTreeNode* right_subtree_root = right_result.first;
            int right_height_change = right_result.second;
            current_node->set_right(right_result.first);
            if (right_height_change == 1)
            {
                int result_height_change = 1;
                current_node->balance += bias_right;
                if (current_node->balance == right_too_heavy)
                {
                    if (right_subtree_root->balance == left_heavy)
                    {
                        pair<SegmentTree::SegmentTreeNode*, int> right_rotation_result = this->rotate_right(right_subtree_root);
                        if (right_rotation_result.second != 0)
                        {
                            throw 1;
                        }
                        current_node->set_right(right_rotation_result.first);
                    }
                    pair<SegmentTree::SegmentTreeNode*, int> right_rotation_result = this->rotate_left(current_node);
                    result_height_change += right_rotation_result.second;
                    current_node = right_rotation_result.first;
                }

                return pair<SegmentTree::SegmentTreeNode*, int>(current_node, result_height_change);
            }
            else
            {
                return pair<SegmentTree::SegmentTreeNode*, int>(current_node, 1);
            }
        }
        else
        {
            throw 2;
        }
    }
}

void SegmentTree::delete_containing_interval(int value)
{
    // Step 1: Find the containing interval
    SegmentTree::SegmentTreeNode* containing_interval = this->find_containing_interval(value);

    // Step 2: Find the leaf node to delete
    int replace_from;
    int replace_to;
    bool need_replace = false;
    SegmentTree::SegmentTreeNode* leaf_node_to_delete = containing_interval;
    if (containing_interval->get_left() != NULL && containing_interval->get_right() != NULL)
    {
        leaf_node_to_delete = containing_interval->get_right();
        while (leaf_node_to_delete->get_left() != NULL)
        {
            leaf_node_to_delete = leaf_node_to_delete->get_left();
        }
        need_replace = true;
        replace_from = leaf_node_to_delete->get_from();
        replace_to = leaf_node_to_delete->get_to();
    }

    // Step 3: Delete the leaf node recursively
    this->root = this->delete_leaf_node(this->root, leaf_node_to_delete).first;

    // Step 4: Replace values
    if (need_replace)
    {
        containing_interval->set_interval(replace_from, replace_to);
    }
}

pair<SegmentTree::SegmentTreeNode*, int> SegmentTree::delete_leaf_node(SegmentTree::SegmentTreeNode* current_node, SegmentTree::SegmentTreeNode* to_delete)
{
    if (current_node == to_delete)
    {
        delete to_delete;
        return pair<SegmentTree::SegmentTreeNode*, int>(NULL, -1);
    }
    else
    {
        if (to_delete->get_to() <= current_node->get_from())
        {
            // TODO: Rotation!
            current_node->set_left(this->delete_leaf_node(current_node->get_left(), to_delete).first);
            return pair<SegmentTree::SegmentTreeNode*, int>(current_node, -1);
        }
        else if (current_node->get_to() <= to_delete->get_from())
        {
            // TODO: Rotation!
            current_node->set_right(this->delete_leaf_node(current_node->get_right(), to_delete).first);
            return pair<SegmentTree::SegmentTreeNode*, int>(current_node, -1);
        }
        else
        {
            throw 14;
        }
    }
}

/**
* From
*
*   D
* E   B
*    C A
*
* to
*
*    B
*  D   A
* E C
*
*/
pair<SegmentTree::SegmentTreeNode*, int> SegmentTree::rotate_left(SegmentTree::SegmentTreeNode* current_node)
{
    // Step 1: Obtain node references
    SegmentTree::SegmentTreeNode* d = current_node;
    SegmentTree::SegmentTreeNode* b = current_node->get_right();
    if (b == NULL)
    {
        throw 7;
    }
    SegmentTree::SegmentTreeNode* c = b->get_left();

    // Step 2: Setup links
    d->set_right(c);
    b->set_left(d);

    // Step 3: Account for balances and height changes
    //
    // Let the height of d be h
    //
    if (d->balance == right_too_heavy)
    {
        // d was right too heavy
        // Therefore, the height of b was h - 1 (because d was right too heavy)
        //            the height of e was h - 3 (because d was right too heavy)
        if (b->balance == right_heavy)
        {
            // Now we further know 
            // the height of a is h - 2 (b is right heavy)
            // the height of c is h - 3 (b is right heavy)
            // 
            // Therefore, after change
            // d is balance (c and e are both h - 3), and therefore the height of d is h - 2
            // b is balance (a and d are both h - 2), and therefore the height of b is h - 1
            d->balance = balance;
            b->balance = balance;
            return pair<SegmentTree::SegmentTreeNode*, int>(b, -1);
        }
        else if (b->balance == balance)
        {
            // Now we further know 
            // the height of a is h - 2 (b was balance)
            // the height of c is h - 2 (b was balance)
            // 
            // Therefore, after change
            // d is right heavy (c is h - 2 and e is h - 3), and therefore the height of d is h - 1
            // b is left heavy (a is h - 2 and d is h - 1), and therefore the height of b is h
            d->balance = right_heavy;
            b->balance = left_heavy;
            return pair<SegmentTree::SegmentTreeNode*, int>(b, 0);
        }
        else
        {
            throw 8;
        }
    }
    else if (d->balance == right_heavy)
    {
        // d was right heavy
        // Therefore, the height of b was h - 1 (because d was right heavy)
        //            the height of e was h - 2 (because d was right heavy)
        if (b->balance == right_heavy)
        {
            // Now we further know 
            // the height of a is h - 2 (b is right heavy)
            // the height of c is h - 3 (b is right heavy)
            // 
            // Therefore, after change
            // d is left heavy (c is h - 3 and e is h - 2), and therefore the height of d is h - 1
            // b is left heavy (a is h - 2 and d is h - 1), and therefore the height of b is h
            d->balance = left_heavy;
            b->balance = left_heavy;
            return pair<SegmentTree::SegmentTreeNode*, int>(b, 0);
        }
        else if (b->balance == balance)
        {
            // Now we further know 
            // the height of a is h - 2 (b was balance)
            // the height of c is h - 2 (b was balance)
            // 
            // Therefore, after change
            // d is balance (both c and e are h - 2), and therefore the height of d is h - 1
            // b is left heavy (a is h - 2 and d is h - 1), and therefore the height of b is h
            d->balance = balance;
            b->balance = left_heavy;
            return pair<SegmentTree::SegmentTreeNode*, int>(b, 0);
        }
        else
        {
            throw 9;
        }
    }    
    throw 10;
}

/**
* From
*
*    D
*  B   E
* A C
*
* to
*
*   B
* A   D
*    C E
*
*/
pair<SegmentTree::SegmentTreeNode*, int> SegmentTree::rotate_right(SegmentTree::SegmentTreeNode* current_node)
{
    // Step 1: Obtain node references
    SegmentTree::SegmentTreeNode* d = current_node;
    SegmentTree::SegmentTreeNode* b = current_node->get_left();
    if (b == NULL)
    {
        throw 7;
    }
    SegmentTree::SegmentTreeNode* c = b->get_right();

    // Step 2: Setup links
    d->set_left(c);
    b->set_right(d);

    // Step 3: Account for balances and height changes
    //
    // Let the height of d be h
    //
    if (d->balance == left_too_heavy)
    {
        // d was left too heavy
        // Therefore, the height of b was h - 1 (because d was left too heavy)
        //            the height of e was h - 3 (because d was left too heavy)
        if (b->balance == left_heavy)
        {
            // Now we further know 
            // the height of a is h - 2 (b is left heavy)
            // the height of c is h - 3 (b is left heavy)
            // 
            // Therefore, after change
            // d is balance (c and e are both h - 3), and therefore the height of d is h - 2
            // b is balance (a and d are both h - 2), and therefore the height of b is h - 1
            d->balance = balance;
            b->balance = balance;
            return pair<SegmentTree::SegmentTreeNode*, int>(b, -1);
        }
        else if (b->balance == balance)
        {
            // Now we further know 
            // the height of a is h - 2 (b was balance)
            // the height of c is h - 2 (b was balance)
            // 
            // Therefore, after change
            // d is left heavy (c is h - 2 and e is h - 3), and therefore the height of d is h - 1
            // b is right heavy (a is h - 2 and d is h - 1), and therefore the height of b is h
            d->balance = left_heavy;
            b->balance = right_heavy;
            return pair<SegmentTree::SegmentTreeNode*, int>(b, 0);
        }
        else
        {
            throw 8;
        }
    }
    else if (d->balance == left_heavy)
    {
        // d was left heavy
        // Therefore, the height of b was h - 1 (because d was left heavy)
        //            the height of e was h - 2 (because d was left heavy)
        if (b->balance == left_heavy)
        {
            // Now we further know 
            // the height of a is h - 2 (b is left heavy)
            // the height of c is h - 3 (b is left heavy)
            // 
            // Therefore, after change
            // d is right heavy (c is h - 3 and e is h - 2), and therefore the height of d is h - 1
            // b is right heavy (a is h - 2 and d is h - 1), and therefore the height of b is h
            d->balance = right_heavy;
            b->balance = right_heavy;
            return pair<SegmentTree::SegmentTreeNode*, int>(b, 0);
        }
        else if (b->balance == balance)
        {
            // Now we further know 
            // the height of a is h - 2 (b was balance)
            // the height of c is h - 2 (b was balance)
            // 
            // Therefore, after change
            // d is balance (both c and e are h - 2), and therefore the height of d is h - 1
            // b is right heavy (a is h - 2 and d is h - 1), and therefore the height of b is h
            d->balance = balance;
            b->balance = right_heavy;
            return pair<SegmentTree::SegmentTreeNode*, int>(b, 0);
        }
        else
        {
            throw 9;
        }
    }    
    throw 10;
}

SegmentTree::SegmentTreeNode* SegmentTree::find_containing_interval(int value)
{
    if (this->root == NULL)
    {
        throw 11;
    }
    SegmentTree::SegmentTreeNode* cursor = root;
    while (true)
    {
        if (cursor == NULL)
        {
            throw 12;
        }
        if (cursor->get_from() <= value && value < cursor->get_to())
        {
            return cursor;
        }
        else if (value < cursor->get_from())
        {
            cursor = cursor->get_left();
        }
        else 
        {
            if (value < cursor->get_to())
            {
                throw 13;
            }
            cursor = cursor->get_right();
        }
    }
}

void SegmentTree::print()
{
    this->root->print(0);
}

int SPOJ_LITE()
{
    SegmentTree tree;
    tree.insert_elementary_interval(1, 5);
    tree.insert_elementary_interval(10, 15);
    tree.insert_elementary_interval(5, 10);
    tree.delete_containing_interval(7);

    tree.print();
    return 0;
}