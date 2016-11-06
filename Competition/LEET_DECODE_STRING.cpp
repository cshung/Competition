#include "stdafx.h"

// https://leetcode.com/problems/decode-string/

#include "LEET_DECODE_STRING.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_DECODE_STRING
{
    class Solution
    {
    private:
        // position pointing at the next unscaned character
        int p;
        // 1: string
        // 2: number
        // 3: [
        // 4: ]
        // 5: eof
        int token_type;
        int n;
        string t;

        void scan(string& text)
        {
            if (p == text.length())
            {
                token_type = 5;
            }
            else if (text[p] == '[')
            {
                token_type = 3;
                p++;
            }
            else if (text[p] == ']')
            {
                token_type = 4;
                p++;
            }
            else if ('0' <= text[p] && text[p] <= '9')
            {
                this->n = 0;
                token_type = 2;
                while (p != text.length() && '0' <= text[p] && text[p] <= '9')
                {
                    n *= 10;
                    n += (text[p] - '0');
                    p++;
                }
            }
            else
            {
                this->token_type = 1;
                this->t = "";
                while (p != text.length() && text[p] != '[' && text[p] != ']' && !('0' <= text[p] && text[p] <= '9'))
                {
                    t += text[p];
                    p++;
                }
            }
        }

        class command
        {
        public:
            virtual void execute(ostringstream& sout) = 0;
        };
        class string_command : public command
        {
        public:
            string_command(string s) { this->s = s; }
            string s;
            virtual void execute(ostringstream& sout)
            {
                sout << s;
            }
        };
        class repeat_command : public command
        {
        public:
            repeat_command(int times, vector<command*> body)
            {
                this->times = times;
                this->body = body;
            }
            int times;
            vector<command*> body;

            virtual void execute(ostringstream& sout)
            {
                for (int i = 0; i < this->times; i++)
                {
                    for (auto&& command : this->body)
                    {
                        command->execute(sout);
                    }
                }
            }
        };
    public:
        string decodeString(string s)
        {
            this->p = 0;
            this->scan(s);
            vector<command*> commands = parseInput(s);
            ostringstream sout;
            for (auto&& command : commands)
            {
                command->execute(sout);
            }
            return sout.str();
        }

        vector<command*> parseInput(string& s)
        {
            vector<command*> result;
            while (true)
            {
                if (this->token_type == 5 || this->token_type == 4)
                {
                    return result;
                }
                else if (this->token_type == 1)
                {
                    result.push_back(new string_command(t));
                    this->scan(s);
                }
                else if (this->token_type == 2)
                {
                    int r = n;
                    this->scan(s);
                    if (this->token_type == 3)
                    {
                        this->scan(s);
                        vector<command*> recursive_result = parseInput(s);
                        if (this->token_type == 4)
                        {
                            this->scan(s);
                            result.push_back(new repeat_command(r, recursive_result));
                        }
                        else
                        {
                            throw 2;
                        }
                    }
                    else
                    {
                        throw 1;
                    }
                }
            }

        }

    };
};

using namespace _LEET_DECODE_STRING;

int LEET_DECODE_STRING()
{
    Solution solution;
    cout << solution.decodeString("3[a]2[bc]") << endl;
    cout << solution.decodeString("3[a2[c]]") << endl;
    cout << solution.decodeString("2[abc]3[cd]ef") << endl;
    return 0;
}