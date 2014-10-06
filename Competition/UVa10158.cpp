#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1099 

#include "UVa10158.h"

#include <iostream>
#include <string>
#include <set>
#include <vector>

using namespace std;

struct partition
{
    int left_root;
    int right_root;
};

int find_group_representative(vector<pair<int, partition*> >& related_groups, int person)
{
    if (related_groups[person].first < 0)
    {
        return person;
    }
    else
    {
        return (related_groups[person].first = find_group_representative(related_groups, related_groups[person].first));
    }
}

int find_friend_representative(vector<int>& known_friends, int person)
{
    if (known_friends[person] < 0)
    {
        return person;
    }
    else
    {
        return (known_friends[person] = find_friend_representative(known_friends, known_friends[person]));
    }
}

partition* merge_same_side(partition* first, partition* second, vector<int>& known_friends)
{
    partition* merged = new partition();

    if (first->left_root == -1)
    {
        merged->left_root = second->left_root;
    }
    else if (second->left_root == -1)
    {
        merged->left_root = first->left_root;
    }
    else
    {
        // Union-by-size for left
        if (known_friends[first->left_root] < known_friends[second->left_root])
        {
            known_friends[first->left_root] = known_friends[first->left_root] + known_friends[second->left_root];
            known_friends[second->left_root] = first->left_root;
            merged->left_root = first->left_root;
        }
        else
        {
            known_friends[second->left_root] = known_friends[first->left_root] + known_friends[second->left_root];
            known_friends[first->left_root] = second->left_root;
            merged->left_root = second->left_root;
        }
    }

    if (first->right_root == -1)
    {
        merged->right_root = second->right_root;
    }
    else if (second->right_root == -1)
    {
        merged->right_root = first->right_root;
    }
    else
    {
        // Union-by-size for right
        if (known_friends[first->right_root] < known_friends[second->right_root])
        {
            known_friends[first->right_root] = known_friends[first->right_root] + known_friends[second->right_root];
            known_friends[second->right_root] = first->right_root;
            merged->right_root = first->right_root;
        }
        else
        {
            known_friends[second->right_root] = known_friends[first->right_root] + known_friends[second->right_root];
            known_friends[first->right_root] = second->right_root;
            merged->right_root = second->right_root;
        }
    }

    return merged;
}

partition* merge_diff_side(partition* first, partition* second, vector<int>& known_friends)
{
    partition* merged = new partition();
    
    if (first->left_root == -1)
    {
        merged->left_root = second->right_root;
    }
    else if (second->right_root == -1)
    {
        merged->left_root = first->left_root;
    }
    else
    {
        // Union-by-size for left
        if (known_friends[first->left_root] < known_friends[second->right_root])
        {
            known_friends[first->left_root] = known_friends[first->left_root] + known_friends[second->right_root];
            known_friends[second->right_root] = first->left_root;
            merged->left_root = first->left_root;
        }
        else
        {
            known_friends[second->right_root] = known_friends[first->left_root] + known_friends[second->right_root];
            known_friends[first->left_root] = second->right_root;
            merged->left_root = second->right_root;
        }
    }

    if (first->right_root == -1)
    {
        merged->right_root = second->left_root;
    }
    else if (second->left_root == -1)
    {
        merged->right_root = first->right_root;
    }
    else
    {
        // Union-by-size for right
        if (known_friends[first->right_root] < known_friends[second->left_root])
        {
            known_friends[first->right_root] = known_friends[first->right_root] + known_friends[second->left_root];
            known_friends[second->left_root] = first->right_root;
            merged->right_root = first->right_root;
        }
        else
        {
            known_friends[second->left_root] = known_friends[first->right_root] + known_friends[second->left_root];
            known_friends[first->right_root] = second->left_root;
            merged->right_root = second->left_root;
        }
    }

    return merged;
}

int UVa10158()
{
    int number_of_people;
    cin >> number_of_people;
    vector<pair<int, partition*> > related_groups;
    vector<int> known_friends;
    related_groups.resize(number_of_people);
    known_friends.resize(number_of_people);
    for (int i = 0; i < number_of_people; i++)
    {
        related_groups[i].first = -1;
        related_groups[i].second = new partition();
        related_groups[i].second->left_root = i;
        related_groups[i].second->right_root = -1;
        known_friends[i] = -1;
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
        int root1 = find_group_representative(related_groups, person1);
        int root2 = find_group_representative(related_groups, person2);
        bool oneIsLeft = find_friend_representative(known_friends, person1) == related_groups[root1].second->left_root;
        bool twoIsLeft = find_friend_representative(known_friends, person2) == related_groups[root2].second->left_root;

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
                partition* merged = NULL;
                if (oneIsLeft == twoIsLeft)
                {
                    // Now we know they are on the same side
                    merged = merge_same_side(related_groups[root1].second, related_groups[root2].second, known_friends);
                }
                else
                {
                    // Now we know they are on the different sides
                    merged = merge_diff_side(related_groups[root1].second, related_groups[root2].second, known_friends);
                }

                // Union by size
                if (related_groups[root1].first < related_groups[root2].first)
                {
                    related_groups[root1].first = related_groups[root1].first + related_groups[root2].first;
                    related_groups[root2].first = root1;
                    delete related_groups[root1].second;
                    delete related_groups[root2].second;
                    related_groups[root1].second = merged;
                    related_groups[root2].second = NULL;
                }
                else
                {
                    related_groups[root2].first = related_groups[root1].first + related_groups[root2].first;
                    related_groups[root1].first = root2;
                    delete related_groups[root1].second;
                    delete related_groups[root2].second;
                    related_groups[root1].second = NULL;
                    related_groups[root2].second = merged;
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
                partition* merged = NULL;
                if (oneIsLeft == twoIsLeft)
                {
                    // Now we know they are on different sides
                    merged = merge_diff_side(related_groups[root1].second, related_groups[root2].second, known_friends);
                }
                else
                {
                    // Now we know they are on the same side
                    merged = merge_same_side(related_groups[root1].second, related_groups[root2].second, known_friends);
                }

                // Union by size
                if (related_groups[root1].first < related_groups[root2].first)
                {
                    related_groups[root1].first = related_groups[root1].first + related_groups[root2].first;
                    related_groups[root2].first = root1;
                    delete related_groups[root1].second;
                    delete related_groups[root2].second;
                    related_groups[root1].second = merged;
                    related_groups[root2].second = NULL;
                }
                else
                {
                    related_groups[root2].first = related_groups[root1].first + related_groups[root2].first;
                    related_groups[root1].first = root2;
                    delete related_groups[root1].second;
                    delete related_groups[root2].second;
                    related_groups[root1].second = NULL;
                    related_groups[root2].second = merged;
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