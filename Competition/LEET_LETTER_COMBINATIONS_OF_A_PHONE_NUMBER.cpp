#include "stdafx.h"

// https://leetcode.com/problems/letter-combinations-of-a-phone-number

#include "LEET_LETTER_COMBINATIONS_OF_A_PHONE_NUMBER.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_LETTER_COMBINATIONS_OF_A_PHONE_NUMBER
{
    class Solution
    {
    private:
        void letterCombinations(string& digits, char* buffer, int index, vector<string>& result)
        {
            if (index == digits.length())
            {
                result.push_back(buffer);
            }
            else
            {
                char digit = digits[index];
                switch (digit)
                {
                case '2':
                    buffer[index] = 'a'; letterCombinations(digits, buffer, index + 1, result);
                    buffer[index] = 'b'; letterCombinations(digits, buffer, index + 1, result);
                    buffer[index] = 'c'; letterCombinations(digits, buffer, index + 1, result);
                    break;
                case '3':
                    buffer[index] = 'd'; letterCombinations(digits, buffer, index + 1, result);
                    buffer[index] = 'e'; letterCombinations(digits, buffer, index + 1, result);
                    buffer[index] = 'f'; letterCombinations(digits, buffer, index + 1, result);
                    break;
                case '4':
                    buffer[index] = 'g'; letterCombinations(digits, buffer, index + 1, result);
                    buffer[index] = 'h'; letterCombinations(digits, buffer, index + 1, result);
                    buffer[index] = 'i'; letterCombinations(digits, buffer, index + 1, result);
                    break;
                case '5':
                    buffer[index] = 'j'; letterCombinations(digits, buffer, index + 1, result);
                    buffer[index] = 'k'; letterCombinations(digits, buffer, index + 1, result);
                    buffer[index] = 'l'; letterCombinations(digits, buffer, index + 1, result);
                    break;
                case '6':
                    buffer[index] = 'm'; letterCombinations(digits, buffer, index + 1, result);
                    buffer[index] = 'n'; letterCombinations(digits, buffer, index + 1, result);
                    buffer[index] = 'o'; letterCombinations(digits, buffer, index + 1, result);
                    break;
                case '7':
                    buffer[index] = 'p'; letterCombinations(digits, buffer, index + 1, result);
                    buffer[index] = 'q'; letterCombinations(digits, buffer, index + 1, result);
                    buffer[index] = 'r'; letterCombinations(digits, buffer, index + 1, result);
                    buffer[index] = 's'; letterCombinations(digits, buffer, index + 1, result);
                    break;
                case '8':
                    buffer[index] = 't'; letterCombinations(digits, buffer, index + 1, result);
                    buffer[index] = 'u'; letterCombinations(digits, buffer, index + 1, result);
                    buffer[index] = 'v'; letterCombinations(digits, buffer, index + 1, result);
                    break;
                case '9':
                    buffer[index] = 'w'; letterCombinations(digits, buffer, index + 1, result);
                    buffer[index] = 'x'; letterCombinations(digits, buffer, index + 1, result);
                    buffer[index] = 'y'; letterCombinations(digits, buffer, index + 1, result);
                    buffer[index] = 'z'; letterCombinations(digits, buffer, index + 1, result);
                    break;
                }
            }
        }
    public:
        vector<string> letterCombinations(string digits)
        {
            vector<string> result;
            if (digits.length() > 0)
            {
                char* buffer = new char[digits.length() + 1];
                buffer[digits.length()] = '\0';
                letterCombinations(digits, buffer, 0, result);
                delete[] buffer;
            }
            return result;
        }
    };
};

using namespace _LEET_LETTER_COMBINATIONS_OF_A_PHONE_NUMBER;

int LEET_LETTER_COMBINATIONS_OF_A_PHONE_NUMBER()
{
    Solution solution;
    vector<string> answer = solution.letterCombinations("23");
    for (size_t i = 0; i < answer.size(); i++)
    {
        cout << answer[i] << endl;
    }
    return 0;
}