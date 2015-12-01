#include "stdafx.h"

// https://leetcode.com/problems/word-pattern/

#include "LEET_WORD_PATTERN.h"
#include <map>
#include <string>
#include <iostream>

using namespace std;

namespace _LEET_WORD_PATTERN
{
    class Solution
    {
    private:
        bool match(map<char, string>& p_to_s, map<string, char>& s_to_p, char p, string s)
        {
            map<char, string>::iterator p_to_s_probe = p_to_s.find(p);
            map<string, char>::iterator s_to_p_probe = s_to_p.find(s);
            if (p_to_s_probe == p_to_s.end() && s_to_p_probe == s_to_p.end())
            {
                p_to_s.insert(pair<char, string>(p, s));
                s_to_p.insert(pair<string, char>(s, p));
                return true;
            }
            else if(p_to_s_probe != p_to_s.end() && s_to_p_probe != s_to_p.end())
            {
                return (p_to_s_probe->second == s) && (s_to_p_probe->second == p);
            }
            else
            {
                return false;
            }
        }
    public:
        bool wordPattern(string pattern, string str)
        {
            map<char, string> p_to_s;
            map<string, char> s_to_p;
            unsigned int s_i = 0;
            unsigned int p_i = 0;
            for (unsigned int s_e = 0; s_e < str.size(); s_e++)
            {
                if (str[s_e] == ' ')
                {
                    if (p_i < pattern.size())
                    {
                        if (match(p_to_s, s_to_p, pattern[p_i++], str.substr(s_i, s_e - s_i)))
                        {
                            s_i = s_e + 1;
                        }
                        else
                        {
                            return false;
                        }
                    }
                    else
                    {
                        return false;
                    }
                }
            }
            if (p_i < pattern.size())
            {
                if (!match(p_to_s, s_to_p, pattern[p_i++], str.substr(s_i, str.size() - s_i)))
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
            if (p_i != pattern.size())
            {
                return false;
            }
            return true;
        }
    };
};

using namespace _LEET_WORD_PATTERN;

int LEET_WORD_PATTERN()
{
    Solution solution;
    cout << solution.wordPattern("abba", "dog cat cat dog") << endl;
    cout << !solution.wordPattern("abba", "dog cat cat fish") << endl;
    cout << !solution.wordPattern("aaaa", "dog cat cat dog") << endl;
    cout << !solution.wordPattern("abba", "dog dog dog dog") << endl;
    return 0;
}