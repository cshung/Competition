#include "stdafx.h"

// https://leetcode.com/problems/regular-expression-matching/

#include "LEET_REGULAR_EXPRESSION_MATCHING.h"
#include <set>
#include <map>
#include <list>
#include <queue>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_REGULAR_EXPRESSION_MATCHING
{
    class Solution
    {
    private:
        class NfaEdge
        {
        public:
            NfaEdge(int from, int to, char c) : m_from(from), m_to(to), m_c(c)
            {
            }

            int m_from;
            int m_to;
            char m_c;
        };

        class TrieNode
        {
        public:
            TrieNode() : m_value(-1)
            {
            }

            ~TrieNode()
            {
                for (map<int, TrieNode*>::iterator mci = this->m_children.begin(); mci != this->m_children.end(); mci++)
                {
                    delete mci->second;
                }
            }
            map<int, TrieNode*> m_children;
            int m_value; // -1 represents a non-leaf
        };

        int get_epsilon_closure(set<int>& seeds, list<pair<char, int>>* nfa_adjacent_maps, TrieNode* subsetsRoot, map<int, set<int>>* subsets, int* currentDfaNode)
        {
            // Step 1: Find the epsilon_closure
            queue<int> bfs_queue;
            set<int> visited;
            for (set<int>::iterator si = seeds.begin(); si != seeds.end(); si++)
            {
                visited.insert(*si);
                bfs_queue.push(*si);
            }
            while (bfs_queue.size() > 0)
            {
                int current = bfs_queue.front();
                bfs_queue.pop();
                for (list<pair<char, int>>::iterator nami =  nfa_adjacent_maps[current].begin(); nami != nfa_adjacent_maps[current].end(); nami++)
                {
                    if (nami->first == '\0')
                    {
                        if (visited.find(nami->second) == visited.end())
                        {
                            visited.insert(nami->second);
                            bfs_queue.push(nami->second);
                        }
                    }
                }
            }

            // Step 2: Find or insert in the trie
            TrieNode* currentTrieNode = subsetsRoot;
            for (set<int>::iterator vi = visited.begin(); vi != visited.end(); vi++)
            {
                int currentNfaNode = *vi;
                map<int, TrieNode*>::iterator probe = currentTrieNode->m_children.find(currentNfaNode);
                if (probe == currentTrieNode->m_children.end())
                {
                    TrieNode* newTrieNode = new TrieNode();
                    currentTrieNode->m_children.insert(pair<int, TrieNode*>(currentNfaNode, newTrieNode));
                    currentTrieNode = newTrieNode;
                }
                else
                {
                    currentTrieNode = probe->second;
                }
            }

            if (currentTrieNode->m_value == -1)
            {
                currentTrieNode->m_value = ++(*currentDfaNode);
                subsets->insert(pair<int, set<int>>(currentTrieNode->m_value, visited));
            }

            return currentTrieNode->m_value;
        }

    public:
        bool isMatch(string s, string p)
        {
            int nfaNodeId = 0;
            set<int> characters;

            // Step 0: Construct the set of all characters
            for (unsigned int i = 0; i < p.length(); i++)
            {
                char pc = p[i];
                if (pc != '.')
                {
                    set<int>::iterator probe = characters.find(pc);
                    if (probe == characters.end())
                    {
                        characters.insert(pc);
                    }
                }
            }

            // Step 1: Construct the NFA
            list<NfaEdge> nfa_edges;
            int prevNodeId= 0;
            for (unsigned int i = 0; i < p.length(); i++)
            {
                char pc = p[i];
                bool star = false;
                if (i != p.length() - 1)
                {
                    star = p[i + 1] == '*';
                }

                int nextNodeId = ++nfaNodeId;

                nfa_edges.push_back(NfaEdge(prevNodeId, nextNodeId, pc));
                if (pc == '.')
                {
                    for (set<int>::iterator ci = characters.begin(); ci != characters.end(); ci++)
                    {
                        nfa_edges.push_back(NfaEdge(prevNodeId, nextNodeId, *ci));
                    }
                }

                if (star)
                {
                    nfa_edges.push_back(NfaEdge(prevNodeId, nextNodeId, '\0'));
                    nfa_edges.push_back(NfaEdge(nextNodeId, prevNodeId, '\0'));
                    nextNodeId = ++nfaNodeId;
                    nfa_edges.push_back(NfaEdge(nextNodeId - 1, nextNodeId, '\0'));
                    i++;

                }
                prevNodeId = nextNodeId;
            }

            int numNfaNodes = nfaNodeId + 1;

            // Step 2: To adjacency sets 
            list<pair<char, int>>* nfa_adjacent_maps = new list<pair<char, int>>[numNfaNodes];
            for (list<NfaEdge>::iterator nei = nfa_edges.begin(); nei != nfa_edges.end(); nei++)
            {
                nfa_adjacent_maps[nei->m_from].push_back(pair<char, int>(nei->m_c, nei->m_to));
            }

            // Step 3: Convert to a DFA using subset construction
            int currentDfaNode = -1;
            TrieNode* subsetsRoot = new TrieNode();
            map<int, set<int>> subsets;
            set<int> rootSeed;
            rootSeed.insert(0);
            int rootNode = get_epsilon_closure(rootSeed, nfa_adjacent_maps, subsetsRoot, &subsets, &currentDfaNode);

            map<int, map<char, int>> dfa;

            queue<int> bfs_queue;
            set<int> visited;
            bfs_queue.push(rootNode);
            visited.insert(rootNode);
            while (bfs_queue.size() > 0)
            {
                int current_node = bfs_queue.front();
                bfs_queue.pop();
                set<int>& subset = subsets[current_node];

                // Step 3.1: Create the branches
                map<char, set<int>> branch;
                for (set<int>::iterator si = subset.begin(); si != subset.end(); si++)
                {
                    int current_nfa_node = *si;
                    for (list<pair<char, int>>::iterator nami = nfa_adjacent_maps[current_nfa_node].begin(); nami != nfa_adjacent_maps[current_nfa_node].end(); nami++)
                    {
                        if (nami->first != '\0')
                        {
                            map<char, set<int>>::iterator probe1 = branch.find(nami->first);
                            if (probe1 == branch.end())
                            {
                                branch.insert(pair<char, set<int>>(nami->first, set<int>()));
                            }
                            set<int>& branchSet = branch[nami->first];
                            set<int>::iterator probe2 = branchSet.find(nami->second);
                            if (probe2 == branchSet.end())
                            {
                                branchSet.insert(nami->second);
                            }
                        }
                    }
                }

                // Step 3.2: Branches to the eplison closure of them
                for (map<char, set<int>>::iterator bi = branch.begin(); bi != branch.end(); bi++)
                {
                    int branchTargetDfaNode = get_epsilon_closure(bi->second, nfa_adjacent_maps, subsetsRoot, &subsets, &currentDfaNode);

                    map<int, map<char, int>>::iterator probe1 = dfa.find(current_node);
                    if (probe1 == dfa.end())
                    {
                        dfa.insert(pair<int, map<char, int>>(current_node, map<char, int>()));
                    }
                    map<int, map<char, int>>::iterator probe2 = dfa.find(branchTargetDfaNode);
                    if (probe2 == dfa.end())
                    {
                        dfa.insert(pair<int, map<char, int>>(branchTargetDfaNode, map<char, int>()));
                    }

                    char bc = bi->first;
                    if (bc == '.')
                    {
                        bc = '\0'; // In the DFA, we use '\0' to represent the other characters
                    }

                    dfa[current_node].insert(pair<char, int>(bc, branchTargetDfaNode));

                    if (visited.find(branchTargetDfaNode) == visited.end())
                    {
                        visited.insert(branchTargetDfaNode);
                        bfs_queue.push(branchTargetDfaNode);
                    }
                }
            }

            delete subsetsRoot;

            // Step 4: Run the DFA for the answer
            int currentState = 0;
            for (unsigned int si = 0; si < s.length(); si++)
            {
                char current_character = s[si];
                if (characters.find(current_character) == characters.end())
                {
                    current_character = '\0'; // This is an 'other' character, see if there is an allowed branch in the DFA
                }
                map<char, int>::iterator probe =  dfa[currentState].find(current_character);
                if (probe == dfa[currentState].end())
                {
                    return false;
                }
                else
                {
                    currentState = probe->second;
                }
            }

            return subsets[currentState].find(numNfaNodes - 1) != subsets[currentState].end();
        }
    };
};

using namespace _LEET_REGULAR_EXPRESSION_MATCHING;

int LEET_REGULAR_EXPRESSION_MATCHING()
{
    Solution s;
    cout << (s.isMatch("aa","a") == 0) << endl;
    cout << s.isMatch("aa","aa") << endl;
    cout << (s.isMatch("aaa","aa") == 0) << endl;
    cout << s.isMatch("aa", "a*") << endl;
    cout << s.isMatch("aa", ".*") << endl;
    cout << s.isMatch("ab", ".*") << endl;
    cout << s.isMatch("aab", "c*a*b") << endl;
    cout << (s.isMatch("ab", ".*c") == 0)   << endl;
    cout << (s.isMatch("aaa", "ab*a") == 0) << endl;

    return 0;
}