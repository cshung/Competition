#include "stdafx.h"

// https://leetcode.com/problems/text-justification/

#include "LEET_TEXT_JUSTIFICATION.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_TEXT_JUSTIFICATION
{
	class Solution {
	public:
		vector<string> fullJustify(vector<string>& words, int maxWidth)
		{
			vector<string> result;
			int packed_size = -1;
			size_t from = 0;
			char* line = new char[maxWidth + 1];

			// Note the loop also go through one index outside of the words vector
			for (size_t i = 0; i <= words.size(); i++)
			{
				bool is_last_word = i == words.size();
				int additional_size = is_last_word ? 0 : (words[i].length() + 1);
				int l = 0;
				if (((packed_size + additional_size) > maxWidth) || is_last_word)
				{
					// Emit a line with words coming from [from, i)
					int numWords = i - from;
					if ((numWords == 1) || is_last_word)
					{
						// Emit left justified
						for (int j = from; j < i; j++)
						{
							// Emit all words
							for (int k = 0; k < words[j].length(); k++)
							{
								line[l++] = words[j][k];
							}
							// between each word, emit a space
							if (j != i - 1)
							{
								line[l++] = ' ';
							}
						}

						// Emit spaces until we reach the end
						for (; l < maxWidth; l++)
						{
							line[l] = ' ';
						}
					}
					else
					{
						// Emit full justified
						int numGaps = numWords - 1;
						int numSpaces = maxWidth - packed_size + numGaps;
						int smallGaps = numSpaces / numGaps;
						int numBigGaps = numSpaces % numGaps;
						for (int j = from; j < i; j++)
						{
							// Emit all words
							for (int k = 0; k < words[j].length(); k++)
							{
								line[l++] = words[j][k];
							}
	
							if (j != i - 1)
							{
								// between each word, emit a small gap
								for (int k = 0; k < smallGaps; k++)
								{
									line[l++] = ' ';
								}
								// Emit one more space for big gaps
								if (j - from < numBigGaps)
								{
									line[l++] = ' ';
								}
							}
						}
					}

					// Null terminate the line
					line[maxWidth] = '\0';
					result.push_back(line);

					// The next iteration will consider word (i + 1), so we account for the word i here
					from = i;
					packed_size = additional_size - 1;
				}
				else
				{
					packed_size += additional_size;
				}
			}
			return result;
		}
	};
};

using namespace _LEET_TEXT_JUSTIFICATION;

int LEET_TEXT_JUSTIFICATION()
{
	Solution solution;
	vector<string> words;
	words.push_back("But");
	words.push_back("soft!");
	words.push_back("What"); 
	words.push_back("light");
	words.push_back("through");
	words.push_back("yonder"); 
	words.push_back("window"); 
	words.push_back("breaks?");
	words.push_back("It"); 
	words.push_back("is"); 
	words.push_back("the"); 
	words.push_back("East,");
	words.push_back("and"); 
	words.push_back("Juliet");
	words.push_back("is"); 
	words.push_back("the");
	words.push_back("sun!"); 
	words.push_back("Arise,");
	words.push_back("fair"); 
	words.push_back("sun,"); 
	words.push_back("and"); 
	words.push_back("kill"); 
	words.push_back("the"); 
	words.push_back("envious"); 
	words.push_back("moon,"); 
	words.push_back("who"); 
	words.push_back("is"); 
	words.push_back("already");
	words.push_back("sick"); 
	words.push_back("and"); 
	words.push_back("pale"); 
	words.push_back("with"); 
	words.push_back("grief"); 
	words.push_back("That"); 
	words.push_back("thou"); 
	words.push_back("her"); 
	words.push_back("maid");
	words.push_back("art");
	words.push_back("far");
	words.push_back("more");
	words.push_back("fair");
	words.push_back("than");
	words.push_back("she.");

	vector<string> result = solution.fullJustify(words, 20);
	for (size_t i = 0; i < result.size(); i++)
	{
		cout << result[i] << endl;
	}
	return 0;
}