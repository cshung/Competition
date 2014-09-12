#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=9&page=show_problem&problem=680

#include "UVa739.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

static int digit(char c)
{
	switch (c)
	{
	case 'B':
	case 'P':
	case 'F':
	case 'V':
		return 1;
	case 'C':
	case 'S':
	case 'K':
	case 'G':
	case 'J':
	case 'Q':
	case 'X':
	case 'Z':
		return 2;
	case 'D':
	case 'T':
		return 3;
	case 'L':
		return 4;
	case 'M':
	case 'N':
		return 5;
	case 'R':
		return 6;
	default:
		return 0;
	}
}

int UVa739()
{
	//       1234567890123456789012345678901234567890123456789
	cout << "         NAME                     SOUNDEX CODE" << endl;
	while (!cin.eof())
	{
		string name;
		cin >> name;
		if (name.length() > 0)
		{
			//       123456789
			cout << "         " << name;
			int spentColumn = name.length();
			while (spentColumn < 25)
			{
				cout << " ";
				spentColumn++;
			}
			cout << name[0] ;
			int lastDigitCode = digit(name[0]);
			int emitted_digit_count = 0;
			for (unsigned int i = 1; emitted_digit_count < 3 && i < name.length(); i++)
			{
				int currentDigitCode = digit(name[i]);
				if (currentDigitCode != 0)
				{
					if (currentDigitCode != lastDigitCode)
					{
						emitted_digit_count++;
						cout << currentDigitCode;
					}
				}
				lastDigitCode = currentDigitCode;
			}

			while (emitted_digit_count < 3)
			{
				cout << 0;
				emitted_digit_count++;
			}

			cout << endl;
		}
	}

	//       12345678901234567890
	cout << "                   END OF OUTPUT" << endl;
	return 0;
}