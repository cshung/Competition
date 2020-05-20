#include "stdafx.h"

// https://leetcode.com/problems/equal-rational-numbers/

#include "LEET_EQUAL_RATIONAL_NUMBERS.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

namespace _LEET_EQUAL_RATIONAL_NUMBERS
{
    class Helper
    {
    public:
        Helper(string& str) : m_str(str)
        {
            m_d = -1;
            m_o = -1;
            m_l = m_str.length();
            for (int i = 0; i < m_str.length(); i++)
            {
                if (m_str[i] == '.')
                {
                    m_d = i;
                }
                else if (m_str[i] == '(')
                {
                    m_o = i;
                }
            }
            m_9 = false;
            if (m_o != -1)
            {
                m_9 = true;
                for (int i = m_o + 1; i < m_l - 1; i++)
                {
                    if (m_str[i] != '9')
                    {
                        m_9 = false;
                        break;
                    }
                }
            }
            m_carry = m_9;
        }

        int get_integer_part_length()
        {
            if (m_d == -1)
            {
                return m_l;
            }
            else
            {
                return m_d;
            }
        }

        char get_integer_part_character(int i)
        {
            char c;
            if (i < m_p)
            {
                c = '0';
            }
            else
            {
                c = m_str[i - m_p];
            }
            return process_carry(c);
        }

        int get_decimal_part_length()
        {
            if (m_d == -1)
            {
                return 0;
            }
            else if (m_o == -1)
            {
                return m_l - m_d - 1;
            }
            else
            {
                return m_o - m_d - 1;
            }
        }

        char get_decimal_part_character(int i)
        {
            char c;
            if (i < get_decimal_part_length())
            {
                c = m_str[m_d + i + 1];
            }
            else
            {
                if (m_o == -1)
                {
                    c = '0';
                }
                else
                {
                    c = m_str[m_o + 1 + (i - get_decimal_part_length()) % get_repeating_part_length()];
                }
            }

            return process_carry(c);
        }

        int get_repeating_part_length()
        {
            if (m_9)
            {
                return 1;
            }
            else if (m_o == -1)
            {
                return 1;
            }
            else
            {
                return m_l - m_o - 2;
            }
        }

        char get_repeating_character(int i)
        {
            if (m_9)
            {
                return '0';
            }
            else if (m_o == -1)
            {
                return '0';
            }
            else
            {
                return m_str[m_o + 1 + (m_r + i) % get_repeating_part_length()];
            }
        }

        void pad(int that_integer_part_length)
        {
            int this_integer_part_length = this->get_integer_part_length();
            if (this_integer_part_length < that_integer_part_length)
            {
                m_p = that_integer_part_length - this_integer_part_length;
            }
            else
            {
                m_p = 0;
            }
        }
        void unroll(int that_decimal_part_length)
        {
            int this_decimal_part_length = this->get_decimal_part_length();
            if (this_decimal_part_length < that_decimal_part_length)
            {
                m_r = that_decimal_part_length - this_decimal_part_length;
            }
            else
            {
                m_r = 0;
            }
        }
    private:
        string& m_str;
        int m_d;
        int m_o;
        int m_l;
        bool m_9;
        int m_r;
        int m_p;
        bool m_carry;
        char process_carry(char c)
        {
            if (m_carry)
            {
                if (c == '9')
                {
                    c = '0';
                }
                else
                {
                    c = c + 1;
                    m_carry = false;
                }
            }
            return c;
        }
    };
    class Solution
    {
    public:
        bool isRationalEqual(string S, string T)
        {
            Helper s(S);
            Helper t(T);

            int s_integer_part_length = s.get_integer_part_length();
            int t_integer_part_length = t.get_integer_part_length();

            int s_decimal_part_length = s.get_decimal_part_length();
            int t_decimal_part_length = t.get_decimal_part_length();

            int s_repeating_part_length = s.get_repeating_part_length();
            int t_repeating_part_length = t.get_repeating_part_length();

            s.unroll(t_decimal_part_length);
            t.unroll(s_decimal_part_length);

            s.pad(t_integer_part_length);
            t.pad(s_integer_part_length);

            int common_integer_part_length = max(s_integer_part_length, t_integer_part_length);
            int common_decimal_part_length = max(s_decimal_part_length, t_decimal_part_length);
            int common_repeating_part_length = lcm(s_repeating_part_length, t_repeating_part_length);

            for (int i = 0; i < common_repeating_part_length; i++)
            {
                if (s.get_repeating_character(i) != t.get_repeating_character(i))
                {
                    return false;
                }
            }
            for (int i = common_decimal_part_length - 1; i >= 0; i--)
            {
                if (s.get_decimal_part_character(i) != t.get_decimal_part_character(i))
                {
                    return false;
                }
            }
            for (int i = common_integer_part_length - 1; i >= 0; i--)
            {
                if (s.get_integer_part_character(i) != t.get_integer_part_character(i))
                {
                    return false;
                }
            }
            return true;
        }
    private:
        int lcm(int a, int b)
        {
            return a * b / gcd(a, b);
        }
        int gcd(int a, int b)
        {
            if (b > a)
            {
                return gcd(b, a);
            }
            else if (b == 0)
            {
                return a;
            }
            else
            {
                return gcd(b, b % a);
            }

        }
    };
};

using namespace _LEET_EQUAL_RATIONAL_NUMBERS;

int LEET_EQUAL_RATIONAL_NUMBERS()
{
    Solution solution;
    cout << solution.isRationalEqual("0.(52)", "0.5(25)") << endl;
    cout << solution.isRationalEqual("0.1666(6)", "0.166(66)") << endl;
    cout << solution.isRationalEqual("0.9(9)", "1.") << endl;
    return 0;
}