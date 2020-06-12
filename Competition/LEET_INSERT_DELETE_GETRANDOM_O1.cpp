#include "stdafx.h"

// https://leetcode.com/problems/insert-delete-getrandom-o1/

#include "LEET_INSERT_DELETE_GETRANDOM_O1.h"
#include <map>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_INSERT_DELETE_GETRANDOM_O1
{
    class RandomizedSet
    {
    public:
        /** Initialize your data structure here. */
        RandomizedSet()
        {

        }

        /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
        bool insert(int val)
        {
            if (forward.find(val) != forward.end())
            {
                return false;
            }
            forward.insert(make_pair(val, backward.size()));
            backward.push_back(val);
            return true;
        }

        /** Removes a value from the set. Returns true if the set contained the specified element. */
        bool remove(int val)
        {
            auto probe = forward.find(val);
            if (probe == forward.end())
            {
                return false;
            }
            int id = probe->second;
            int last_id = backward.size() - 1;
            int last_val = backward[last_id];
            backward.pop_back();
            forward.erase(probe);
            if (id != last_id)
            {
                forward.erase(last_val);
                forward.insert(make_pair(last_val, id));
                backward[id] = last_val;
            }
            return true;
        }

        /** Get a random element from the set. */
        int getRandom()
        {
            return backward[rand() % backward.size()];
        }
    private:
        unordered_map<int, int> forward;
        vector<int> backward;
    };
};

using namespace _LEET_INSERT_DELETE_GETRANDOM_O1;

int LEET_INSERT_DELETE_GETRANDOM_O1()
{
    RandomizedSet obj;
    cout << obj.insert(1) << endl;
    cout << obj.remove(2) << endl;
    cout << obj.getRandom() << endl;
    return 0;
}