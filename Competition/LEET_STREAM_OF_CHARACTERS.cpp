#include "stdafx.h"

// https://leetcode.com/problems/stream-of-characters/

#include "LEET_STREAM_OF_CHARACTERS.h"
#include <map>
#include <iostream>
#include <unordered_map>
#include <queue>
#include <string>

using namespace std;

namespace _LEET_STREAM_OF_CHARACTERS
{
    class StreamChecker
    {
        class TrieNode
        {
        public:
            unordered_map<char, TrieNode*> m_children;
            TrieNode* m_failure;
            TrieNode* m_output;
            int m_pattern;
            TrieNode()
            {
                m_failure = nullptr;
                m_output = nullptr;
                m_pattern = -1;
            }
            ~TrieNode()
            {
                for (auto&& c : m_children)
                {
                    delete c.second;
                }
            }
            void add(string& s, int index)
            {
                this->add(0, s, index);
            }
            void add(int i, string& s, int index)
            {
                if (i == s.length())
                {
                    this->m_pattern = index;
                }
                else
                {
                    char first = s[i];
                    auto probe = this->m_children.find(first);
                    if (probe == this->m_children.end())
                    {
                        this->m_children.insert(make_pair(first, new TrieNode()));
                    }
                    this->m_children[first]->add(i + 1, s, index);
                }
            }
            void bfs(TrieNode* root)
            {
                queue<TrieNode*> parent;
                queue<char> character;
                queue<TrieNode*> bfs;
                parent.push(nullptr);
                character.push(' ');
                bfs.push(root);
                while (!bfs.empty())
                {
                    TrieNode* p = parent.front();
                    char c = character.front();
                    TrieNode* v = bfs.front();
                    parent.pop();
                    character.pop();
                    bfs.pop();
                    while (p != nullptr)
                    {
                        if (p == root)
                        {
                            break;
                        }
                        auto probe = p->m_failure->m_children.find(c);
                        if (probe != p->m_failure->m_children.end())
                        {
                            v->m_failure = probe->second;
                            if (v->m_failure->m_pattern != -1)
                            {
                                v->m_output = v->m_failure;
                            }
                            else if (v->m_failure->m_output != nullptr)
                            {
                                v->m_output = v->m_failure->m_output;
                            }
                            break;
                        }
                        p = p->m_failure;
                    }
                    if (v->m_failure == nullptr)
                    {
                        v->m_failure = root;
                    }
                    for (auto&& pair : v->m_children)
                    {
                        parent.push(v);
                        character.push(pair.first);
                        bfs.push(pair.second);
                    }
                }
            }
        };
    public:
        TrieNode* cursor;
        TrieNode* root;
        StreamChecker(vector<string>& words)
        {
            vector<pair<int, int>> result;
            this->root = new TrieNode();
            for (int i = 0; i < words.size(); i++)
            {
                this->root->add(words[i], i);
            }
            this->root->bfs(this->root);
            this->cursor = root;
        }

        ~StreamChecker()
        {
            delete this->root;
        }

        bool query(char letter) {
            bool found = false;
            bool advanced = false;
            char c = letter;
            while (!advanced)
            {
                auto probe = cursor->m_children.find(c);
                if (probe == cursor->m_children.end())
                {
                    if (cursor == root)
                    {
                        advanced = true;
                    }
                    else
                    {
                        cursor = cursor->m_failure;
                    }
                }
                else
                {
                    cursor = probe->second;
                    advanced = true;
                    if (cursor->m_pattern != -1)
                    {
                        found = true;
                    }
                    if (cursor->m_output != nullptr)
                    {
                        found = true;
                    }
                }
            }
            return found;
        }
    };
};

using namespace _LEET_STREAM_OF_CHARACTERS;

int LEET_STREAM_OF_CHARACTERS()
{
    string words_array[] = { "cd", "f", "kl" };
    vector<string> words(words_array, words_array + _countof(words_array));
    StreamChecker streamChecker(words);        // init the dictionary.
    cout << streamChecker.query('a') << endl;  // return false
    cout << streamChecker.query('b') << endl;  // return false
    cout << streamChecker.query('c') << endl;  // return false
    cout << streamChecker.query('d') << endl;  // return true, because 'cd' is in the wordlist
    cout << streamChecker.query('e') << endl;  // return false
    cout << streamChecker.query('f') << endl;  // return true, because 'f' is in the wordlist
    cout << streamChecker.query('g') << endl;  // return false
    cout << streamChecker.query('h') << endl;  // return false
    cout << streamChecker.query('i') << endl;  // return false
    cout << streamChecker.query('j') << endl;  // return false
    cout << streamChecker.query('k') << endl;  // return false
    cout << streamChecker.query('l') << endl;  // return true, because 'kl' is in the wordlist
    return 0;
}