#include "stdafx.h"

// https://leetcode.com/problems/goat-latin/

#include "LEET_GOAT_LATIN.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_GOAT_LATIN
{
    class Solution
    {
    public:
        string toGoatLatin(string S)
        {
            string vowels = "aeiouAEIOU";
            vector<char> w;
            int i = 0;
            int count = 0;
            ostringstream oss;
            for (int i = 0; i <= S.length(); i++)
            {
                char c = i == S.length() ? ' ' : S[i];
                if (c == ' ')
                {
                    if (count != 0)
                    {
                        oss << " ";
                    }
                    bool move = vowels.find(w[0]) == string::npos;
                    bool first = true;
                    for (auto wc : w)
                    {
                        if (first)
                        {
                            first = false;
                            if (!move)
                            {
                                oss << wc;
                            }
                        }
                        else
                        {
                            oss << wc;
                        }
                    }
                    if (move)
                    {
                        oss << w[0];
                    }
                    oss << "ma";
                    count++;
                    for (int j = 0; j < count; j++)
                    {
                        oss << "a";
                    }
                    w.clear();
                }
                else
                {
                    w.push_back(c);
                }
            }

            return oss.str();
        }
    };
};

using namespace _LEET_GOAT_LATIN;

int LEET_GOAT_LATIN()
{
    Solution solution;
    cout << solution.toGoatLatin("I speak Goat Latin") << endl;
    cout << solution.toGoatLatin("The quick brown fox jumped over the lazy dog") << endl;
    return 0;
}