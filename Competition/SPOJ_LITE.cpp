#include "stdafx.h"

// http://www.spoj.com/problems/LITE/

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

const int intMin = -2147483647;
const int intMax = 2147483647;

class SegmentTree
{
public:
    SegmentTree();
    ~SegmentTree();
    void insert_interval(int from, int to);
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

        // Summaries for sub-tree
        int subtree_from;
        int subtree_to;
        int finite_segment_count;
        int even_segment_length;
        int odd_segment_length;
    };

    void insert_elementary_interval(int from, int to);
    void delete_elementary_interval(SegmentTreeNode* interval_to_delete);
    void split_elementary_interval(SegmentTree::SegmentTreeNode* interval_to_split, int splitting_value);
    pair<SegmentTreeNode*, int> insert_elementary_interval(SegmentTreeNode* current_node, int from, int to);
    SegmentTreeNode* find_containing_interval(int value);
    pair<SegmentTreeNode*, int> delete_easy_node(SegmentTreeNode* current_node, SegmentTreeNode* toDelete);

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
    // Since we need to delete a node without releasing the whole tree
    // Deletion of the left/right subtrees is left to the tree itself
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
    this->subtree_from = this->left == NULL ? this->from : this->left->subtree_from;
    this->subtree_to = this->right == NULL ? this->to : this->right->subtree_to;

    if (this->from == intMin || this->to == intMax)
    {
        this->finite_segment_count = 0;
    }
    else
    {
        this->finite_segment_count = 1;
        if (this->left != NULL)
        {
            this->finite_segment_count += this->left->finite_segment_count;
        }
        if (this->right != NULL)
        {
            this->finite_segment_count += this->right->finite_segment_count;
        }
    }

    bool middle_is_even = true;
    this->even_segment_length = 0;
    if (this->left != NULL)
    {
        this->even_segment_length += this->left->even_segment_length;
        this->odd_segment_length += this->left->odd_segment_length;
        middle_is_even = this->left->finite_segment_count % 2 == 0;
    }
    if (middle_is_even)
    {
        this->even_segment_length += this->to - this->from;
    }
    else 
    {
        this->odd_segment_length += this->to - this->from;
    }
    if (this->right != NULL)
    {
        if (middle_is_even)
        {
            this->odd_segment_length += this->right->even_segment_length;
            this->even_segment_length += this->right->odd_segment_length;
        }
        else
        {
            this->even_segment_length += this->right->even_segment_length;
            this->odd_segment_length += this->right->odd_segment_length;
        }
    }
}

void SegmentTree::SegmentTreeNode::print(int indent)
{
    for (int i = 0; i < indent; i++)
    {
        cout << " ";
    }
    if (this != NULL)
    {
        cout << "[" << this->from << ", " << this->to << ")" << " has balance " << this->balance << " covering [" << this->subtree_from << ", " << this->subtree_to << ") with " << this->finite_segment_count << " finite segments" << endl;
        this->left->print(indent + 2);
        this->right->print(indent + 2);
    }
    else
    {
        cout << "(null)" << endl;
    }
}

SegmentTree::SegmentTree()
{
    // TODO: replace these values with actual infinity
    this->root = new SegmentTreeNode(intMin, intMax);
}

SegmentTree::~SegmentTree()
{
    // TODO: Delete the whole tree!
    if (this->root != NULL)
    {
        delete this->root;
        this->root = NULL;
    }
}

void SegmentTree::insert_interval(int from, int to)
{
    // TODO: Fix the assumption that the endpoints is disjoint
    SegmentTree::SegmentTreeNode* from_containing_interval = this->find_containing_interval(from);
    this->split_elementary_interval(from_containing_interval, from);
    SegmentTree::SegmentTreeNode* to_containing_interval = this->find_containing_interval(to);
    this->split_elementary_interval(to_containing_interval, to);
}

void SegmentTree::split_elementary_interval(SegmentTree::SegmentTreeNode* interval_to_split, int splitting_value)
{
    int from = interval_to_split->get_from();
    int to = interval_to_split->get_to();
    cout << "---------------------------------" << endl;
    cout << "delete [" << interval_to_split->get_from() << ", " << interval_to_split->get_to() << ")" << endl;
    this->delete_elementary_interval(interval_to_split);
    this->print();
    cout << "---------------------------------" << endl;
    cout << "insert [" << from << ", " << splitting_value << ")" << endl;
    this->insert_elementary_interval(from, splitting_value);
    this->print();
    cout << "---------------------------------" << endl;
    cout << "insert [" << splitting_value << ", " << to << ")" << endl;
    this->insert_elementary_interval(splitting_value, to);
    this->print();
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
            pair<SegmentTree::SegmentTreeNode*, int> left_insertion_result = insert_elementary_interval(current_node->get_left(), from, to);
            SegmentTree::SegmentTreeNode* left_subtree_root = left_insertion_result.first;
            int left_height_change = left_insertion_result.second;
            current_node->set_left(left_subtree_root);
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
                if (left_height_change != 0)
                {
                    throw 15;
                }

                return pair<SegmentTree::SegmentTreeNode*, int>(current_node, 0);
            }
        }
        else if (from >= current_node->get_to())
        {
            pair<SegmentTree::SegmentTreeNode*, int> right_insertion_result = insert_elementary_interval(current_node->get_right(), from, to);
            SegmentTree::SegmentTreeNode* right_subtree_root = right_insertion_result.first;
            int right_height_change = right_insertion_result.second;
            current_node->set_right(right_subtree_root);
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
                if (right_height_change != 0)
                {
                    throw 15;
                }

                return pair<SegmentTree::SegmentTreeNode*, int>(current_node, 0);
            }
        }
        else
        {
            throw 2;
        }
    }
}

