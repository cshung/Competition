#include "stdafx.h"

// http://www.spoj.com/problems/PALIN/

#include "SPOJ_PALIN.h"

#include <iostream>
#include <string>

using namespace std;

static void processInput(string input)
{
    int length = input.length();
    bool isChainOf9 = true;
    for (unsigned int i = 0; isChainOf9 && i < input.length(); i++)
    {
        if (input[i] != '9') {
            isChainOf9 = false;
        }
    }
    if (isChainOf9)
    {
        cout << 1;
        for (unsigned int i = 0; i < input.length() - 1; i++)
        {
            cout << 0;
        }
        cout << 1;
    }
    else
    {
        int half = length / 2;

        int leftReversePointer = half - 1;      // For example, if length is 4, then leftReversePointer = 1, rightPointer = 2
        int rightPointer = half + length % 2;   // For example, if length is 5, then leftReversePointer = 1, rightPointer = 3
        int leftReverseCompareright = 0;
        while ((leftReverseCompareright == 0) && leftReversePointer >= 0)
        {
            if (input[leftReversePointer] > input[rightPointer])
            {
                leftReverseCompareright = 1;
            }
            else if (input[leftReversePointer] < input[rightPointer])
            {
                leftReverseCompareright = -1;
            }
            leftReversePointer--;
            rightPointer++;
        }

        if (length % 2 == 0)
        {
            if (leftReverseCompareright == 1)
            {
                for (int i = 0; i < half; i++)
                {
                    cout << input[i];                   // For example, 0 to 1
                }
                for (int i = 0; i < half; i++)
                {
                    cout << input[half - 1 - i];        // For example 1 to 0
                }
            }
            else
            {
                int leftLsbPointer = half - 1;
                while (true)
                {
                    if (input[leftLsbPointer] == '9')
                    {
                        input[leftLsbPointer] = '0';
                        leftLsbPointer--;
                    }
                    else
                    {
                        input[leftLsbPointer]++;
                        break;
                    }
                }
                for (int i = 0; i < half; i++)
                {
                    cout << input[i];                   // For example, 0 to 1
                }
                for (int i = 0; i < half; i++)
                {
                    cout << input[half - 1 - i];        // For example 1 to 0
                }
            }
        }
        else
        {
            // Odd length sequences
            char middle = input[length / 2];
            if (leftReverseCompareright == 1)
            {
                for (int i = 0; i < half; i++)
                {
                    cout << input[i];                   // For example, 0 to 1
                }
                cout << middle;
                for (int i = 0; i < half; i++)
                {
                    cout << input[half - 1 - i];             // For example 1 to 0
                }
            }
            else
            {
                if (middle != '9')
                {
                    // 1st, left (middle + 1) reverse(left) is a next palindrome
                    // 2nd, decreasing any digit on the right will decrease digit on the left, so it is no longer a valid next palindrome.
                    // 3rd, decreasing the middle digit it is no longer a valid next palindrome.
                    // 4th, therefore this is the next palindrome
                    for (int i = 0; i < half; i++)
                    {
                        cout << input[i];                   // For example, 0 to 1
                    }
                    cout << (char)(middle + 1);
                    for (int i = 0; i < half; i++)
                    {
                        cout << input[half - 1 - i];             // For example 1 to 0
                    }
                }
                else
                {
                    int leftLsbPointer = half - 1;
                    while (true)
                    {
                        if (input[leftLsbPointer] == '9')
                        {
                            input[leftLsbPointer] = '0';
                            leftLsbPointer--;
                        }
                        else
                        {
                            input[leftLsbPointer]++;
                            break;
                        }
                    }
                    for (int i = 0; i < half; i++)
                    {
                        cout << input[i];                   // For example, 0 to 1
                    }
                    cout << 0;
                    for (int i = 0; i < half; i++)
                    {
                        cout << input[half - 1 - i];             // For example 1 to 0
                    }
                }
            }
        }
    }
    cout << endl;
}

int SPOJ_PALIN()
{
    int round;
    cin >> round;
    for (int roundCount = 0; roundCount < round; roundCount++)
    {
        string input;
        cin >> input;
        processInput(input);
    }

    return 0;
}