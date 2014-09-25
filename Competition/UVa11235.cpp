#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=2176

#include "UVa11235.h"

#include <iostream>
#include <list>
#include <map>
#include <algorithm>

using namespace std;

struct interval_tree_node
{
    int from;
    int to;
    int answer; /* the frequency of the most frequent number in the interval */
    interval_tree_node* left;
    interval_tree_node* right;

    interval_tree_node(int from, int to, int answer) : from(from), to(to), answer(answer), left(NULL), right(NULL) {

    }

    ~interval_tree_node()
    {
        if (this->left != NULL)
        {
            delete this->left;
        }
        if (this->right != NULL)
        {
            delete this->right;
        }
    }
};

int process_query(interval_tree_node* node, int query_from, int query_to)
{
    if (node->from == query_from && node->to == query_to)
    {
        return node->answer;
    }
    else
    {
        if (node->left == NULL)
        {
            // I am at a leaf node now - the best answer is just the input range
            return query_to - query_from;
        }
        else
        {
            int left_answer = process_query(node->left, max(node->left->from, query_from), min(node->left->to, query_to));
            int right_answer = process_query(node->right, max(node->right->from, query_from), min(node->right->to, query_to));
            return max(left_answer, right_answer);
        }
    }
}

int UVa11235()
{
    int number_of_values, number_of_queries;
    cin >> number_of_values;
    cin >> number_of_queries;
    list<interval_tree_node*> ranges;

    // Step 1: Read the input as ranges
    bool first = true;
    int last = -1;
    int last_index = 0;
    for (int i = 0; i < number_of_values; i++)
    {
        int current_value;
        cin >> current_value;
        if (first)
        {
            first = false;
        }
        else
        {
            if (last != current_value)
            {
                ranges.push_back(new interval_tree_node(last_index, i, (i - last_index)));
                last_index = i;
            }
        }
        last = current_value;
    }

    ranges.push_back(new interval_tree_node(last_index, number_of_values, (number_of_values - last_index)));

    // Step 2: Build the tree
    list<interval_tree_node*> empty_list;

    list<interval_tree_node*>* layer_below = &ranges;
    list<interval_tree_node*>* layer_above = &empty_list;

    while (layer_below->size() > 1)
    {
        interval_tree_node* left = NULL;
        interval_tree_node* right = NULL;
        for (list<interval_tree_node*>::iterator ii = layer_below->begin(); ii != layer_below->end(); ii++)
        {
            if (left == NULL)
            {
                left = *ii;
            }
            else
            {
                // Step 2.1: Any two nodes in the bottom layer has a parent node
                right = *ii;
                interval_tree_node* parent = new interval_tree_node(left->from, right->to, max(left->answer, right->answer));
                parent->left = left;
                parent->right = right;
                left = right = NULL;
                layer_above->push_back(parent);
            }
        }
        if (left != NULL)
        {
            // Step 2.2: The orphan last node will be made to the parent layer
            layer_above->push_back(left);
        }

        // Step 2.3: Swap the role of above and below to reuse the list
        list<interval_tree_node*>* temp = layer_below;
        layer_below = layer_above;
        layer_above = temp;

        // Step 2.4: Prepare for the next iteration, above should be empty
        layer_above->clear();
    }

    interval_tree_node* root = *(layer_below->begin());

    for (int i = 0; i < number_of_queries; i++)
    {
        int query_from;
        int query_to;
        cin >> query_from;
        cin >> query_to;
        cout << process_query(root, query_from, query_to) << endl;
    }

    int zero;
    cin >> zero; // The meaningless zero input

    delete root;

    return 0;
}
