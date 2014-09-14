#include "stdafx.h"
#pragma warning(disable : 4996)

// 

#include "UVa10281.h"

#include <iostream>
#include <string>

using namespace std;

int UVa10281()
{
    int current_second = 0;
    double current_speed = 0;
    double current_distance = 0;
    while (!cin.eof())
    {
        string line;
        getline(cin, line);
        if (line.length() < 8)
        {
            return 0;
        }
        string hour_part = line.substr(0, 2);
        string min_part  = line.substr(3, 2);
        string sec_part  = line.substr(6, 2);
        int hour = (hour_part[0] - '0') * 10 + (hour_part[1] - '0');
        int min  = (min_part[0]  - '0') * 10 + (min_part[1]  - '0');
        int sec  = (sec_part[0]  - '0') * 10 + (sec_part[1]  - '0');
        int second_elapsed = sec + min * 60 + hour * 60 * 60;

        int second_passed = second_elapsed - current_second;
        current_distance += current_speed * second_passed / 3600.0;

        bool isQuery = true;
        if (line.length() > 8)
        {
            string speed_part = line.substr(8);
            while (speed_part[0] == ' ')
            {
                speed_part = speed_part.substr(1);
            }
            if (speed_part.length() > 0)
            {
                sscanf(speed_part.c_str(), "%lf", &current_speed);
                isQuery = false;
            }
        }

        if (isQuery)
        {
            char buffer[1024];
            sprintf(buffer, "%.2f", current_distance);
            cout << hour_part << ":" << min_part << ":" << sec_part << " " << buffer << " km" << endl;
        }

        current_second = second_elapsed;
    }

    return 0;
}