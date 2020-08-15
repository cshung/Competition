#include "stdafx.h"

// https://leetcode.com/problems/iterator-for-combination/

#include "LEET_ITERATOR_FOR_COMBINATION.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_ITERATOR_FOR_COMBINATION
{

    class CombinationIterator
    {
    public:
        CombinationIterator(string characters, int combinationLength)
        {
            this->m_characters = characters;
            this->m_combinationLength = combinationLength;
        }

        string next()
        {
            if (this->m_combination.size() == 0)
            {
                this->m_combination.resize(this->m_combinationLength);
                for (int i = 0; i < this->m_combinationLength; i++)
                {
                    this->m_combination[i] = i;
                }
            }
            else
            {
                int digit_to_follow = 0;
                int digit_to_move = this->m_combinationLength - 1;
                while (true)
                {
                    if (this->m_combination[digit_to_move] < this->m_characters.length() - 1 - digit_to_follow)
                    {
                        this->m_combination[digit_to_move]++;
                        for (int i = 0; i < digit_to_follow; i++)
                        {
                            this->m_combination[digit_to_move + 1 + i] = this->m_combination[digit_to_move + i] + 1;
                        }
                        break;
                    }
                    else
                    {
                        digit_to_move--;
                        digit_to_follow++;
                    }
                }
            }
            ostringstream oss;
            for (int i = 0; i < this->m_combinationLength; i++)
            {
                oss << this->m_characters[this->m_combination[i]];
            }
            return oss.str();
        }

        bool hasNext()
        {
            return this->m_combination.size() == 0 || this->m_combination[0] < this->m_characters.length() - this->m_combinationLength;
        }
    private:
        string m_characters;
        int m_combinationLength;
        vector<int> m_combination;
    };
};

using namespace _LEET_ITERATOR_FOR_COMBINATION;

int LEET_ITERATOR_FOR_COMBINATION()
{
    CombinationIterator ci("abcdef", 3);
    while (ci.hasNext())
    {
        cout << ci.next() << endl;
    }
    return 0;
}