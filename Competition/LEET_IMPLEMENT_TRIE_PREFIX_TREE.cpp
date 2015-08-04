#include "stdafx.h"

// https://leetcode.com/problems/implement-trie-prefix-tree/

#include "LEET_IMPLEMENT_TRIE_PREFIX_TREE.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_IMPLEMENT_TRIE_PREFIX_TREE
{
    class TrieNode
    {
    public:
        map<char, TrieNode*> children;

        // Initialize your data structure here.
        TrieNode()
        {

        }

        ~TrieNode()
        {
            for (map<char, TrieNode*>::iterator ci = this->children.begin(); ci != this->children.end(); ci++)
            {
                delete ci->second;
            }
        }
    };

    class Trie {
    private:
        TrieNode* root;

        TrieNode* run(string word, bool create)
        {
            TrieNode* current = this->root;
            for (unsigned int i = 0; i < word.size(); i++)
            {
                map<char, TrieNode*>::iterator probe = current->children.find(word[i]);
                if (probe == current->children.end())
                {
                    if (create)
                    {
                        TrieNode* newNode = new TrieNode();
                        current->children.insert(pair<char, TrieNode*>(word[i], newNode));
                        current = newNode;
                    }
                    else
                    {
                        return NULL;
                    }
                }
                else
                {
                    current = probe->second;
                }
            }

            return current;
        }
    public:
        Trie()
        {
            this->root = new TrieNode();
        }

        // Inserts a word into the trie.
        void insert(string word)
        {
            this->run(word + '\0', true);
        }

        // Returns if the word is in the trie.
        bool search(string word)
        {
            TrieNode* current = this->run(word + '\0', false);
            return current != NULL && current->children.size() == 0;
        }

        // Returns if there is any word in the trie
        // that starts with the given prefix.
        bool startsWith(string prefix)
        {
            TrieNode* current = this->run(prefix, false);
            return current != NULL;
        }
    };
};

using namespace _LEET_IMPLEMENT_TRIE_PREFIX_TREE;

int LEET_IMPLEMENT_TRIE_PREFIX_TREE()
{
    Trie trie;
    trie.insert("some");
    trie.insert("something");
    cout << trie.startsWith("ksom") << endl;
    return 0;
}