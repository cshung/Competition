#include "stdafx.h"

// https://leetcode.com/problems/special-binary-string

#include "LEET_SPECIAL_BINARY_STRING.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_SPECIAL_BINARY_STRING
{
#define LOG

    struct Bracket
    {
        vector<Bracket*> children;
        Bracket* parent;
        int height;
        size_t s;
        size_t e;
    };

    int compare(const Bracket* a, const Bracket* b)
    {
        if (a->height == a->height)
        {
            for (int i = 0; i < a->children.size() && i < b->children.size(); i++)
            {
                int result = compare(a->children[i], b->children[i]);
                if (result != 0)
                {
                    return result;
                }
            }
            return a->children.size() - b->children.size();
        }
        else
        {
            return a->height - b->height;
        }
    }

    class Solution
    {
    public:
        void sortByHeight(Bracket* node)
        {
            node->height = 1;
            for (auto child : node->children)
            {
                sortByHeight(child);
                node->height = max(node->height, child->height + 1);
            }
            sort(node->children.begin(), node->children.end(), [](const Bracket* a, const Bracket* b) -> bool
            {
                return compare(a, b) > 0;
            });
        }
        
        void build(Bracket* node, ostringstream& sb, bool skip)
        {
            if (!skip)
            {
                node->s = sb.tellp();
                sb << "1";
            }
            for (auto child : node->children)
            {
                build(child, sb, false);
            }
            if (!skip)
            {
                node->e = sb.tellp();
                sb << "0";
            }
        }

#ifdef LOG
        void print(Bracket* node, string t)
        {
            for (int h = node->height - 1; h > 0; h--)
            {
                for (size_t i = 0; i < t.size(); i++)
                {
                    t[i] = ' ';
                }
                print(node, t, h);
                cout << t << endl;
            }
        }

        void print(Bracket* node, string& t, int height)
        {
            if (node->height > height)
            {
                for (auto child : node->children)
                {
                    print(child, t, height);
                }
            }
            else if (node->height == height)
            {
                t[node->s] = '(';
                t[node->e] = ')';
            }
        }
#endif

        string makeLargestSpecial(string s)
        {
            Bracket* root = new Bracket();
            Bracket* current = root;
            for (size_t i = 0; i < s.size(); i++)
            {
                if (s[i] == '1')
                {
                    Bracket* new_bracket = new Bracket();
                    new_bracket->s = i;
                    new_bracket->parent = current;
                    current->children.push_back(new_bracket);
                    current = new_bracket;
                }
                else
                {
                    current->e = i;
                    current = current->parent;
                }
            }
            sortByHeight(root);
#ifdef LOG
            print(root, s);
#endif
            ostringstream sb;
            build(root, sb, true);
#ifdef LOG
            print(root, s);
#endif
            return sb.str();
        }
    };
};

using namespace _LEET_SPECIAL_BINARY_STRING;

int LEET_SPECIAL_BINARY_STRING()
{
    Solution solution;
    cout << solution.makeLargestSpecial("1101001110001101010110010010") << endl;
    return 0;
}