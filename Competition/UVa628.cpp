#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=569 

#include "UVa628.h"

#include <iostream>
#include <string>
#include <map>
#include <list>

using namespace std;

void generate(string rule, int index, list<string>& dictionary, list<string> generated)
{
    if (index == rule.length())
    {
        for (list<string>::iterator gi = generated.begin(); gi != generated.end(); gi++)
        {
            cout << *gi;
        }
        cout << endl;
    }
    else
    {
        if (rule[index] == '0')
        {
            for (int i = 0; i < 10; i++)
            {
                string d = " ";
                d[0] = (char)(i + '0');
                generated.push_back(d);
                generate(rule, index + 1, dictionary, generated);
                generated.pop_back();
            }
        }
        else
        {
            for (list<string>::iterator di = dictionary.begin(); di != dictionary.end(); di++)
            {
                generated.push_back(*di);
                generate(rule, index + 1, dictionary, generated);
                generated.pop_back();
            }
        }
    }
}

int UVa628()
{
    while (true)
    {
        int number_of_words;
        int number_of_rules;
        list<string> dictionary;
        list<string> rules;
        cin >> number_of_words;
        if (cin.fail())
        {
            break;
        }
        for (int i = 0; i < number_of_words; i++)
        {
            string word;
            cin >> word;
            dictionary.push_back(word);
        }
        cin >> number_of_rules;
        for (int i = 0; i < number_of_rules; i++)
        {
            string rule;
            cin >> rule;
            rules.push_back(rule);
        }
        cout << "--" << endl;
        for (list<string>::iterator ri = rules.begin(); ri != rules.end(); ri++)
        {
            list<string> generated;
            generate(*ri, 0, dictionary, generated);
        }
    }
    return 0;
}