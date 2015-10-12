#include "stdafx.h"

// https://leetcode.com/problems/multiply-strings/

#include "LEET_MULTIPLY_STRINGS.h"
#include <iostream>
#include <string>
#include <cassert>
#include <algorithm>

using namespace std;

namespace _LEET_MULTIPLY_STRINGS
{
// #define LOG
    class Solution
    {
    public:
        void add_with_shift(
            char* input1, int input1_s, int input1_e,
            char* input2, int input2_s, int input2_e, int input2_shift,
            char* answer, int answer_s, int answer_e)
        {
            int carry = 0;
            int input1_index = input1_e - 1;
            int input2_index = input2_e - 1;
            int answer_index = answer_e - 1;
            int shift_down_counter = input2_shift;

            while (input1_index >= input1_s || input2_index >= input2_s || carry != 0)
            {
                int digit1 = -1;
                if (input1_index >= input1_s)
                {
                    digit1 = input1[input1_index--] - '0';
                }
                else
                {
                    digit1 = 0;
                }

                int digit2 = -1;
                if (shift_down_counter > 0)
                {
                    shift_down_counter--;
                    digit2 = 0;
                }
                else if (input2_index >= input2_s)
                {
                    digit2 = input2[input2_index--] - '0';
                }
                else
                {
                    digit2 = 0;
                }
                int sum = digit1 + digit2 + carry;
                carry = sum / 10;
                assert(carry <= 1);
                sum -= carry * 10;

                if (answer_index < answer_s)
                {
                    assert(sum == 0);
                }
                else
                {
                    answer[answer_index--] = sum + '0';
                }
            }
            while (answer_index >= answer_s)
            {
                answer[answer_index--] = '0';
            }
        }

        void sub_with_shift(
            char* input1, int input1_s, int input1_e,
            char* input2, int input2_s, int input2_e, int input2_shift,
            char* answer, int answer_s, int answer_e)
        {
            int borrow = 0;
            int input1_index = input1_e - 1;
            int input2_index = input2_e - 1;
            int answer_index = answer_e - 1;
            int shift_down_counter = input2_shift;

            while (input1_index >= input1_s || input2_index >= input2_s || borrow != 0)
            {
                int digit1 = -1;
                if (input1_index >= input1_s)
                {
                    digit1 = input1[input1_index--] - '0';
                }
                else
                {
                    digit1 = 0;
                }

                int digit2 = -1;
                if (shift_down_counter > 0)
                {
                    shift_down_counter--;
                    digit2 = 0;
                }
                else if (input2_index >= input2_s)
                {
                    digit2 = input2[input2_index--] - '0';
                }
                else
                {
                    digit2 = 0;
                }
                int diff = digit1 - digit2 - borrow;
                borrow = 0;
                while (diff < 0)
                {
                    diff += 10;
                    borrow++;
                }
                assert(borrow <= 1);

                if (answer_index < answer_s)
                {
                    assert(diff == 0);
                }
                else
                {
                    answer[answer_index--] = diff + '0';
                }
            }
            while (answer_index >= answer_s)
            {
                answer[answer_index--] = '0';
            }
        }