void SegmentTree::delete_elementary_interval(SegmentTree::SegmentTreeNode* interval_to_delete)
{
    // Step 1: Find the leaf node to delete
    int replace_from;
    int replace_to;
    bool need_replace = false;
    SegmentTree::SegmentTreeNode* leaf_node_to_delete = interval_to_delete;
    if (interval_to_delete->get_left() != NULL && interval_to_delete->get_right() != NULL)
    {
        leaf_node_to_delete = interval_to_delete->get_right();
        while (leaf_node_to_delete->get_left() != NULL)
        {
            leaf_node_to_delete = leaf_node_to_delete->get_left();
        }
        need_replace = true;
        replace_from = leaf_node_to_delete->get_from();
        replace_to = leaf_node_to_delete->get_to();
    }

    // Step 2: Delete the node without two children recursively
    this->root = this->delete_easy_node(this->root, leaf_node_to_delete).first;

    // Step 3: Replace values
    if (need_replace)
    {
        interval_to_delete->set_interval(replace_from, replace_to);
    }
}

pair<SegmentTree::SegmentTreeNode*, int> SegmentTree::delete_easy_node(SegmentTree::SegmentTreeNode* current_node, SegmentTree::SegmentTreeNode* to_delete)
{
    if (current_node == to_delete)
    {
        SegmentTree::SegmentTreeNode* next = to_delete->get_left();
        if (next == NULL)
        {
            next = to_delete->get_right();
        }
        delete to_delete;
        return pair<SegmentTree::SegmentTreeNode*, int>(next, -1);
    }
    else
    {
        if (to_delete->get_to() <= current_node->get_from())
        {
            pair<SegmentTree::SegmentTreeNode*, int> left_deletion_result = this->delete_easy_node(current_node->get_left(), to_delete);
            SegmentTree::SegmentTreeNode* left_subtree_root = left_deletion_result.first;
            int left_height_change = left_deletion_result.second;
            current_node->set_left(left_subtree_root);
            if (left_height_change == -1)
            {
                int result_height_change = -1;
                current_node->balance -= bias_left;
                if (current_node->balance == right_too_heavy)
                {
                    if (left_subtree_root->balance == left_heavy)
                    {
                        pair<SegmentTree::SegmentTreeNode*, int> right_rotation_result = this->rotate_right(left_subtree_root);
                        if (right_rotation_result.second != 0)
                        {
                            throw 1;
                        }
                        current_node->set_left(right_rotation_result.first);
                    }
                    pair<SegmentTree::SegmentTreeNode*, int> right_rotation_result = this->rotate_left(current_node);
                    result_height_change += right_rotation_result.second;
                    current_node = right_rotation_result.first;
                }

                return pair<SegmentTree::SegmentTreeNode*, int>(current_node, result_height_change);
            }
            else
            {
                if (left_height_change != 0)
                {
                    throw 15;
                }

                return pair<SegmentTree::SegmentTreeNode*, int>(current_node, 0);
            }
        }
        else if (current_node->get_to() <= to_delete->get_from())
        {
            pair<SegmentTree::SegmentTreeNode*, int> right_deletion_result = this->delete_easy_node(current_node->get_right(), to_delete);
            SegmentTree::SegmentTreeNode* right_subtree_root = right_deletion_result.first;
            int right_height_change = right_deletion_result.second;
            current_node->set_right(right_subtree_root);
            if (right_height_change == -1)
            {
                int result_height_change = -1;
                current_node->balance -= bias_right;
                if (current_node->balance == left_too_heavy)
                {
                    if (right_subtree_root->balance == right_heavy)
                    {
                        pair<SegmentTree::SegmentTreeNode*, int> left_rotation_result = this->rotate_left(right_subtree_root);
                        if (left_rotation_result.second != 0)
                        {
                            throw 1;
                        }
                        current_node->set_right(left_rotation_result.first);
                    }
                    pair<SegmentTree::SegmentTreeNode*, int> left_rotation_result = this->rotate_right(current_node);
                    result_height_change += left_rotation_result.second;
                    current_node = left_rotation_result.first;
                }

                return pair<SegmentTree::SegmentTreeNode*, int>(current_node, result_height_change);
            }
            else
            {
                if (right_height_change != 0)
                {
                    throw 15;
                }

                return pair<SegmentTree::SegmentTreeNode*, int>(current_node, 0);
            }
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
    tree.insert_interval(1, 5);
    tree.insert_interval(3, 7);

    return 0;
}