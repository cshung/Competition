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
    class Node
    {
    public:
        Node()
        {
            this->a = this->c = this->t = this->g = NULL;
        }
        ~Node()
        {
            if (this->a != NULL) { delete this->a; }
            if (this->c != NULL) { delete this->c; }
            if (this->t != NULL) { delete this->t; }
            if (this->g != NULL) { delete this->g; }
        }
        Node* a;
        Node* c;
        Node* t;
        Node* g;
    };

    class Solution
    {
    public:
        vector<string> findRepeatedDnaSequences(string s)
        {
            vector<string> result;
            Node* root = new Node();
            for (int i = s.length() - 10; i >= 0; i--)
            {
                bool used_new = false;
                Node* cursor = root;
                for (unsigned int j = i; j < i + 10; j++)
                {
                    if (s[j] == 'A')
                    {
                        if (cursor->a == NULL)
                        {
                            used_new = true;
                            cursor->a = new Node();
                        }

                        cursor = cursor->a;
                    } 
                    else if (s[j] == 'C')
                    {
                        if (cursor->c == NULL)
                        {
                            used_new = true;
                            cursor->c = new Node();
                        }

                        cursor = cursor->c;
                    }
                    else if (s[j] == 'T')
                    {
                        if (cursor->t == NULL)
                        {
                            used_new = true;
                            cursor->t = new Node();
                        }

                        cursor = cursor->t;
                    }
                    else if (s[j] == 'G')
                    {
                        if (cursor->g == NULL)
                        {
                            used_new = true;
                            cursor->g = new Node();
                        }

                        cursor = cursor->g;
                    }
                }

                if (!used_new)
                {
                    string t = s.substr(i, 10);
                    result.push_back(t);
                }
            }

            delete root;
            return result;
        }
    };
};

using namespace _LEET_REPEATED_DNA_SEQUENCES;

int LEET_REPEATED_DNA_SEQUENCES()
{
    Solution solution;
    vector<string> result = solution.findRepeatedDnaSequences("AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT");
    for (unsigned int i = 0; i < result.size(); i++)
    {
        cout << result[i] << endl;
    }
    return 0;
}