        void multiply
            (
            char* input1, int input1_s, int input1_e,
            char* input2, int input2_s, int input2_e,
            char* answer, int answer_e,
            int recursion_depth
            )
        {
            int size = input1_e - input1_s;
            assert(size == input2_e - input2_s);
            // TODO: Consider a larger base case to better leverage hardware!
            if (size == 1)
            {
                int digit1 = input1[input1_s] - '0';
                int digit2 = input2[input2_s] - '0';
                int product = digit1 * digit2;
                answer[answer_e - 1] = product % 10 + '0';
                answer[answer_e - 2] = product / 10 + '0';
            }
            else if (size == 2)
            {
                int num1 = (input1[input1_s] - '0') * 10 + (input1[input1_s + 1] - '0');
                int num2 = (input2[input2_s] - '0') * 10 + (input2[input2_s + 1] - '0');
                int product = num1 * num2;
                int a = product / 1000;
                product -= a * 1000;
                int b = product / 100;
                product -= b * 100;
                int c = product / 10;
                product -= c * 10;
                int d = product;
                answer[answer_e - 4] = a + '0';
                answer[answer_e - 3] = b + '0';
                answer[answer_e - 2] = c + '0';
                answer[answer_e - 1] = d + '0';
            }
            else
            {
                /*
                 * n = number of digits in b and d
                 *
                 *   (10^n a + b)(10^n c + d)
                 * = 10^2n ac + 10^n (ad + bc) + bd
                 * = 10^2n ac + 10^n ((a + b)(c + d) - ac - bd) + bd
                 */
                int input1_m = (input1_s + input1_e) / 2;
                int input2_m = (input2_s + input2_e) / 2;
#ifdef LOG
                for (int i = 0; i < recursion_depth; i++) { cout << "  "; }; cout << "a = "; for (int i = input1_s; i < input1_m; i++) { cout << input1[i]; } cout << endl; 
                for (int i = 0; i < recursion_depth; i++) { cout << "  "; }; cout << "b = "; for (int i = input1_m; i < input1_e; i++) { cout << input1[i]; } cout << endl;
                for (int i = 0; i < recursion_depth; i++) { cout << "  "; }; cout << "c = "; for (int i = input2_s; i < input1_m; i++) { cout << input2[i]; } cout << endl; 
                for (int i = 0; i < recursion_depth; i++) { cout << "  "; }; cout << "d = "; for (int i = input2_m; i < input2_e; i++) { cout << input2[i]; } cout << endl;
#endif
                for (int i = 0; i < answer_e; i++)
                {
                    answer[i] = '0';
                }

                int upper_part_length = input1_m - input1_s;
                int lower_part_length = input1_e - input1_m;

                assert(upper_part_length == input2_m - input2_s);
                assert(lower_part_length == input2_e - input2_m);
                assert(lower_part_length >= upper_part_length);

                char* amc = new char[2 * upper_part_length];
                char* bmd = new char[2 * lower_part_length];
                char* apb = new char[lower_part_length + 1];
                char* cpd = new char[lower_part_length + 1];
                char* apbmcpd = new char[lower_part_length * 2 + 2];

                // Computing a x c
                this->multiply(input1, input1_s, input1_m, input2, input2_s, input2_m, amc, upper_part_length * 2, recursion_depth + 1);
#ifdef LOG
                for (int i = 0; i < recursion_depth; i++) { cout << "  "; }; cout << "a x c = "; for (int i = 0; i < upper_part_length * 2; i++) { cout << amc[i]; } cout << endl;
#endif
                // Computing b x d
                this->multiply(input1, input1_m, input1_e, input2, input2_m, input2_e, bmd, lower_part_length * 2, recursion_depth + 1);
#ifdef LOG
                for (int i = 0; i < recursion_depth; i++) { cout << "  "; }; cout << "b x d = "; for (int i = 0; i < lower_part_length * 2; i++) { cout << bmd[i]; } cout << endl;
#endif
                this->add_with_shift(answer, 0, answer_e, amc, 0, upper_part_length * 2, lower_part_length * 2, answer, 0, answer_e);
#ifdef LOG
                for (int i = 0; i < recursion_depth; i++) { cout << "  "; }; cout << "answer (1) = "; for (int i = 0; i < answer_e; i++) { cout << answer[i]; } cout << endl;
#endif

                this->add_with_shift(answer, 0, answer_e, bmd, 0, lower_part_length * 2, 0, answer, 0, answer_e);
#ifdef LOG
                for (int i = 0; i < recursion_depth; i++) { cout << "  "; }; cout << "answer (2) = "; for (int i = 0; i < answer_e; i++) { cout << answer[i]; } cout << endl;
#endif
                this->add_with_shift(input1, input1_s, input1_m, input1, input1_m, input1_e, 0, apb, 0, lower_part_length + 1);

                this->add_with_shift(input2, input2_s, input2_m, input2, input2_m, input2_e, 0, cpd, 0, lower_part_length + 1);

                // TODO: Be careful of buffer overrun here
                // This leading zero removal is critical, without that the program will run out of stack
                int leadingZero = 0;
                while (apb[leadingZero] == '0' && cpd[leadingZero] == '0')
                {
                    leadingZero++;
                }

#ifdef LOG
                for (int i = 0; i < recursion_depth; i++) { cout << "  "; }; cout << "a + b = "; for (int i = leadingZero; i < lower_part_length + 1; i++) { cout << apb[i]; } cout << endl;
                for (int i = 0; i < recursion_depth; i++) { cout << "  "; }; cout << "c + d = "; for (int i = leadingZero; i < lower_part_length + 1; i++) { cout << cpd[i]; } cout << endl;
#endif
                this->multiply(
                    apb, leadingZero, lower_part_length + 1,
                    cpd, leadingZero, lower_part_length + 1,
                    apbmcpd, (lower_part_length + 1 - leadingZero) * 2,
                    recursion_depth + 1);
#ifdef LOG
                for (int i = 0; i < recursion_depth; i++) { cout << "  "; }; cout << "(a + b) x (c + d) = "; for (int i = 0; i < (lower_part_length + 1 - leadingZero) * 2; i++) { cout << apbmcpd[i]; } cout << endl;
#endif
                this->sub_with_shift(apbmcpd, 0, (lower_part_length + 1 - leadingZero) * 2, amc, 0, upper_part_length * 2, 0, apbmcpd, 0, (lower_part_length + 1 - leadingZero) * 2);
#ifdef LOG
                for (int i = 0; i < recursion_depth; i++) { cout << "  "; }; cout << "(a + b) x (c + d) - ac = "; for (int i = 0; i < (lower_part_length + 1 - leadingZero) * 2; i++) { cout << apbmcpd[i]; } cout << endl;
#endif
                this->sub_with_shift(apbmcpd, 0, (lower_part_length + 1 - leadingZero) * 2, bmd, 0, lower_part_length * 2, 0, apbmcpd, 0, (lower_part_length + 1 - leadingZero) * 2);
#ifdef LOG
                for (int i = 0; i < recursion_depth; i++) { cout << "  "; }; cout << "(a + b) x (c + d) - ac - bd = "; for (int i = 0; i < (lower_part_length + 1 - leadingZero) * 2; i++) { cout << apbmcpd[i]; } cout << endl;
#endif
                this->add_with_shift(answer, 0, answer_e, apbmcpd, 0, (lower_part_length + 1 - leadingZero) * 2, lower_part_length, answer, 0, answer_e);
#ifdef LOG
                for (int i = 0; i < recursion_depth; i++) { cout << "  "; }; cout << "answer (5) = "; for (int i = 0; i < answer_e; i++) { cout << answer[i]; } cout << endl;
#endif
                delete[] amc;
                delete[] bmd;
                delete[] apb;
                delete[] cpd;
                delete[] apbmcpd;
            }
        }

