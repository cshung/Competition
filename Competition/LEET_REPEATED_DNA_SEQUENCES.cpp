#include "stdafx.h"

// https://leetcode.com/problems/repeated-dna-sequences/

#include "LEET_REPEATED_DNA_SEQUENCES.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_REPEATED_DNA_SEQUENCES
{
    class Solution
    {
    public:
        vector<string> findRepeatedDnaSequences(string s)
        {
            map<int, int> seen_signatures;
            vector<string> result;
            int current_signature = 0;
            for (int i = 0; i < s.length(); i++)
            {
                current_signature = current_signature << 2;
                current_signature = current_signature & 0x000FFFFF;
                if (s[i] == 'A')
                {
                    current_signature = current_signature | 0x00000000;
                }
                else if (s[i] == 'C')
                {
                    current_signature = current_signature | 0x00000001;
                }
                else if (s[i] == 'T')
                {
                    current_signature = current_signature | 0x00000002;
                }
                else if (s[i] == 'G')
                {
                    current_signature = current_signature | 0x00000003;
                }
                if (i >= 9)
                {
                    map<int, int>::iterator probe = seen_signatures.find(current_signature);
                    if (probe == seen_signatures.end())
                    {
                        seen_signatures.insert(pair<int, int>(current_signature, i - 9));
                    }
                    else
                    {
                        if (probe->second != -1)
                        {
                            result.push_back(s.substr(probe->second, 10));
                            probe->second = -1;
                        }
                    }
                }
            }

            return result;
        }
    };
};

using namespace _LEET_REPEATED_DNA_SEQUENCES;

int LEET_REPEATED_DNA_SEQUENCES()
{
    Solution solution;
    vector<string> result = solution.findRepeatedDnaSequences("AAAAAAAAAAAA");
    for (unsigned int i = 0; i < result.size(); i++)
    {
        cout << result[i] << endl;
    }
    return 0;
}
