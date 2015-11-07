#include "stdafx.h"

// https://leetcode.com/problems/bulls-and-cows/

#include "LEET_BULLS_AND_COWS.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

namespace _LEET_BULLS_AND_COWS
{
    class Solution
    {
    public:
        string getHint(string secret, string guess)
        {
            map<char, int> mismatchedSecrets;
            map<char, int> mismatchedGuesses;
            int bullCount = 0;
            for (unsigned int i = 0; i < secret.length(); i++)
            {
                if (secret[i] == guess[i])
                {
                    bullCount++;
                }
                else
                {
                    if (mismatchedGuesses.find(guess[i]) == mismatchedGuesses.end())
                    {
                        mismatchedGuesses.insert(pair<char, int>(guess[i], 1));
                    }
                    else
                    {
                        mismatchedGuesses[guess[i]]++;
                    }
                    if (mismatchedSecrets.find(secret[i]) == mismatchedSecrets.end())
                    {
                        mismatchedSecrets.insert(pair<char, int>(secret[i], 1));
                    }
                    else
                    {
                        mismatchedSecrets[secret[i]]++;
                    }
                }
            }

            int cowCount = 0;
            for (map<char, int>::iterator msi = mismatchedSecrets.begin(); msi != mismatchedSecrets.end(); msi++)
            {
                char secret = msi->first;
                map<char, int>::iterator mgi = mismatchedGuesses.find(secret);
                if (mgi != mismatchedGuesses.end())
                {
                    int secretCount = msi->second;
                    int guessCount = mgi->second;
                    cowCount += min(secretCount, guessCount);
                }
            }

            ostringstream sout;
            sout << bullCount << "A" << cowCount << "B";
            return sout.str();
        }
    };
};

using namespace _LEET_BULLS_AND_COWS;

int LEET_BULLS_AND_COWS()
{
    Solution solution;
    cout << solution.getHint("111000", "000111") << endl;
    return 0;
}