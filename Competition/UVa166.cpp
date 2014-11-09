#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=102

#include "UVa166.h"

#include <iostream>
#include <iomanip>
#include <set>
#include <queue>

using namespace std;

struct UVa166_State
{
    int num_5_cents;
    int num_10_cents;
    int num_20_cents;
    int num_50_cents;
    int num_1_dollar;
    int num_2_dollars;
    int value_in_cents;
    int used_coin;
};

class UVa166_State_less
{
public:
    bool operator()(UVa166_State* first, UVa166_State* second)
    {
        if (first->value_in_cents < second->value_in_cents)
        {
            return true;
        }
        else if (first->value_in_cents > second->value_in_cents)
        {
            return false;
        }
        if (first->num_5_cents < second->num_5_cents)
        {
            return true;
        }
        else if (first->num_5_cents > second->num_5_cents)
        {
            return false;
        }
        if (first->num_10_cents < second->num_10_cents)
        {
            return true;
        }
        else if (first->num_10_cents > second->num_10_cents)
        {
            return false;
        }
        if (first->num_20_cents < second->num_20_cents)
        {
            return true;
        }
        else if (first->num_20_cents > second->num_20_cents)
        {
            return false;
        }
        if (first->num_50_cents < second->num_50_cents)
        {
            return true;
        }
        else if (first->num_50_cents > second->num_50_cents)
        {
            return false;
        }
        if (first->num_1_dollar < second->num_1_dollar)
        {
            return true;
        }
        else if (first->num_1_dollar > second->num_1_dollar)
        {
            return false;
        }
        if (first->num_2_dollars < second->num_2_dollars)
        {
            return true;
        }
        else if (first->num_2_dollars > second->num_2_dollars)
        {
            return false;
        }
        if (first->used_coin < second->used_coin)
        {
            return true;
        }
        else if (first->used_coin > second->used_coin)
        {
            return false;
        }

        return false;
    }
};

