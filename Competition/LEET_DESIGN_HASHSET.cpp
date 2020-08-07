#include "stdafx.h"

// https://leetcode.com/problems/design-hashset/

#include "LEET_DESIGN_HASHSET.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_DESIGN_HASHSET
{
    class MyHashSet
    {
    public:
        MyHashSet()
        {
            capacity = 10000;
            cells = new Cell * [capacity];
            for (int i = 0; i < capacity; i++)
            {
                cells[i] = nullptr;
            }
            size = 0;
        }

        ~MyHashSet()
        {
            for (int i = 0; i < this->capacity; i++)
            {
                Cell* cursor = this->cells[i];
                while (cursor != nullptr)
                {
                    Cell* toDelete = cursor;
                    cursor = cursor->next;
                    delete toDelete;
                }
            }
            delete[] this->cells;
        }

        void add(int key)
        {
            remove(key);
            int hash = hash_value(key);
            Cell* newCell = new Cell();
            newCell->value = key;
            newCell->next = this->cells[hash];
            this->cells[hash] = newCell;
            this->size++;
        }

        void remove(int key)
        {
            int hash = hash_value(key);
            Cell* cursor = this->cells[hash];
            if (cursor != nullptr)
            {
                if (cursor->value == key)
                {
                    this->cells[hash] = cursor->next;
                    delete cursor;
                    this->size--;
                    return;
                }
                Cell* prev = cursor;
                Cell* next = prev->next;
                while (next != nullptr)
                {
                    if (next->value == key)
                    {
                        prev->next = next->next;
                        delete next;
                        this->size--;
                        return;
                    }
                    prev = next;
                    next = next->next;
                }
            }
        }

        bool contains(int key)
        {
            int hash = hash_value(key);
            Cell* cursor = this->cells[hash];
            while (cursor != nullptr)
            {
                if (cursor->value == key)
                {
                    return true;
                }
                cursor = cursor->next;
            }
            return false;
        }
    private:
        unsigned int hash_value(int key)
        {
            return key % this->capacity;
        }
        struct Cell
        {
            int value;
            Cell* next;
        };
        Cell** cells;
        int capacity;
        int size;
    };
};

using namespace _LEET_DESIGN_HASHSET;

int LEET_DESIGN_HASHSET()
{
    MyHashSet hashSet;
    hashSet.add(1);
    hashSet.add(2);
    cout << hashSet.contains(1) << endl;    // returns true
    cout << hashSet.contains(3) << endl;    // returns false (not found)
    hashSet.add(2);
    cout << hashSet.contains(2) << endl;    // returns true
    hashSet.remove(2);
    cout << hashSet.contains(2) << endl;    // returns false (already removed)
    return 0;
}