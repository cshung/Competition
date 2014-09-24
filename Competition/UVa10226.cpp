#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1167

#include "UVa10226.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <map>

using namespace std;

int UVa10226()
{
    string dummy;
    int number_of_cases;
    cin >> number_of_cases;
    getline(cin, dummy); /* Consume the endline */
    getline(cin, dummy); /* Consume the blank line*/
    for (int i = 0; i < number_of_cases; i++)
    {
        map<string, int> tree_count;
        int count = 0;
        while (true)
        {
            string tree;
            getline(cin, tree);
            if (tree.length() == 0)
            {
                break;
            }
            map<string, int>::iterator probe = tree_count.find(tree);
            if (probe == tree_count.end())
            {
                tree_count.insert(pair<string, int>(tree, 1));
            }
            else
            {
                tree_count[tree]++;
            }
            count++;
        }
        double factor = 100.0 / count;
        std::cout << std::setprecision(4) << std::fixed;
        for (map<string, int>::iterator ti = tree_count.begin(); ti != tree_count.end(); ti++)
        {
            cout << ti->first << " " << ti->second * factor << endl;
        }

        if (i != number_of_cases - 1)
        {
            cout << endl; // The required blank line between test cases
        }
    }
    return 0;
}