#include "stdafx.h"

// http://uva.onlinejudge.org/external/106/10651.html

#include "UVa10651.h"

#include <iostream>
#include <queue>

using namespace std;

int read_input()
{
    int game = 0;
    int bit = 1 << 11;
    for (int p = 0; p < 12; p++)
    {
        char c = cin.get();
        if (c == 'o')
        {
            game = game | bit;
        }
        bit = bit >> 1;
    }

    return game;
}

int UVa10651()
{
    int number_of_test_case;
    cin >> number_of_test_case;
    for (int c = 0; c < number_of_test_case; c++)
    {
        cin.get(); // eliminate the endline
        int game = read_input();
        bool enqueued[4096];
        queue<int> bfs_queue;
        for (int i = 0; i < 4096; i++)
        {
            enqueued[i] = false;
        }

        bfs_queue.push(game);
        enqueued[game] = true;

        int min_piece = 13; // there are at most 12 pieces, so this is basically infinitely

        while (!bfs_queue.empty())
        {
            int current = bfs_queue.front();
            bfs_queue.pop();
            int num_piece = 0;
            for (int p = 0; p < 12; p++)
            {
                if ((current & (1 << p)) != 0)
                {
                    num_piece++;
                }
            }
            min_piece = min(min_piece, num_piece);

            for (int p = 11; p >= 2; p--)
            {
                int m1 = 1 << p;
                int m2 = 1 << (p - 1);
                int m3 = 1 << (p - 2);

                // 1 1 0 case
                if (((current & m1) != 0) && ((current & m2) != 0) && ((current & m3) == 0))
                {
                    // 0 0 1
                    int new_game = current - m1 - m2 + m3;
                    if (!enqueued[new_game])
                    {
                        bfs_queue.push(new_game);
                        enqueued[new_game] = true;
                    }
                }

                // 0 1 1 case
                if (((current & m1) == 0) && ((current & m2) != 0) && ((current & m3) != 0))
                {
                    // 1 0 0
                    int new_game = current + m1 - m2 - m3;
                    if (!enqueued[new_game])
                    {
                        bfs_queue.push(new_game);
                        enqueued[new_game] = true;
                    }
                }
            }
        }

        cout << min_piece << endl;
    }

    return 0;
}