#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2272

#include "UVa11297.h"

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct QuadTreeNode
{
    QuadTreeNode* upper_left;
    QuadTreeNode* upper_right;
    QuadTreeNode* lower_left;
    QuadTreeNode* lower_right;
    int left_x;
    int upper_y;
    int right_x;
    int lower_y;
    int max;
    int min;

    QuadTreeNode()
    {
        this->upper_left = NULL;
        this->upper_right = NULL;
        this->lower_left = NULL;
        this->lower_right = NULL;
    }

    ~QuadTreeNode()
    {
        if (this->upper_left != NULL) { delete this->upper_left; }
        if (this->upper_right != NULL) { delete this->upper_right; }
        if (this->lower_left != NULL) { delete this->lower_left; }
        if (this->lower_right != NULL) { delete this->lower_right; }
    }
};

void build_quad_tree(QuadTreeNode* node, int** population)
{
    bool split_x = node->right_x - node->left_x > 1;
    bool split_y = node->lower_y - node->upper_y > 1;

    if (split_x && split_y)
    {
        int mid_x = (node->right_x + node->left_x) / 2;
        int mid_y = (node->upper_y + node->lower_y) / 2;
        node->upper_left = new QuadTreeNode();
        node->upper_left->left_x = node->left_x;
        node->upper_left->upper_y = node->upper_y;
        node->upper_left->right_x = mid_x;
        node->upper_left->lower_y = mid_y;
        build_quad_tree(node->upper_left, population);
        node->upper_right = new QuadTreeNode();
        node->upper_right->left_x = mid_x;
        node->upper_right->upper_y = node->upper_y;
        node->upper_right->right_x = node->right_x;
        node->upper_right->lower_y = mid_y;
        build_quad_tree(node->upper_right, population);
        node->lower_left = new QuadTreeNode();
        node->lower_left->left_x = node->left_x;
        node->lower_left->upper_y = mid_y;
        node->lower_left->right_x = mid_x;
        node->lower_left->lower_y = node->lower_y;
        build_quad_tree(node->lower_left, population);
        node->lower_right = new QuadTreeNode();
        node->lower_right->left_x = mid_x;
        node->lower_right->upper_y = mid_y;
        node->lower_right->right_x = node->right_x;
        node->lower_right->lower_y = node->lower_y;
        build_quad_tree(node->lower_right, population);
        node->min = min(node->upper_left->min, min(node->upper_right->min, min(node->lower_left->min, node->lower_right->min)));
        node->max = max(node->upper_left->max, max(node->upper_right->max, max(node->lower_left->max, node->lower_right->max)));
    }
    else if (split_x)
    {
        int mid_x = (node->right_x + node->left_x) / 2;
        node->upper_left = new QuadTreeNode();
        node->upper_left->left_x = node->left_x;
        node->upper_left->upper_y = node->upper_y;
        node->upper_left->right_x = mid_x;
        node->upper_left->lower_y = node->lower_y;
        build_quad_tree(node->upper_left, population);
        node->upper_right = new QuadTreeNode();
        node->upper_right->left_x = mid_x;
        node->upper_right->upper_y = node->upper_y;
        node->upper_right->right_x = node->right_x;
        node->upper_right->lower_y = node->lower_y;
        build_quad_tree(node->upper_right, population);
        node->min = min(node->upper_left->min, node->upper_right->min);
        node->max = max(node->upper_left->max, node->upper_right->max);
    }
    else if (split_y)
    {
        int mid_y = (node->upper_y + node->lower_y) / 2;
        node->upper_left = new QuadTreeNode();
        node->upper_left->left_x = node->left_x;
        node->upper_left->upper_y = node->upper_y;
        node->upper_left->right_x = node->right_x;
        node->upper_left->lower_y = mid_y;
        build_quad_tree(node->upper_left, population);
        node->lower_left = new QuadTreeNode();
        node->lower_left->left_x = node->left_x;
        node->lower_left->upper_y = mid_y;
        node->lower_left->right_x = node->right_x;
        node->lower_left->lower_y = node->lower_y;
        build_quad_tree(node->lower_left, population);
        node->min = min(node->upper_left->min, node->lower_left->min);
        node->max = max(node->upper_left->max, node->lower_left->max);
    }
    else
    {
        node->min = node->max = population[node->left_x][node->upper_y];
    }
}

void print_tree(QuadTreeNode* node, int indent)
{
    if (node != NULL)
    {
        for (int i = 0; i < indent; i++)
        {
            cout << " ";
        }
        cout << "(" << node->left_x << ", " << node->upper_y << ") - (" << node->right_x << ", " << node->lower_y << ") has min = " << node->min << ", max = " << node->max << endl;
        print_tree(node->upper_left, indent + 1);
        print_tree(node->upper_right, indent + 1);
        print_tree(node->lower_left, indent + 1);
        print_tree(node->lower_right, indent + 1);
    }
}

