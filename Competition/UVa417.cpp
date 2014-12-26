#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=358

#include "UVa417.h"

#include <iostream>
#include <string>
#include <queue>

using namespace std;

int UVa417()
{
    while (true)
    {
        string s;
        cin >> s;
        if (cin.eof())
        {
            break;
        }
        bool valid = true;
        for (unsigned int i = 1; i < s.length(); i++)
        {
            if (s[i] <= s[i - 1])
            {
                valid = false;
                break;
            }
        }
        if (valid)
        {
            queue<string> bfs_queue;
            bfs_queue.push("");
            int count = 0;
            while (true)
            {
                string v = bfs_queue.front();
                if (v == s)
                {
                    break;
                }
                count++;
                bfs_queue.pop();
                if (v == "")
                {
                    for (char c = 'a'; c <= 'z'; c++)
                    {
                        char s[2];
                        s[0] = c;
                        s[1] = 0;
                        bfs_queue.push(s);
                    }
                }
                else
                {
                    char last = v[v.length() - 1];
                    for (char next = last + 1; next <= 'z'; next++)
                    {
                        bfs_queue.push(v + next);
                    }
                }
            }
            cout << count << endl;
        }
        else
        {
            cout << 0 << endl;
        }
    }
    return 0;
}