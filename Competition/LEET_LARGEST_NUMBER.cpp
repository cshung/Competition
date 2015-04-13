#include "stdafx.h"

// https://leetcode.com/problems/count-and-say/

#include "LEET_LARGEST_NUMBER.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_LARGEST_NUMBER
{
    class Solution
    {
    public:
        string largestNumber(vector<int> &num)
        {
            // Step 1: Convert all numbers into string for easy access
            int n = num.size();
            vector<string> num_strings;
            
            for (int i = 0; i < n; i++)
            {
                stringstream iss;
                iss << num[i];
                num_strings.push_back(iss.str());
            }

            // Step 2: Build the trie 
            TrieNode root;
            TrieNode* current_node;
            for (int i = 0; i < n; i++)
            {
                const string& current_string = num_strings[i];
                current_node = &root;
                for (unsigned int j = 0; j < current_string.length(); j++)
                {
                    int current_digit = current_string[j] - '0';
                    TrieNode* next_node = current_node->children[current_digit];
                    if (next_node == NULL)
                    {
                        next_node = new TrieNode();
                        current_node->children[current_digit] = next_node;
                    }

                    current_node->refCounts[current_digit]++;
                    current_node = next_node;
                }
                current_node->isLeaf = true;
            }

            // Step 3: Walking on the trie greedily for a solution
            ostringstream rss;
            current_node = &root;
            while (true)
            {
                int best_digit = -1;
                for (int i = 9; i >= 0; i--)
                {
                    if (current_node->children[i] != 0)
                    {
                        best_digit = i;
                        break;
                    }
                }

                if (best_digit == -1)
                {
                    if (current_node->isLeaf)
                    {
                        current_node->isLeaf = false;
                        current_node = &root;
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    if (current_node->isLeaf)
                    {
                        // Consider finding a way to cache this
                        int best_root_choice = -1;
                        for (int j = 9; j > best_digit; j--)
                        {
                            if (root.children[j] != NULL)
                            {
                                best_root_choice = j;
                                break;
                            }
                        }

                        if (best_root_choice != -1)
                        {
                            current_node->isLeaf = false;
                            current_node = &root;
                        }
                        else
                        {
                            rss << best_digit;
                            TrieNode* next_node = current_node->children[best_digit];
                            current_node->refCounts[best_digit]--;
                            if (current_node->refCounts[best_digit] == 0)
                            {
                                current_node->children[best_digit] = NULL;
                            }
                            current_node = next_node;
                        }
                    }
                    else
                    {
                        rss << best_digit;
                        TrieNode* next_node = current_node->children[best_digit];
                        current_node->refCounts[best_digit]--;
                        if (current_node->refCounts[best_digit] == 0)
                        {
                            current_node->children[best_digit] = NULL;
                        }
                        current_node = next_node;
                    }
                }
            }

            return rss.str();
        }
    private:
        class TrieNode
        {
        public:
            TrieNode()
            {
                this->children = new TrieNode*[10];
                this->refCounts = new int[10];
                this->isLeaf = false;
                for (int i = 0; i < 10; i++)
                {
                    this->children[i] = NULL;
                    this->refCounts[i] = 0;
                }
            }
            TrieNode** children;
            int* refCounts; 
            bool isLeaf;
            void Dump(int depth)
            {
                for (int i = 0; i < 10; i++)
                {
                    if (children[i] != NULL)
                    {
                        for (int j = 0; j < depth; j++)
                        {
                            cout << " ";
                        }
                        cout << i;
                        if (children[i]->isLeaf)
                        {
                            cout << "*";
                        }
                        cout << endl;
                        children[i]->Dump(depth + 2);
                    }
                }
            }
        };
    };
};

using namespace _LEET_LARGEST_NUMBER;

int LEET_LARGEST_NUMBER()
{
    Solution solution;
    vector<int> input;
    input.push_back(12);
    input.push_back(121);
    cout << solution.largestNumber(input) << endl;
    return 0;
}