void query_tree(QuadTreeNode* node, int x1, int y1, int x2, int y2, int& minValue, int& maxValue)
{
    if (node->left_x == x1 && node->right_x == x2 && node->upper_y == y1 && node->lower_y == y2)
    {
        minValue = node->min;
        maxValue = node->max;
    }
    else
    {
        bool candidateAssigned = false;
        int minCandidate;
        int maxCandidate;
        if (node->upper_left != NULL)
        {
            int upper_left_x1 = max(x1, node->upper_left->left_x);
            int upper_left_x2 = min(x2, node->upper_left->right_x);
            int upper_left_y1 = max(y1, node->upper_left->upper_y);
            int upper_left_y2 = min(y2, node->upper_left->lower_y);
            if ((upper_left_x2 - upper_left_x1 > 0) && (upper_left_y2 - upper_left_y1 > 0))
            {
                int localMin, localMax;
                query_tree(node->upper_left, upper_left_x1, upper_left_y1 ,upper_left_x2, upper_left_y2, localMin, localMax);
                if (candidateAssigned)
                {
                    minCandidate = min(localMin, minCandidate);
                    maxCandidate = max(localMax, maxCandidate);
                }
                else 
                {
                    minCandidate = localMin;
                    maxCandidate = localMax;
                    candidateAssigned = true;
                }
            }
        }
        if (node->upper_right != NULL)
        {
            int upper_right_x1 = max(x1, node->upper_right->left_x);
            int upper_right_x2 = min(x2, node->upper_right->right_x);
            int upper_right_y1 = max(y1, node->upper_right->upper_y);
            int upper_right_y2 = min(y2, node->upper_right->lower_y);
            if ((upper_right_x2 - upper_right_x1 > 0) && (upper_right_y2 - upper_right_y1 > 0))
            {
                int localMin, localMax;
                query_tree(node->upper_right, upper_right_x1, upper_right_y1 ,upper_right_x2, upper_right_y2, localMin, localMax);
                if (candidateAssigned)
                {
                    minCandidate = min(localMin, minCandidate);
                    maxCandidate = max(localMax, maxCandidate);
                }
                else 
                {
                    minCandidate = localMin;
                    maxCandidate = localMax;
                    candidateAssigned = true;
                }
            }
        }
        if (node->lower_left != NULL)
        {
            int lower_left_x1 = max(x1, node->lower_left->left_x);
            int lower_left_x2 = min(x2, node->lower_left->right_x);
            int lower_left_y1 = max(y1, node->lower_left->upper_y);
            int lower_left_y2 = min(y2, node->lower_left->lower_y);
            if ((lower_left_x2 - lower_left_x1 > 0) && (lower_left_y2 - lower_left_y1 > 0))
            {
                int localMin, localMax;
                query_tree(node->lower_left, lower_left_x1, lower_left_y1 ,lower_left_x2, lower_left_y2, localMin, localMax);
                if (candidateAssigned)
                {
                    minCandidate = min(localMin, minCandidate);
                    maxCandidate = max(localMax, maxCandidate);
                }
                else 
                {
                    minCandidate = localMin;
                    maxCandidate = localMax;
                    candidateAssigned = true;
                }
            }
        }
        if (node->lower_right != NULL)
        {
            int lower_right_x1 = max(x1, node->lower_right->left_x);
            int lower_right_x2 = min(x2, node->lower_right->right_x);
            int lower_right_y1 = max(y1, node->lower_right->upper_y);
            int lower_right_y2 = min(y2, node->lower_right->lower_y);
            if ((lower_right_x2 - lower_right_x1 > 0) && (lower_right_y2 - lower_right_y1 > 0))
            {
                int localMin, localMax;
                query_tree(node->lower_right, lower_right_x1, lower_right_y1 ,lower_right_x2, lower_right_y2, localMin, localMax);
                if (candidateAssigned)
                {
                    minCandidate = min(localMin, minCandidate);
                    maxCandidate = max(localMax, maxCandidate);
                }
                else 
                {
                    minCandidate = localMin;
                    maxCandidate = localMax;
                    candidateAssigned = true;
                }
            }
        }
        if (candidateAssigned)
        {
            minValue = minCandidate;
            maxValue = maxCandidate;
        }
        else
        {
            minValue = node->min;
            maxValue = node->max;
        }
    }
}