        string multiply(string num1, string num2)
        {
            int num1_pad = 0;
            int num2_pad = 0;
            int size = 0;
            if (num1.size() > num2.size())
            {
                num2_pad = num1.size() - num2.size();
                size = num1.size();
            }
            else
            {
                num1_pad = num2.size() - num1.size();
                size = num2.size();
            }

            char* input1 = new char[size];
            char* input2 = new char[size];
            char* answer = new char[size * 2];

            for (int i = 0; i < num1_pad; i++) { input1[i] = '0'; }
            for (int i = 0; i < num1.size(); i++) { input1[i + num1_pad] = num1[i]; }
            for (int i = 0; i < num2_pad; i++) { input2[i] = '0'; }
            for (int i = 0; i < num2.size(); i++) { input2[i + num2_pad] = num2[i]; }

            this->multiply(input1, 0, size, input2, 0, size, answer, size * 2, 0);
            
            int leadingZero = 0;
            while (answer[leadingZero] == '0' && leadingZero < size * 2 - 1)
            {
                leadingZero++;
            }

            string result = string(answer + leadingZero, answer + size * 2);
            delete[] input1;
            delete[] input2;
            delete[] answer;
            return result;
        }
    };
};

using namespace _LEET_MULTIPLY_STRINGS;

int LEET_MULTIPLY_STRINGS()
{
    Solution s;
    // cout << s.multiply("2", "3") << endl;
    cout << (s.multiply("3284324385937593", "579837574598437") == "1904374686136554873066717342141") << endl;
    return 0;
}