#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1361

#include "UVa10420.h"

#include <iostream>
#include <string>
#include <map>

using namespace std;

int UVa10420()
{
    string dummy;
    int number_of_beauties;
    cin >> number_of_beauties;
    getline(cin, dummy);
    
    map<string, int> num_beauties_by_country;
    for (int b = 0; b < number_of_beauties; b++)
    {
        string beauty_line;
        string beauty_country;
        getline(cin, beauty_line);
        for (unsigned int i =0; i < beauty_line.length(); i++)
        {
            if (beauty_line[i] == ' ') 
            {
                beauty_country = beauty_line.substr(0, i);
                break;
            }
        }

        map<string, int>::iterator probe = num_beauties_by_country.find(beauty_country);
        if (probe == num_beauties_by_country.end())
        {
            num_beauties_by_country.insert(pair<string, int>(beauty_country, 1));
        }
        else
        {
            num_beauties_by_country[beauty_country]++;
        }
    }

    // TODO: Double check if this actually give sorted results
    for (map<string, int>::iterator c = num_beauties_by_country.begin(); c != num_beauties_by_country.end(); c++)
    {
        cout << c->first << " " << c->second << endl;
    }

    return 0;
}