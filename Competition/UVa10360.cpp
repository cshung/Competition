#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1301

#include "UVa10360.h"

#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>

using namespace std;

struct rat_population
{
    int x;
    int y;
    int size;
};

struct kdtree_node
{
    bool by_x;
    bool is_leaf;
    double split_value;
    rat_population* data;
    kdtree_node* left;
    kdtree_node* right;
    kdtree_node() : left(NULL), right(NULL), data(NULL), is_leaf(false)
    {
    }
    ~kdtree_node()
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

bool sort_by_x(rat_population* first, rat_population* second)
{
    return first->x * 10000 + first->y < second->x * 10000 + second->y;
}

bool sort_by_y(rat_population* first, rat_population* second)
{
    return first->y * 10000 + first->x < second->y * 10000 + second->x;
}

kdtree_node* build(vector<rat_population*> x_sorted, vector<rat_population*> y_sorted, bool by_x)
{
    kdtree_node* result = new kdtree_node();
    int num_points = x_sorted.size();        
    double median_x;
    double median_y;
    int half = num_points / 2;

    if (num_points == 0)
    {
        result->is_leaf = true;
    }
    else if (num_points == 1)
    {
        result->is_leaf = true;
        result->data = x_sorted[0];
    }
    else 
    {
        if (by_x)
        {
            if (num_points % 2 == 0)
            {
                median_x = (x_sorted[half - 1]->x + x_sorted[half]->x) / 2.0;
                median_y = (x_sorted[half - 1]->y + x_sorted[half]->y) / 2.0;
            }
            else
            {
                median_x = x_sorted[half]->x;
                median_y = x_sorted[half]->y;
            }
            result->split_value = median_x;
            result->by_x = true;
            vector<rat_population*> left_x_sorted;
            vector<rat_population*> right_x_sorted;
            vector<rat_population*> left_y_sorted;
            vector<rat_population*> right_y_sorted;
            for (vector<rat_population*>::iterator i = x_sorted.begin(); i != x_sorted.end(); i++)
            {
                rat_population* current = *i;
                if (current->x < median_x)
                {
                    left_x_sorted.push_back(current);
                }
                else if (current->x == median_x && current->y < median_y)
                {
                    left_x_sorted.push_back(current);
                }
                else
                {
                    right_x_sorted.push_back(current);
                }
            }
            for (vector<rat_population*>::iterator i = y_sorted.begin(); i != y_sorted.end(); i++)
            {
                rat_population* current = *i;
                if (current->x < median_x)
                {
                    left_y_sorted.push_back(current);
                }
                else if (current->x == median_x && current->y < median_y)
                {
                    left_y_sorted.push_back(current);
                }
                else
                {
                    right_y_sorted.push_back(current);
                }
            }
            result->left = build(left_x_sorted, left_y_sorted, false);
            result->right = build(right_x_sorted, right_y_sorted, false);
        }
        else
        {
            if (num_points % 2 == 0)
            {
                median_y = (y_sorted[half - 1]->y + y_sorted[half]->y) / 2.0;
                median_x = (y_sorted[half - 1]->x + y_sorted[half]->x) / 2.0;
            }
            else
            {
                median_y = y_sorted[half]->y;
                median_x = y_sorted[half]->x;
            }
            result->split_value = median_y;
            result->by_x = false;
            vector<rat_population*> left_x_sorted;
            vector<rat_population*> right_x_sorted;
            vector<rat_population*> left_y_sorted;
            vector<rat_population*> right_y_sorted;
            for (vector<rat_population*>::iterator i = x_sorted.begin(); i != x_sorted.end(); i++)
            {
                rat_population* current = *i;
                if (current->y < median_y)
                {
                    left_x_sorted.push_back(current);
                }
                else if (current->y == median_y && current->x < median_x)
                {
                    left_x_sorted.push_back(current);
                }
                else
                {
                    right_x_sorted.push_back(current);
                }
            }
            for (vector<rat_population*>::iterator i = y_sorted.begin(); i != y_sorted.end(); i++)
            {
                rat_population* current = *i;
                if (current->y < median_y)
                {
                    left_y_sorted.push_back(current);
                }
                else if (current->y == median_y && current->x < median_x)
                {
                    left_y_sorted.push_back(current);
                }
                else
                {
                    right_y_sorted.push_back(current);
                }
            }
            result->left = build(left_x_sorted, left_y_sorted, true);
            result->right = build(right_x_sorted, right_y_sorted, true);
        }
    }

    return result;
}

void print_tree(kdtree_node* root, int indent)
{
    for (int i = 0; i < indent; i++)
    {
        cout << " ";
    }
    if (root->data)
    {
        cout << "Leaf: (" << root->data->x << ", " << root->data->y << ")" << root->data->size << endl;
    }
    else
    {
        if (root->by_x)
        {
            cout << "Split by X: " << root->split_value << endl;
            print_tree(root->left, indent + 1);
            print_tree(root->right, indent + 1);
        }
        else
        {
            cout << "Split by Y: " << root->split_value << endl;
            print_tree(root->left, indent + 1);
            print_tree(root->right, indent + 1);
        }
    }
}

int count(kdtree_node* node)
{
    if (node->is_leaf)
    {
        if (node->data != NULL)
        {
            return node->data->size;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return count(node->left) + count(node->right);
    }
}

int count(kdtree_node* node, int qMinX, int qMinY, int qMaxX, int qMaxY, int bMinX, int bMinY, int bMaxX, int bMaxY)
{
    // Case 0: The node is a leaf node
    if (node->is_leaf)
    {
        if (node->data != NULL)
        {
            if (qMinX <= node->data->x &&node->data->x <= qMaxX && qMinY <= node->data->y &&node->data->y <= qMaxY)
            {
                return node->data->size;
            }
            else
            {
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }

    // Case 1: The query region completely includes the bounding box of the current node
    if (qMinX <= bMinX && qMinY <= bMinY && qMaxX >= bMaxX && qMaxY >= bMaxY)
    {
        return count(node);
    }

    // These value matter only if node->split_value is not an integer
    // When split_value is treated as inclusive upper bound, it should be round down (e.g the set of integers less    than or equal to 1.5 is the same set of integer less    than or equals to 1)
    // When split_value is treated as inclusive lower bound, it should be round up   (e.g the set of integers greater than or equal to 1.5 is the same set of integer greater than or equals to 2)
    int split_lower = (int)node->split_value; 
    int split_upper = (int)(node->split_value + 0.5);

    if (node->by_x)
    {
        if (qMaxX <= split_lower)
        {
            return count(node->left, qMinX, qMinY, qMaxX, qMaxY, bMinX, bMinY, split_lower, bMaxY);
        }
        else if (qMinX >= split_upper)
        {
            return count(node->right, qMinX, qMinY, qMaxX, qMaxY, split_upper, bMinY, bMaxX, bMaxY);
        }
        else 
        {
            int leftCount = count(node->left, qMinX, qMinY, qMaxX, qMaxY, bMinX, bMinY, split_lower, bMaxY);
            int rightCount = count(node->right, qMinX, qMinY, qMaxX, qMaxY, split_upper, bMinY, bMaxX, bMaxY);
            return leftCount + rightCount;
        }
    }
    else 
    {
        if (qMaxY <= split_lower)
        {
            return count(node->left, qMinX, qMinY, qMaxX, qMaxY, bMinX, bMinY, bMaxX, split_lower);
        }
        else if (qMinY >= split_upper)
        {
            return count(node->right, qMinX, qMinY, qMaxX, qMaxY, bMinX, split_upper, bMaxX, bMaxY);
        }
        else
        {
            int leftCount = count(node->left, qMinX, qMinY, qMaxX, qMaxY, bMinX, bMinY, bMaxX, split_lower);
            int rightCount = count(node->right, qMinX, qMinY, qMaxX, qMaxY, bMinX, split_upper, bMaxX, bMaxY);
            return leftCount + rightCount;
        }
    }

}

int count(kdtree_node* root, int minX, int minY, int maxX, int maxY)
{
    return count(root, minX, minY, maxX, maxY, 0, 0, 1024, 1024);
}

int UVa10360()
{
    int number_of_cases;
    cin >> number_of_cases;
    for (int c = 0; c < number_of_cases; c++)
    {
        // Step 1: Read input
        int strength;
        cin >> strength;
        int num_rat_populations;
        cin >> num_rat_populations;
        list<rat_population*> rat_populations;
        for (int p = 0; p < num_rat_populations; p++)
        {
            rat_population* current_line = new rat_population();
            cin >> current_line->x;
            cin >> current_line->y;
            cin >> current_line->size;
            rat_populations.push_back(current_line);
        }

        // Step 2: Build a spatial index using kd-tree
        vector<rat_population*> x_sorted_rat_populations;
        vector<rat_population*> y_sorted_rat_populations;

        // Step 2.1: Pre-sort the points
        for (list<rat_population*>::iterator ri = rat_populations.begin(); ri != rat_populations.end(); ri++)
        {
            x_sorted_rat_populations.push_back(*ri);
            y_sorted_rat_populations.push_back(*ri);
        }
        sort(x_sorted_rat_populations.begin(), x_sorted_rat_populations.end(), sort_by_x);
        sort(y_sorted_rat_populations.begin(), y_sorted_rat_populations.end(), sort_by_y);

        // Step 2.2: Recursively build the tree
        kdtree_node* root = build(x_sorted_rat_populations, y_sorted_rat_populations, true);
        // print_tree(root, 0);

        // Step 3: Search for answer
        int best_bomb_x = 0;
        int best_bomb_y = 0;
        int max_dead_rats = -1;

        map<int, int> result_cache;

        for (list<rat_population*>::iterator ri = rat_populations.begin(); ri != rat_populations.end(); ri++)
        {
            int minBombX = max(strength, (*ri)->x - strength);
            int maxBombX = min(1024 - strength, (*ri)->x + strength);
            int minBombY = max(strength, (*ri)->y - strength);
            int maxBombY = min(1024- strength, (*ri)->y + strength);

            for (int bombX = minBombX; bombX <= maxBombX; bombX++)
            {
                for (int bombY = minBombY; bombY <= maxBombY; bombY++)
                {
                    int dead_rats = 0;
                    int bomb_key = bombX * 10000 + bombY;
                    // A worthwhile check - running the spatial index can be expensive doing repeatedly
                    // Initializing the array would be expensive enough just for the purpose of checking
                    if (result_cache.find(bomb_key) == result_cache.end())
                    {
                        // Good for verification

                        /*for (list<rat_population*>::iterator ti = rat_populations.begin(); ti != rat_populations.end(); ti++)
                        {
                            if (abs(bombX - (*ti)->x) <= strength && abs(bombY - (*ti)->y) <= strength)
                            {
                                dead_rats += (*ti)->size;
                            }
                        }*/

                        dead_rats = count(root, bombX - strength, bombY - strength, bombX + strength, bombY + strength);
                        // Good for comparison with simple search
                        // cout << bomb_key << "->" << dead_rats << endl;
                        result_cache.insert(pair<int, int>(bomb_key, dead_rats));
                        bool replace_result = false;
                        if (dead_rats > max_dead_rats)
                        {   
                            replace_result = true;
                        } 
                        else if (dead_rats == max_dead_rats)
                        {
                            if (bombX < best_bomb_x)
                            {
                                replace_result = true;
                            }
                            else if (bombX == best_bomb_x)
                            {
                                if (bombY < best_bomb_y)
                                {
                                    replace_result = true;
                                }
                            }
                        }
                        if (replace_result)
                        {
                            max_dead_rats = dead_rats;
                            best_bomb_x = bombX;
                            best_bomb_y = bombY;
                        }
                    }
                }
            }
        }
        cout << best_bomb_x << " " << best_bomb_y << " " << max_dead_rats << endl;

        // Step 4: Release dynamically allocated memory
        for (list<rat_population*>::iterator ri = rat_populations.begin(); ri != rat_populations.end(); ri++)
        {
            delete (*ri);
        }
        delete root;
    }

    return 0;
}