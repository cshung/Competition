#include "stdafx.h"

// TODO

#include "UVa483.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
* This problem has two simple subproblem - tokenizing the string - and to reverse a string.
* Tokenizing the string is easy - maintain a start pointer, and advance an end pointer until we see a space.
* Found the token - Move the end pointer until it is no longer space - we locate the start pointer of the next 
* token, and so on. Special care needed on the beginning and the ending of the string.
*
* Reversing a string is simple too. Since the problem does not talk about input size, we assume the worst, that
* the input is large, but good enough for us to buffer a line. Then we do reverse in place. To reverse in place
* swap the begin and end character, and advance the begin pointer and end pointer towards the center, do that until 
* the begin pointer start to equals or get larger than the end pointer.
*/
int UVa483()
{
	while (!cin.eof())
	{
		string s;
		getline(cin, s);
		unsigned int start = 0;
		for (unsigned int i = 0; i < s.length(); i++)
		{
			if (s[i] == ' ' || i == s.length() - 1)
			{
				if (i == s.length() - 1)
				{
					i++;
				}

				if (start < i)
				{
					int wordBegin = start;
					int wordEnd = i-1;
					while (wordBegin < wordEnd)
					{
						char temp = s[wordBegin] ;
						s[wordBegin] = s[wordEnd];
						s[wordEnd] = temp;
						wordBegin++;
						wordEnd--;
					}
				}

				while (s[i] == ' ')
				{
					i++;
				}

				start = i;
			}
		}
		cout << s << endl;
	}

	return 0;
}