void update_tree(QuadTreeNode* node, int x, int y, int v)
{
    // cout << "update_tree (" << node->left_x <<", " << node->upper_y << ") - (" << node->right_x << ", " << node->lower_y << ")" << endl;
    if (node->upper_left != NULL)
    {
        if (node->upper_left->left_x <= x && x < node->upper_left->right_x && node->upper_left->upper_y <= y && y < node->upper_left->lower_y)
        {
            update_tree(node->upper_left, x, y, v);
        }
    }
    if (node->upper_right != NULL)
    {
        if (node->upper_right->left_x <= x && x < node->upper_right->right_x && node->upper_right->upper_y <= y && y < node->upper_right->lower_y)
        {
            update_tree(node->upper_right, x, y, v);
        }
    }
    if (node->lower_left != NULL)
    {
        if (node->lower_left->left_x <= x && x < node->lower_left->right_x && node->lower_left->upper_y <= y && y < node->lower_left->lower_y)
        {
            update_tree(node->lower_left, x, y, v);
        }
    }
    if (node->lower_right != NULL)
    {
        if (node->lower_right->left_x <= x && x < node->lower_right->right_x && node->lower_right->upper_y <= y && y < node->lower_right->lower_y)
        {
            update_tree(node->lower_right, x, y, v);
        }
    }
    bool candidateAssigned = false;
    int minCandidate;
    int maxCandidate;
    if (node->upper_left != NULL)
    {
        if (candidateAssigned)
        {
            minCandidate = min(node->upper_left->min, minCandidate);
            maxCandidate = max(node->upper_left->max, maxCandidate);
        }
        else
        {
            minCandidate = node->upper_left->min;
            maxCandidate = node->upper_left->max;
            candidateAssigned = true;
        }
    }
    if (node->upper_right != NULL)
    {
        if (candidateAssigned)
        {
            minCandidate = min(node->upper_right->min, minCandidate);
            maxCandidate = max(node->upper_right->max, maxCandidate);
        }
        else
        {
            minCandidate = node->upper_right->min;
            maxCandidate = node->upper_right->max;
            candidateAssigned = true;
        }
    }
    if (node->lower_left != NULL)
    {
        if (candidateAssigned)
        {
            minCandidate = min(node->lower_left->min, minCandidate);
            maxCandidate = max(node->lower_left->max, maxCandidate);
        }
        else
        {
            minCandidate = node->lower_left->min;
            maxCandidate = node->lower_left->max;
            candidateAssigned = true;
        }
    }
    if (node->lower_right != NULL)
    {
        if (candidateAssigned)
        {
            minCandidate = min(node->lower_right->min, minCandidate);
            maxCandidate = max(node->lower_right->max, maxCandidate);
        }
        else
        {
            minCandidate = node->lower_right->min;
            maxCandidate = node->lower_right->max;
            candidateAssigned = true;
        }
    }
    if (candidateAssigned)
    {
        node->min = minCandidate;
        node->max = maxCandidate;
    }
    else
    {
        node->min = node->max = v;
    }
}

int UVa11297()
{
    int num_rows, num_cols;
    int** populations;
    cin >> num_rows;
    cin >> num_cols;
    // Step 1: Allocate the 2D array
    populations = new int*[num_cols];
    for (int i = 0; i < num_cols; i++)
    {
        populations[i] = new int[num_rows];
    }
    // Step 2: Perform the input
    for (int i = 0; i < num_rows; i++)
    {
        for (int j = 0; j < num_cols; j++)
        {
            cin >> populations[j][i];
        }
    }

    // Step 3: Build Quad Tree
    QuadTreeNode* root = new QuadTreeNode();
    root->left_x = 0;
    root->upper_y = 0;
    root->right_x = num_cols;
    root->lower_y = num_rows;
    build_quad_tree(root, populations);
    // print_tree(root, 0);

    // Step 4: Perform queries
    int number_of_queries;
    cin >> number_of_queries;
    for (int q = 0; q < number_of_queries; q++)
    {
        char query_type;
        cin >> query_type;
        if (query_type == 'q')
        {
            int row1, col1, row2, col2;
            cin >> row1;
            cin >> col1;
            cin >> row2;
            cin >> col2;
            // Change coordinate to zero based index, with right/lower side exclusive
            int x1 = col1 - 1;
            int y1 = row1 - 1;
            int x2 = col2;
            int y2 = row2;
            int min, max;
            query_tree(root, x1, y1, x2, y2, min, max);
            cout << max << " " << min << endl;
        }
        else if (query_type == 'c')
        {
            int row, col, v;
            cin >> row;
            cin >> col;
            cin >> v;
            row--;
            col--;
            update_tree(root, col, row, v);
            // print_tree(root, 0);
        }
    }

    delete root;
    return 0;
}