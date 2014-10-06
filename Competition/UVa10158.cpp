#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1099 

#include "UVa10158.h"

#include <iostream>
#include <string>
#include <set>
#include <vector>

using namespace std;

struct Partition
{
    set<int> left;
    set<int> right;
};

int find(vector<pair<int, Partition*> >& disjoint_sets, int person)
{
    if (disjoint_sets[person].first < 0)
    {
        return person;
    }
    else
    {
        return (disjoint_sets[person].first = find(disjoint_sets, disjoint_sets[person].first));
    }
}

Partition* merge_same_side(set<int>& one_left_set, set<int>& one_right_set, set<int>& two_left_set, set<int>& two_right_set)
{
    Partition* merged = new Partition();
    for (set<int>::iterator ol = one_left_set.begin(); ol != one_left_set.end(); ol++)
    {
        merged->left.insert(*ol);
    }
    for (set<int>::iterator or1 = one_right_set.begin(); or1 != one_right_set.end(); or1++)
    {
        merged->right.insert(*or1);
    }
    for (set<int>::iterator tl = two_left_set.begin(); tl != two_left_set.end(); tl++)
    {
        merged->left.insert(*tl);
    }
    for (set<int>::iterator tr = two_right_set.begin(); tr != two_right_set.end(); tr++)
    {
        merged->right.insert(*tr);
    }

    return merged;
}

Partition* merge_diff_side(set<int>& one_left_set, set<int>& one_right_set, set<int>& two_left_set, set<int>& two_right_set)
{
    Partition* merged = new Partition();
    for (set<int>::iterator ol = one_left_set.begin(); ol != one_left_set.end(); ol++)
    {
        merged->left.insert(*ol);
    }
    for (set<int>::iterator or1 = one_right_set.begin(); or1 != one_right_set.end(); or1++)
    {
        merged->right.insert(*or1);
    }
    for (set<int>::iterator tl = two_left_set.begin(); tl != two_left_set.end(); tl++)
    {
        merged->right.insert(*tl);
    }
    for (set<int>::iterator tr = two_right_set.begin(); tr != two_right_set.end(); tr++)
    {
        merged->left.insert(*tr);
    }

    return merged;
}

int UVa10158()
{
    int number_of_people;
    cin >> number_of_people;
    vector<pair<int, Partition*> > disjoint_sets;
    disjoint_sets.resize(number_of_people);
    for (int i = 0; i < number_of_people; i++)
    {
        disjoint_sets[i].first = -1;
        disjoint_sets[i].second = new Partition();
        disjoint_sets[i].second->left.insert(i);
    }
    while (true)
    {
        int operation_code;
        int person1;
        int person2;
        cin >> operation_code;
        cin >> person1;
        cin >> person2;
        if (operation_code == 0)
        {
            break;
        }
        int root1 = find(disjoint_sets, person1);
        int root2 = find(disjoint_sets, person2);
        set<int>& one_left_set = disjoint_sets[root1].second->left;
        set<int>& one_right_set = disjoint_sets[root1].second->right;
        set<int>& two_left_set = disjoint_sets[root2].second->left;
        set<int>& two_right_set = disjoint_sets[root2].second->right;
        bool oneIsLeft = one_left_set.find(person1) != one_left_set.end();
        bool twoIsLeft = two_left_set.find(person2) != two_left_set.end();

        switch(operation_code)
        {
        case 1:
            // setFriends
            if (root1 == root2)
            {
                if (oneIsLeft == twoIsLeft)
                {
                    // They are already on the same side - setFriend is a no-op here
                }
                else
                {
                    // They are already on different sides - report an error
                    cout << -1 << endl;
                }
            }
            else
            {
                Partition* merged = NULL;
                if (oneIsLeft == twoIsLeft)
                {
                    // Now we know they are on the same side
                    merged = merge_same_side(one_left_set, one_right_set, two_left_set, two_right_set);
                    
                }
                else
                {
                    // Now we know they are on the different sides
                    merged = merge_diff_side(one_left_set, one_right_set, two_left_set, two_right_set);
                }

                // Union by size
                if (disjoint_sets[root1].first < disjoint_sets[root2].first)
                {
                    disjoint_sets[root1].first = disjoint_sets[root1].first + disjoint_sets[root2].first;
                    disjoint_sets[root2].first = root1;
                    delete disjoint_sets[root1].second;
                    delete disjoint_sets[root2].second;
                    disjoint_sets[root1].second = merged;
                    disjoint_sets[root2].second = NULL;
                }
                else
                {
                    disjoint_sets[root2].first = disjoint_sets[root1].first + disjoint_sets[root2].first;
                    disjoint_sets[root1].first = root2;
                    delete disjoint_sets[root1].second;
                    delete disjoint_sets[root2].second;
                    disjoint_sets[root1].second = NULL;
                    disjoint_sets[root2].second = merged;
                }
            }
            break;
        case 2:
            // setEnemies
            if (root1 == root2)
            {
                if (oneIsLeft == twoIsLeft)
                {
                    // They are already on the same side - report an error
                    cout << -1 << endl;
                }
                else
                {
                    // They are already on different sides - setEnemies is a no-op here
                }
            }
            else
            {
                Partition* merged = NULL;
                if (oneIsLeft == twoIsLeft)
                {
                    // Now we know they are on different sides
                    merged = merge_diff_side(one_left_set, one_right_set, two_left_set, two_right_set);
                }
                else
                {
                    // Now we know they are on the same side
                    merged = merge_same_side(one_left_set, one_right_set, two_left_set, two_right_set);
                }

                // Union by size
                if (disjoint_sets[root1].first < disjoint_sets[root2].first)
                {
                    disjoint_sets[root1].first = disjoint_sets[root1].first + disjoint_sets[root2].first;
                    disjoint_sets[root2].first = root1;
                    delete disjoint_sets[root1].second;
                    delete disjoint_sets[root2].second;
                    disjoint_sets[root1].second = merged;
                    disjoint_sets[root2].second = NULL;
                }
                else
                {
                    disjoint_sets[root2].first = disjoint_sets[root1].first + disjoint_sets[root2].first;
                    disjoint_sets[root1].first = root2;
                    delete disjoint_sets[root1].second;
                    delete disjoint_sets[root2].second;
                    disjoint_sets[root1].second = NULL;
                    disjoint_sets[root2].second = merged;
                }
            }
            break;
        case 3:
            // areFriends
            if (root1 == root2)
            {
                if (oneIsLeft == twoIsLeft)
                {
                    // They are surely friends
                    cout << 1 << endl;
                }
                else
                {
                    // They are surely enemies
                    cout << 0 << endl;
                }
            }
            else
            {
                // Not sure case
                cout << 0 << endl;
            }
            break;
        case 4:
            // areEnemies
            if (root1 == root2)
            {
                if (oneIsLeft == twoIsLeft)
                {
                    // They are surely friends
                    cout << 0 << endl;
                }
                else
                {
                    // They are surely enemies
                    cout << 1 << endl;
                }
            }
            else
            {
                // Not sure case
                cout << 0 << endl;
            }
            break;
        default:
            break;
        }
    }
    return 0;
}