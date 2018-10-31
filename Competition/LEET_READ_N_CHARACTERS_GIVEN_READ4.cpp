#include "stdafx.h"

// https://leetcode.com/problems/read-n-characters-given-read4

#include "LEET_READ_N_CHARACTERS_GIVEN_READ4.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_READ_N_CHARACTERS_GIVEN_READ4
{
    // Forward declaration of the read4 API.
    int read4(char *buf);

    class Solution
    {
    public:
        /**
         * @param buf Destination buffer
         * @param n   Maximum number of characters to read
         * @return    The number of characters read
         */
        int read(char *buf, int n)
        {
            int count = 0;
            char data[4];
            while (true)
            {
                int data_count = read4(data);
                if (data_count == 0)
                {
                    break;
                }
                if (count == n)
                {
                    break;
                }
                for (int i = 0; i < data_count && count < n; i++)
                {
                    buf[count++] = data[i];
                }
            }
            return count;
        }
    };

    class Data
    {
    public:
        Data(const char* data) : m_data(data)
        {
            this->m_length = strlen(this->m_data) + 1;
            this->m_cursor = 0;
        }

        int read4(char* buf)
        {
            int count = this->m_length - this->m_cursor;
            count = min(count, 4);
            for (int i = 0; i < count; i++)
            {
                buf[i] = *(this->m_data + m_cursor);
                m_cursor++;
            }
            return count;
        }
    private:
        const char* m_data;
        int m_length;
        int m_cursor;
    };

    Data data("Leetcode is awesome");

    int read4(char* buf)
    {
        return data.read4(buf);
    }
};

using namespace _LEET_READ_N_CHARACTERS_GIVEN_READ4;

int LEET_READ_N_CHARACTERS_GIVEN_READ4()
{
    Solution solution;
    char data[20];
    cout << solution.read(data, 20) << endl;
    cout << data << endl;
    return 0;
}