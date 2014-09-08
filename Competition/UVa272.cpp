#include "stdafx.h"

// TODO

#include "UVa272.h"

#include <iostream>

using namespace std;

int UVa272()
{
	bool inQuotes = false;
	while (!cin.eof())
	{
		char c = cin.get();
		if (c != -1)
		{
			if (c == '"')
			{
				if (inQuotes)
				{
					cout << "''";
					inQuotes = false;
				}
				else
				{
					cout << "``";
					inQuotes = true;
				}
			}
			else
			{
				cout << c;
			}
		}
	}

	return 0;
}