#include "stdafx.h"

// https://leetcode.com/problems/peeking-iterator/

#include "LEET_PEEKING_ITERATOR.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

namespace _LEET_PEEKING_ITERATOR
{
    // Below is the interface for Iterator, which is already defined for you.
    // **DO NOT** modify the interface for Iterator.
    class Iterator
    {
        struct Data;
        Data* data;
    public:
        Iterator(const vector<int>& nums);
        Iterator(const Iterator& iter);
        virtual ~Iterator();
        // Returns the next element in the iteration.
        int next();
        // Returns true if the iteration has more elements.
        bool hasNext() const;
    };

    // Implementation for Iterator - not required for the problem - but my code wouldn't compile without it
    struct Iterator::Data
    {
        Data(const vector<int>& nums) : m_nums(nums)
        {
            this->m_index = -1;
        }
        Data(const Iterator::Data& data) : m_nums(data.m_nums)
        {
            this->m_index = data.m_index;
        }
        const vector<int>& m_nums;
        int m_index;
    };

    Iterator::Iterator(const vector<int>& nums)
    {
        this->data = new Iterator::Data(nums);
    }

    Iterator::Iterator(const Iterator& iter)
    {
        this->data = new Iterator::Data(*iter.data);
    }

    Iterator::~Iterator()
    {
        delete this->data;
    }

    int Iterator::next()
    {
        return this->data->m_nums[++this->data->m_index];
    }

    bool Iterator::hasNext() const
    {
        return (this->data->m_index + 1) != this->data->m_nums.size();
    }

    class PeekingIterator : public Iterator
    {
    private:
        bool m_wasHasNext;
        int m_wasNext;

        void prefetch()
        {
            this->m_wasHasNext = Iterator::hasNext();
            if (this->m_wasHasNext)
            {
                this->m_wasNext = Iterator::next();
            }
        }
    public:
        PeekingIterator(const vector<int>& nums) : Iterator(nums)
        {
            this->prefetch();
        }

        // Returns the next element in the iteration without advancing the iterator.
        int peek()
        {
            if (this->m_wasHasNext)
            {
                return this->m_wasNext;
            }
            else
            {
                // represents end of iteration?
                return -1;
            }
        }

        // hasNext() and next() should behave the same as in the Iterator interface.
        // Override them if needed.
        int next()
        {
            int oldWasNext = this->m_wasNext;
            this->prefetch();
            return oldWasNext;
        }

        bool hasNext() const
        {
            return this->m_wasHasNext;
        }
    };
};

using namespace _LEET_PEEKING_ITERATOR;

int LEET_PEEKING_ITERATOR()
{
    int case1[] = { -1, 0, 1, 2, -1, -4 };
    vector<int> case1_vector(case1, case1 + _countof(case1));
    PeekingIterator caseOneIterator(case1_vector);
    while (caseOneIterator.hasNext())
    {
        cout << caseOneIterator.peek() << endl;
        cout << caseOneIterator.next() << endl;
    }

    return 0;
}