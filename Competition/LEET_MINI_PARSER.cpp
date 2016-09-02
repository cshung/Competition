#include "stdafx.h"

// https://leetcode.com/problems/mini-parser/

#include "LEET_MINI_PARSER.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_MINI_PARSER
{
    // This is the interface that allows for creating nested lists.
    // You should not implement it, or speculate about its implementation
    class NestedInteger
    {
    public:
        // Constructor initializes an empty nested list.
        NestedInteger()
        {
            this->_isInteger = false;
        }

        // Constructor initializes a single integer.
        NestedInteger(int value)
        {
            this->_isInteger = true;
            this->value = value;
        }

        // Return true if this NestedInteger holds a single integer, rather than a nested list.
        bool isInteger() const
        {
            return this->_isInteger;
        }

        // Return the single integer that this NestedInteger holds, if it holds a single integer
        // The result is undefined if this NestedInteger holds a nested list
        int getInteger() const
        {
            return this->value;
        }

        // Set this NestedInteger to hold a single integer.
        void setInteger(int value)
        {
            this->value = value;
        }

        // Set this NestedInteger to hold a nested list and adds a nested integer to it.
        void add(const NestedInteger &ni)
        {
            this->list.push_back(ni);
        }

        // Return the nested list that this NestedInteger holds, if it holds a nested list
        // The result is undefined if this NestedInteger holds a single integer
        const vector<NestedInteger> &getList() const
        {
            return this->list;
        }

        const void ToString(stringstream& sout)
        {
            if (this->_isInteger)
            {
                sout << this->value;
            }
            else
            {
                sout << "[";
                bool first = true;
                for (auto&& n : this->list)
                {
                    if (first)
                    {
                        first = false;
                    }
                    else
                    {
                        sout << ",";
                    }
                    n.ToString(sout);
                }
                sout << "]";
            }
        }


    private:
        bool _isInteger;
        int value;
        vector<NestedInteger> list;
    };

    class Solution {
    public:
        NestedInteger deserialize(string s) {
            parser t(s);
            return t.ParseNestedInteger();
        }
    private:
        enum token_type
        {
            open_bracket,
            close_bracket,
            comma,
            integer,
        };
        class scanner
        {
        public:
            scanner(string& s) : m_s(s), m_position(0), m_negative(false) { }
            void scan()
            {
                char c = this->m_s[this->m_position++];
                if (c == '[')
                {
                    if (this->m_negative)
                    {
                        throw 3;
                    }
                    this->m_token_type = token_type::open_bracket;
                }
                else if (c == ']')
                {
                    if (this->m_negative)
                    {
                        throw 3;
                    }
                    this->m_token_type = token_type::close_bracket;
                }
                else if (c == ',')
                {
                    if (this->m_negative)
                    {
                        throw 3;
                    }
                    this->m_token_type = token_type::comma;
                }
                else if (c == '-')
                {
                    if (this->m_negative)
                    {
                        throw 3;
                    }
                    this->m_negative = true;
                    this->scan();
                }
                else if (c >= '0' && c <= '9')
                {
                    this->m_token_type = token_type::integer;
                    this->m_value = c - '0';
                    while (true)
                    {
                        c = this->m_s[this->m_position++];
                        if (c >= '0' && c <= '9')
                        {
                            this->m_value = this->m_value * 10 + c - '0';
                        }
                        else
                        {
                            break;
                        }
                    }

                    if (this->m_negative)
                    {
                        this->m_value = -1 * this->m_value;
                        this->m_negative = false;
                    }
                    this->m_position--;
                }
                else
                {
                    // The input is invalid!
                    throw 0;
                }
            }

            token_type get_token_type()
            {
                return this->m_token_type;
            }

            int get_token_value()
            {
                return this->m_value;
            }
        private:
            
            string& m_s;
            int m_position;
            token_type m_token_type;
            int m_value;
            bool m_negative;
        };
        class parser
        {
        public:
            parser(string& s) : m_scanner(s)
            {
                this->m_scanner.scan();
            }
            NestedInteger ParseNestedInteger()
            {
                if (this->m_scanner.get_token_type() == token_type::integer)
                {
                    return NestedInteger(this->m_scanner.get_token_value());
                }
                else if (this->m_scanner.get_token_type() == token_type::open_bracket)
                {
                    NestedInteger result;
                    while (true)
                    {
                        this->m_scanner.scan();
                        if (this->m_scanner.get_token_type() == token_type::close_bracket)
                        {
                            break;
                        }
                        result.add(this->ParseNestedInteger());
                        this->m_scanner.scan();
                        if (this->m_scanner.get_token_type() == token_type::close_bracket)
                        {
                            break;
                        }
                        else if (this->m_scanner.get_token_type() != token_type::comma)
                        {
                            // The input is invalid
                            throw 1;
                        }
                    }
                    return result;
                }
                else
                {
                    throw 2;
                }
            }
        private:
            scanner m_scanner;
        };
    };
};

using namespace _LEET_MINI_PARSER;

int LEET_MINI_PARSER()
{
    Solution solution;
    NestedInteger result = solution.deserialize("[-32,[]]");
    stringstream sout;
    result.ToString(sout);
    cout << sout.str() << endl;
    return 0;
}