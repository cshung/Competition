#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=63

#include "UVa127.h"

#include <iostream>
#include <stack>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

struct card
{
    char rank;
    char suit;
};

bool read_cards(vector<card*>& deck)
{
    card* current_card = new card();
    cin >> current_card->rank;
    if (current_card->rank == '#')
    {
        delete current_card;
        return false;
    }
    cin >> current_card->suit;
    deck.push_back(current_card);
    current_card = NULL;

    for (int i = 0; i < 51; i++)
    {
        card* current_card = new card();
        cin.get(); /* Consume the whitespace */
        cin >> current_card->rank;
        cin >> current_card->suit;
        deck.push_back(current_card);
        current_card = NULL;
    }

    return true;
}

void delete_cards(vector<card*>& deck)
{
    for (vector<card*>::iterator ci = deck.begin(); ci != deck.end(); ci++)
    {
        delete (*ci);
    }
}

typedef stack<card*> pile;
typedef list<pile*> game;
typedef list<pile*>::iterator position;
typedef vector<position> positions;

bool deal(vector<card*>& deck, int& current_card, positions& movable_cards, game& current_game)
{
    if (current_card == deck.size())
    {
        return false;
    }

    card* next_card = deck[current_card++];
    pile* new_pile = new pile();
    new_pile->push(next_card);
    current_game.push_back(new_pile);
    position new_position = current_game.end();
    new_position--;
    movable_cards.push_back(new_position);
    return true;
}

void inspect(game& current_game, positions& movable_cards)
{
}

void inspect_disabled(game& current_game, positions& movable_cards)
{
    int num_stars = 0;
    for (position gi = current_game.begin(); gi != current_game.end(); gi++)
    {
        bool movable = false;
        for (positions::iterator mi = movable_cards.begin(); mi != movable_cards.end(); mi++)
        {
            if (*mi == gi)
            {
                movable  = true;
                break;
            }
        }
        if (movable)
        {
            num_stars++;
            cout << " * ";
        }
        else
        {
            cout << " - ";
        }
        pile temp_pile;
        pile* current_pile = *gi;
        while (current_pile->size() > 0)
        {
            temp_pile.push(current_pile->top());
            current_pile->pop();
        }
        while (temp_pile.size() > 0)
        {
            cout << temp_pile.top()->rank << temp_pile.top()->suit << " ";
            current_pile->push(temp_pile.top());
            temp_pile.pop();
        }
        cout << endl;
    }
    if (num_stars != movable_cards.size())
    {
        cout << "BOOM!" << endl;
    }
    cout << endl;
}

// I have to say - this is just awful design :(
void move(position& current_position, pile*& current_pile, position& neighbor_position, pile*& neighbor_pile, game& current_game, positions& movable_cards, positions& new_movable_cards)
{
    // Perform the move
    neighbor_pile->push(current_pile->top());
    current_pile->pop();
    
    current_position++;
    position current_next_position = current_position;
    current_position--;

    if (current_pile->size() == 0)
    {   
        current_game.erase(current_position);
        delete current_pile;        
    }
    else
    {
        new_movable_cards.push_back(current_position);           
    }

    if (current_next_position != current_game.end())
    {
        new_movable_cards.push_back(current_next_position);
        current_next_position++;
        if (current_next_position != current_game.end())
        {
            current_next_position++;
            if (current_next_position != current_game.end())
            {
                new_movable_cards.push_back(current_next_position);
            }
        }
    }
    
    neighbor_position++;
    position neighbor_next_position = neighbor_position;
    neighbor_position--;

    new_movable_cards.push_back(neighbor_position);
    if (neighbor_next_position != current_game.end())
    {
        new_movable_cards.push_back(neighbor_next_position);
        neighbor_next_position++;
        if (neighbor_next_position != current_game.end())
        {
            neighbor_next_position++;
            if (neighbor_next_position != current_game.end())
            {
                new_movable_cards.push_back(neighbor_next_position);
            }
        }
    }
}

void play_accordance_patience(vector<card*>& deck)
{
    int current_card = 0;
    
    // Debug only
    int move_count = 0;

    positions movable_cards;
    game current_game;
    while (true)
    {
        if (movable_cards.size() == 0)
        {
            if (!deal(deck, current_card, movable_cards, current_game))
            {
                break;
            }
            // cout << "Deal: " << current_card << endl;
            inspect(current_game, movable_cards);
        }
        else
        {
            positions new_movable_cards;
            for (positions::iterator pi = movable_cards.begin(); pi != movable_cards.end(); pi++)
            {
                position current_position = *pi;
                pile* current_pile = *current_position;
                position neighbor_position = current_position;
                pile* neighbor_pile = NULL;
                if (neighbor_position != current_game.begin())
                {
                    neighbor_position--;
                    if (neighbor_position != current_game.begin())
                    {
                        neighbor_position--;
                        if (neighbor_position != current_game.begin())
                        {
                            neighbor_position--;
                            neighbor_pile = *neighbor_position;
                            if ((current_pile->top()->rank == neighbor_pile->top()->rank) || (current_pile->top()->suit == neighbor_pile->top()->suit))
                            {
                                move_count++;
                                move(current_position, current_pile, neighbor_position, neighbor_pile, current_game, movable_cards, new_movable_cards);
                                movable_cards.erase(pi);
                                break;
                            }
                            neighbor_position++;
                        }
                        neighbor_position++;
                    }
                    neighbor_pile = *neighbor_position;
                    if ((current_pile->top()->rank == neighbor_pile->top()->rank) || (current_pile->top()->suit == neighbor_pile->top()->suit))
                    {
                        move_count++;
                        move(current_position, current_pile, neighbor_position, neighbor_pile, current_game, movable_cards, new_movable_cards);
                        movable_cards.erase(pi);
                        break;
                    }
                }
            }

            if (new_movable_cards.size() == 0)
            {
                movable_cards.clear();
            }
            else
            {
                for (positions::iterator mi = movable_cards.begin(); mi != movable_cards.end(); mi++)
                {
                    new_movable_cards.push_back(*mi);
                }

                movable_cards.clear();
                for (position gi = current_game.begin(); gi != current_game.end(); gi++)
                {
                    for (positions::iterator nmi = new_movable_cards.begin(); nmi != new_movable_cards.end(); nmi++)
                    {
                        if (*nmi == gi)
                        {
                            movable_cards.push_back(gi);
                            break;
                        }
                    }
                }

                // cout << "Move: " << move_count << endl;
                inspect(current_game, movable_cards);
            }
        }
    }

    cout << current_game.size() << " pile" << (current_game.size() == 1 ? "" : "s") << " remaining:";
    for (position gi = current_game.begin(); gi != current_game.end(); gi++)
    {
        pile* current_pile = *gi;
        cout << " " << current_pile->size();
        delete current_pile;
    }
    cout << endl;
}

int UVa127()
{
    while (true)
    {
        vector<card*> deck;
        if (read_cards(deck))
        {
            play_accordance_patience(deck);
            delete_cards(deck);
        }
        else
        {
            break;
        }
    }
    return 0;
}