#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=63

#include "UVa127.h"

#include <iostream>
#include <stack>

using namespace std;

struct card
{
    char num;
    char deck;
};

int UVa127()
{
    while (true)
    {
        card current_card;
        cin >> current_card.num;
        if (current_card.num == '#')
        {
            break;
        }
        cin >> current_card.deck;

        stack<card> decks;

        for (int i = 0; i < 51; i++)
        {

        }

    }
    return 0;
}