int UVa166()
{
    set<UVa166_State*, UVa166_State_less> visited;    
    while (true)
    {
        UVa166_State* initial_state = new UVa166_State();
        cin >> initial_state->num_5_cents;
        cin >> initial_state->num_10_cents;
        cin >> initial_state->num_20_cents;
        cin >> initial_state->num_50_cents;
        cin >> initial_state->num_1_dollar;
        cin >> initial_state->num_2_dollars;
        if (initial_state->num_5_cents < 0) { throw 0; }
        if (initial_state->num_10_cents < 0) { throw 0; }
        if (initial_state->num_20_cents < 0) { throw 0; }
        if (initial_state->num_50_cents < 0) { throw 0; }
        if (initial_state->num_1_dollar < 0) { throw 0; }
        if (initial_state->num_2_dollars < 0) { throw 0; }
        initial_state->value_in_cents = 0;
        initial_state->used_coin = 0;
        if ((initial_state->num_5_cents + initial_state->num_10_cents + initial_state->num_20_cents + initial_state->num_50_cents + initial_state->num_1_dollar + initial_state->num_2_dollars) == 0)
        {
            break;
        }
        double value;
        cin >> value;
        if (value < 0) { throw 0; }
        initial_state->value_in_cents = (int)(value * 100 + 0.1);
        if (initial_state->value_in_cents % 5 != 0)
        {
            throw 0;
        }
        queue<UVa166_State*> bfs_queue;
        bfs_queue.push(initial_state);
        bool found = false;
        while (bfs_queue.size() > 0)
        {
            UVa166_State* current = bfs_queue.front();
            bfs_queue.pop();
            if (current->value_in_cents == 0)
            {
                found = true;
                cout << setw(3) << current->used_coin << endl;
                break;
            }
            else if (current->value_in_cents > 0)
            {
                if (current->num_5_cents > 0)
                {
                    UVa166_State* new_state = new UVa166_State();
                    new_state->num_5_cents = current->num_5_cents - 1;
                    new_state->num_10_cents = current->num_10_cents;
                    new_state->num_20_cents = current->num_20_cents;
                    new_state->num_50_cents = current->num_50_cents;
                    new_state->num_1_dollar = current->num_1_dollar;
                    new_state->num_2_dollars = current->num_2_dollars;
                    new_state->value_in_cents = current->value_in_cents - 5;
                    new_state->used_coin = current->used_coin + 1;
                    if (visited.find(new_state) == visited.end())
                    {
                        visited.insert(new_state);
                        bfs_queue.push(new_state);
                    }
                }
                if (current->num_10_cents > 0)
                {
                    UVa166_State* new_state = new UVa166_State();
                    new_state->num_5_cents = current->num_5_cents;
                    new_state->num_10_cents = current->num_10_cents - 1;
                    new_state->num_20_cents = current->num_20_cents;
                    new_state->num_50_cents = current->num_50_cents;
                    new_state->num_1_dollar = current->num_1_dollar;
                    new_state->num_2_dollars = current->num_2_dollars;
                    new_state->value_in_cents = current->value_in_cents - 10;
                    new_state->used_coin = current->used_coin + 1;
                    if (visited.find(new_state) == visited.end())
                    {
                        visited.insert(new_state);
                        bfs_queue.push(new_state);
                    }
                }
                if (current->num_20_cents > 0)
                {
                    UVa166_State* new_state = new UVa166_State();
                    new_state->num_5_cents = current->num_5_cents;
                    new_state->num_10_cents = current->num_10_cents;
                    new_state->num_20_cents = current->num_20_cents - 1;
                    new_state->num_50_cents = current->num_50_cents;
                    new_state->num_1_dollar = current->num_1_dollar;
                    new_state->num_2_dollars = current->num_2_dollars;
                    new_state->value_in_cents = current->value_in_cents - 20;
                    new_state->used_coin = current->used_coin + 1;
                    if (visited.find(new_state) == visited.end())
                    {
                        visited.insert(new_state);
                        bfs_queue.push(new_state);
                    }
                }
                if (current->num_50_cents > 0)
                {
                    UVa166_State* new_state = new UVa166_State();
                    new_state->num_5_cents = current->num_5_cents;
                    new_state->num_10_cents = current->num_10_cents;
                    new_state->num_20_cents = current->num_20_cents;
                    new_state->num_50_cents = current->num_50_cents - 1;
                    new_state->num_1_dollar = current->num_1_dollar;
                    new_state->num_2_dollars = current->num_2_dollars;
                    new_state->value_in_cents = current->value_in_cents - 50;
                    new_state->used_coin = current->used_coin + 1;
                    if (visited.find(new_state) == visited.end())
                    {
                        visited.insert(new_state);
                        bfs_queue.push(new_state);
                    }
                }
                if (current->num_1_dollar > 0)
                {
                    UVa166_State* new_state = new UVa166_State();
                    new_state->num_5_cents = current->num_5_cents;
                    new_state->num_10_cents = current->num_10_cents;
                    new_state->num_20_cents = current->num_20_cents;
                    new_state->num_50_cents = current->num_50_cents;
                    new_state->num_1_dollar = current->num_1_dollar - 1;
                    new_state->num_2_dollars = current->num_2_dollars;
                    new_state->value_in_cents = current->value_in_cents - 100;
                    new_state->used_coin = current->used_coin + 1;
                    if (visited.find(new_state) == visited.end())
                    {
                        visited.insert(new_state);
                        bfs_queue.push(new_state);
                    }
                }
                if (current->num_2_dollars > 0)
                {
                    UVa166_State* new_state = new UVa166_State();
                    new_state->num_5_cents = current->num_5_cents;
                    new_state->num_10_cents = current->num_10_cents;
                    new_state->num_20_cents = current->num_20_cents;
                    new_state->num_50_cents = current->num_50_cents;
                    new_state->num_1_dollar = current->num_1_dollar;
                    new_state->num_2_dollars = current->num_2_dollars - 1;
                    new_state->value_in_cents = current->value_in_cents - 200;
                    new_state->used_coin = current->used_coin + 1;
                    if (visited.find(new_state) == visited.end())
                    {
                        visited.insert(new_state);
                        bfs_queue.push(new_state);
                    }
                }
            } 
            else
            {
                {
                    UVa166_State* new_state = new UVa166_State();
                    new_state->num_5_cents = current->num_5_cents;
                    new_state->num_10_cents = current->num_10_cents;
                    new_state->num_20_cents = current->num_20_cents;
                    new_state->num_50_cents = current->num_50_cents;
                    new_state->num_1_dollar = current->num_1_dollar;
                    new_state->num_2_dollars = current->num_2_dollars;
                    new_state->value_in_cents = current->value_in_cents + 5;
                    new_state->used_coin = current->used_coin + 1;
                    if (visited.find(new_state) == visited.end())
                    {
                        visited.insert(new_state);
                        bfs_queue.push(new_state);
                    }
                }
                {
                    UVa166_State* new_state = new UVa166_State();
                    new_state->num_5_cents = current->num_5_cents;
                    new_state->num_10_cents = current->num_10_cents;
                    new_state->num_20_cents = current->num_20_cents;
                    new_state->num_50_cents = current->num_50_cents;
                    new_state->num_1_dollar = current->num_1_dollar;
                    new_state->num_2_dollars = current->num_2_dollars;
                    new_state->value_in_cents = current->value_in_cents + 10;
                    new_state->used_coin = current->used_coin + 1;
                    if (visited.find(new_state) == visited.end())
                    {
                        visited.insert(new_state);
                        bfs_queue.push(new_state);
                    }
                }
                {
                    UVa166_State* new_state = new UVa166_State();
                    new_state->num_5_cents = current->num_5_cents;
                    new_state->num_10_cents = current->num_10_cents;
                    new_state->num_20_cents = current->num_20_cents;
                    new_state->num_50_cents = current->num_50_cents;
                    new_state->num_1_dollar = current->num_1_dollar;
                    new_state->num_2_dollars = current->num_2_dollars;
                    new_state->value_in_cents = current->value_in_cents + 20;
                    new_state->used_coin = current->used_coin + 1;
                    if (visited.find(new_state) == visited.end())
                    {
                        visited.insert(new_state);
                        bfs_queue.push(new_state);
                    }
                }
                {
                    UVa166_State* new_state = new UVa166_State();
                    new_state->num_5_cents = current->num_5_cents;
                    new_state->num_10_cents = current->num_10_cents;
                    new_state->num_20_cents = current->num_20_cents;
                    new_state->num_50_cents = current->num_50_cents;
                    new_state->num_1_dollar = current->num_1_dollar;
                    new_state->num_2_dollars = current->num_2_dollars;
                    new_state->value_in_cents = current->value_in_cents + 50;
                    new_state->used_coin = current->used_coin + 1;
                    if (visited.find(new_state) == visited.end())
                    {
                        visited.insert(new_state);
                        bfs_queue.push(new_state);
                    }
                }
                {
                    UVa166_State* new_state = new UVa166_State();
                    new_state->num_5_cents = current->num_5_cents;
                    new_state->num_10_cents = current->num_10_cents;
                    new_state->num_20_cents = current->num_20_cents;
                    new_state->num_50_cents = current->num_50_cents;
                    new_state->num_1_dollar = current->num_1_dollar;
                    new_state->num_2_dollars = current->num_2_dollars;
                    new_state->value_in_cents = current->value_in_cents + 100;
                    new_state->used_coin = current->used_coin + 1;
                    if (visited.find(new_state) == visited.end())
                    {
                        visited.insert(new_state);
                        bfs_queue.push(new_state);
                    }
                }
                {
                    UVa166_State* new_state = new UVa166_State();
                    new_state->num_5_cents = current->num_5_cents;
                    new_state->num_10_cents = current->num_10_cents;
                    new_state->num_20_cents = current->num_20_cents;
                    new_state->num_50_cents = current->num_50_cents;
                    new_state->num_1_dollar = current->num_1_dollar;
                    new_state->num_2_dollars = current->num_2_dollars;
                    new_state->value_in_cents = current->value_in_cents + 200;
                    new_state->used_coin = current->used_coin + 1;
                    if (visited.find(new_state) == visited.end())
                    {
                        visited.insert(new_state);
                        bfs_queue.push(new_state);
                    }
                }
            }
        }
        if (!found)
        {
            throw 0;
        }
    }

    return 0;
}