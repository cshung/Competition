#include "stdafx.h"

// TODO

#include "UVa483.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int UVa483()
{
    vector<char> charSeen;
    while (true)
	{
        char c = cin.get();
        if (c == ' ' || c == '\r' || c == '\n' || c == -1)
        {
            for (vector<char>::reverse_iterator p = charSeen.rbegin(); p != charSeen.rend(); p++)
            {
                cout << (*p);
            }
            charSeen.clear();
            if (c != -1)
            {
                cout << c;
            }
            else
            {
                break;
            }
        }
        else
        {
            charSeen.push_back(c);
        }
	}

	return 0;
}