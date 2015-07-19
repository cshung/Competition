#include "stdafx.h"

// https://leetcode.com/problems/add-and-search-word-data-structure-design/

#include "LEET_ADD_AND_SEARCH_WORD.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_ADD_AND_SEARCH_WORD
{
    class WordDictionary 
    {
    private:
        class WordDictionaryNode
        {
        public:
            ~WordDictionaryNode()
            {
                for (map<char, WordDictionaryNode*>::iterator ci = this->children.begin(); ci != this->children.end(); ci++)
                {
                    delete ci->second;
                }
            }
            string label;
            map<char, WordDictionaryNode*> children;
        };
        WordDictionaryNode root;

        bool search_start(string& word, unsigned int i, WordDictionaryNode* current);
        bool search_child(string& word, unsigned int i, WordDictionaryNode* current);
    public:
        // Adds a word into the data structure.
        void addWord(string word)
        {
            word = word + '\0';
            int wordLength = word.length();
            WordDictionaryNode* current = &root;
            unsigned int i = 0;
            while (true)
            {
                map<char, WordDictionaryNode*>::iterator probe = current->children.find(word[i]);
                if (probe == current->children.end())
                {
                    WordDictionaryNode* newNode = new WordDictionaryNode();
                    current->children.insert(pair<char, WordDictionaryNode*>(word[i], newNode));
                    newNode->label = word.substr(i);
                    break;
                }
                else
                {
                    current = probe->second;
                    unsigned int j = 0;
                    for (;j < current->label.length() && i < word.length(); i++, j++)
                    {
                        if (word[i] != current->label[j])
                        {
                            break;
                        }
                    }
                    if (j != current->label.length())
                    {
                        // Split a node
                        string prefix = current->label.substr(0, j);
                        string old_suffix = current->label.substr(j);
                        string new_suffix = word.substr(i);

                        WordDictionaryNode* old_node = new WordDictionaryNode();
                        WordDictionaryNode* new_node = new WordDictionaryNode();

                        old_node->label = old_suffix;
                        new_node->label = new_suffix;
                        current->label = prefix;

                        for (map<char, WordDictionaryNode*>::iterator ci = current->children.begin(); ci != current->children.end(); ci++)
                        {
                            old_node->children.insert(*ci);
                        }
                        current->children.clear();
                        current->children.insert(pair<char, WordDictionaryNode*>(old_suffix[0], old_node));
                        current->children.insert(pair<char, WordDictionaryNode*>(new_suffix[0], new_node));
                        break;
                    }
                }
            }
        }

        // Returns if the word is in the data structure. A word could
        // contain the dot character '.' to represent any one letter.
        bool search(string word)
        {
            word = word + '\0';
            return search_child(word, 0, &root);
        }
    };

    bool WordDictionary::search_start(string& word, unsigned int i, WordDictionary::WordDictionaryNode* current)
    {
        for (unsigned int j = 0; i < word.length() && j < current->label.length(); i++, j++)
        {
            if (word[i] != '.' && word[i] != current->label[j])
            {
                return false;
            }
        }

        return search_child(word, i, current);
    }

    bool WordDictionary::search_child(string& word, unsigned int i, WordDictionary::WordDictionaryNode* current)
    {
        if (i == word.length())
        {
            return true;
        }

        if (word[i] == '.')
        {
            for (map<char, WordDictionary::WordDictionaryNode*>::iterator ci = current->children.begin(); ci != current->children.end(); ci++)
            {
                if (search_start(word, i, ci->second))
                {
                    return true;
                }
            }

            return false;
        }
        else
        {
            map<char, WordDictionary::WordDictionaryNode*>::iterator probe = current->children.find(word[i]);
            if (probe == current->children.end())
            {
                return false;
            }
            else
            {
                return search_start(word, i, probe->second);
            }
        }
    }
};

using namespace _LEET_ADD_AND_SEARCH_WORD;

int LEET_ADD_AND_SEARCH_WORD()
{
    WordDictionary dict;
    dict.addWord("bad");
    dict.addWord("dad");
    dict.addWord("mad");
    cout << (dict.search("pad") == 0) << endl;
    cout << (dict.search("bad") == 1) << endl;
    cout << (dict.search(".ad") == 1) << endl;
    cout << (dict.search("b..") == 1) << endl;
    return 0;
}