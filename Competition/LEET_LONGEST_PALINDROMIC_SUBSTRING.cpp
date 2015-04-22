#include "stdafx.h"

// https://leetcode.com/problems/longest-palindromic-substring/

#include "LEET_LONGEST_PALINDROMIC_SUBSTRING.h"

#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <string>

using namespace std;

namespace _LEET_LONGEST_PALINDROMIC_SUBSTRING
{
    class Solution
    {
    public:
        string longestPalindrome(string s)
        {
            TrieNode root;
            int length = s.length();
            
            // Build a suffix trie
            for (int i = 0; i < length; i++)
            {
                TrieNode* current = &root;
                for (int j = i; j < length; j++)
                {
                    char current_char = s[j];
                    TrieNode* next = NULL;
                    map<char, TrieNode*>::iterator probe = current->children.find(current_char);
                    if (probe == current->children.end())
                    {
                        next = new TrieNode();
                        current->children.insert(pair<char, TrieNode*>(current_char, next));
                    }
                    else
                    {
                        next = probe->second;
                    }

                    current = next;
                }
            }

            string best = "";

            // For each prefix, try to walk the trie, but don't create nodes
            for (int i = length ; i >= 0; i--)
            {
                TrieNode* current = &root;
                string path = "";
                for (int j = i - 1; j >= 0; j--)
                {
                    char current_char = s[j];
                    TrieNode* next = NULL;
                    map<char, TrieNode*>::iterator probe = current->children.find(current_char);
                    if (probe == current->children.end())
                    {
                        if (path.length() > best.length())
                        {
                            best = path;
                        }
                        break;
                    }
                    else
                    {
                        path = path + current_char;
                        next = probe->second;
                    }

                    current = next;
                }
            }

            return best;
        }
    private:
        class TrieNode
        {
        public:
            map<char, TrieNode*> children;
        };
    };
};

using namespace _LEET_LONGEST_PALINDROMIC_SUBSTRING;

int LEET_LONGEST_PALINDROMIC_SUBSTRING()
{
    Solution solution;
    string s;
    for (int i = 0; i < 1000; i++)
    {
        s = s + 'x';
    }
    cout << s << endl;
    cout << solution.longestPalindrome(s) << endl;
    return 0;
}