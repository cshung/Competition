#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=414

#include "UVa473.h"

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct UVa473_State
{
public:
    int songs_recorded;
    bool reachable;
};

int UVa473()
{
    int number_of_test_cases;
    cin >> number_of_test_cases;
    for (int c = 0; c < number_of_test_cases; c++)
    {
        int number_of_songs;
        int time_per_disk;
        int number_of_disks;
        cin >> number_of_songs;
        cin >> time_per_disk;
        cin >> number_of_disks;
        vector<int> song_duration;
        for (int s = 0; s < number_of_songs; s++)
        {
            int song_time;
            cin >> song_time;
            song_duration.push_back(song_time);
            if (s != number_of_songs - 1)
            {
                char comma;
                cin >> comma;
            }
        }
        vector<vector<UVa473_State> > last_max_songs;
        vector<vector<UVa473_State> > max_songs;

        last_max_songs.resize(number_of_disks + 1);
        max_songs.resize(number_of_disks + 1);
        for (int d = 0; d <= number_of_disks; d++)
        {
            last_max_songs[d].resize(time_per_disk + 1);
            max_songs[d].resize(time_per_disk + 1);
        }

        // Initialization - the only achievable state at the beginning is all disk not recorded
        for (int d = 0; d <= number_of_disks; d++)
        {
            for (int t = 0; t <= time_per_disk; t++)
            {
                last_max_songs[d][t].songs_recorded = 0;
                last_max_songs[d][t].reachable = (d == number_of_disks) && (t == time_per_disk);
            }
        }

        for (int s = 0; s < number_of_songs; s++)
        {
            int current_song_duration = song_duration[s];

            // Initializing the max_songs with the not choosing the current song 
            for (int d = 0; d <= number_of_disks; d++)
            {
                for (int t = 0; t <= time_per_disk; t++)
                {
                    max_songs[d][t].reachable = last_max_songs[d][t].reachable;
                    max_songs[d][t].songs_recorded = last_max_songs[d][t].songs_recorded;
                }
            }

            for (int d = 0; d <= number_of_disks; d++)
            {
                for (int t = 0; t <= time_per_disk; t++)
                {
                    if (last_max_songs[d][t].reachable)
                    {
                        int current_disk = d;
                        int current_disk_remaining_time = t;
                        int current_song_recorded = last_max_songs[d][t].songs_recorded;
                        // Step 1: Consider if the current song can fit on the current disk
                        if (current_disk != 0 && current_disk_remaining_time >= current_song_duration)
                        {
                            // Yes it can, let see if that's a better deal
                            int new_disk = current_disk;
                            int new_current_disk_remaining_time = current_disk_remaining_time - current_song_duration;
                            int new_song_recorded = current_song_recorded + 1;
                            if (!max_songs[new_disk][new_current_disk_remaining_time].reachable ||
                                max_songs[new_disk][new_current_disk_remaining_time].songs_recorded < new_song_recorded)
                            {
                                max_songs[new_disk][new_current_disk_remaining_time].reachable = true;
                                max_songs[new_disk][new_current_disk_remaining_time].songs_recorded = new_song_recorded;
                            }
                        }
                        // Step 2: Consider if the current song can fit on the next disk
                        else if (current_disk > 1 && current_song_duration <= time_per_disk)
                        {
                            // Yes it can, let see if that's a better deal
                            int new_disk = current_disk - 1;
                            int new_current_disk_remaining_time = time_per_disk - current_song_duration;
                            int new_song_recorded = current_song_recorded + 1;
                            if (!max_songs[new_disk][new_current_disk_remaining_time].reachable ||
                                max_songs[new_disk][new_current_disk_remaining_time].songs_recorded < new_song_recorded)
                            {
                                max_songs[new_disk][new_current_disk_remaining_time].reachable = true;
                                max_songs[new_disk][new_current_disk_remaining_time].songs_recorded = new_song_recorded;
                            }
                        }
                    }
                }
            }

            for (int d = 0; d <= number_of_disks; d++)
            {
                for (int t = 0; t <= time_per_disk; t++)
                {
                    last_max_songs[d][t].reachable = max_songs[d][t].reachable;
                    last_max_songs[d][t].songs_recorded = max_songs[d][t].songs_recorded;
                }
            }
        }
        int max_songs_recorded = -1;
        for (int t = 0; t <= time_per_disk; t++)
        {
            max_songs_recorded = max(max_songs_recorded, max_songs[1][t].songs_recorded);
        }

        if (c != 0)
        {
            cout << endl;
        }
        cout << max_songs_recorded << endl;
    }
    return 0;
}