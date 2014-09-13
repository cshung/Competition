#include "stdafx.h"
#pragma warning(disable : 4996)

// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=10&page=show_problem&problem=778

#include "UVa837.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <stdio.h>

using namespace std;

const unsigned long long raw_positive_infinity = 0x7ff0000000000000;
const unsigned long long raw_negative_infinity = 0xfff0000000000000;
const double positive_infinity = *(double*)&raw_positive_infinity;
const double negative_infinity = *(double*)&raw_negative_infinity;

struct segment_endpoint
{
    double x;
    double transparency;
    bool isEnter;
	int segment_id;
};

bool compare_segment(segment_endpoint* first, segment_endpoint* second)
{
    return first->x < second->x;
}

double to_double(string s)
{
    if (s == "+inf")
    {
        return positive_infinity;
    }
    else if (s == "-inf")
    {
        return negative_infinity;
    }
    else
    {
        double result;
        sscanf(s.c_str(), "%lf", &result);
        return result;
    }
}

string to_my_string(double value)
{
    if (value == positive_infinity)
    {
        return "+inf";
    }
    else if (value == negative_infinity)
    {
        return "-inf";
    }
    else
    {
        char buffer[1024];
        sprintf(buffer, "%#.3f", value);
        return string(buffer);
    }
}

int UVa837()
{
    int number_of_cases;
    cin >> number_of_cases;
    for (int c = 0; c < number_of_cases; c++)
    {
        string s;
        getline(cin, s);
        int number_of_flims;
        cin >> number_of_flims;
		vector<double> segment_transparencies;
		vector<bool> segment_state;
        vector<segment_endpoint*> endpoints;
		int segment_counter = 0;
        for (int i = 0; i < number_of_flims; i++)
        {
            string ix1, iy1, ix2, iy2, ir;
            double x1, y1, x2, y2, r;
            cin >> ix1 >> iy1 >> ix2 >> iy2 >> ir;

            x1 = to_double(ix1);
            y1 = to_double(iy1);
            x2 = to_double(ix2);
            y2 = to_double(iy2);
            r = to_double(ir);

			if (y1 <= 0 && y2 <= 0 && (y1 + y2 < 0))
			{
				// A segment under x-axis can simply be ignored
				continue;
			}

			if (y1 * y2 <= 0)
			{
				if (y1 != 0 || y2 != 0)
				{
					// A segment crossing (or touching) x-axis
					// (x2-x1)/(y2-y1) = (cx - x1)/(0 - y1)
					double cx = x1 - y1 * (x2 - x1) / (y2 - y1);
					if (y1 <= 0)
					{
						x1 = cx;
						y1 = 0;
					}
					else if (y2 <= 0)
					{
						x2 = cx;
						y2 = 0;
					}
				}
			}

            segment_endpoint* start = new segment_endpoint();
            segment_endpoint* end = new segment_endpoint();
			start->segment_id = segment_counter;
            start->x = min(x1, x2);
			end->segment_id = segment_counter;
            end->x = max(x1, x2);
            start->transparency = r;
            end->transparency = r;
            start->isEnter = true;
            end->isEnter = false;
            endpoints.push_back(start);
            endpoints.push_back(end);
			segment_counter++;
			segment_transparencies.push_back(r);
			segment_state.push_back(false);
        }

		if (endpoints.size() == 0)
		{
			cout << "-inf +inf 1.000";
		}
		else
		{
			sort(endpoints.begin(), endpoints.end(), compare_segment);
			vector<pair<double, double> > results;

			for (vector<segment_endpoint*>::iterator p = endpoints.begin(); p != endpoints.end(); p++)
			{
				segment_endpoint* endpoint = *p;
				if (endpoint->isEnter)
				{
					segment_state[endpoint->segment_id] = true;
				}
				else
				{
					segment_state[endpoint->segment_id] = false;
				}

				double current_transparency = 1;
				for (int i = 0; i < segment_transparencies.size(); i++)
				{
					if (segment_state[i])
					{
						current_transparency *= segment_transparencies[i];
					}
				}

				results.push_back(pair<double, double>(endpoint->x, current_transparency));
				delete endpoint;
			}

			// results is a list of (x, t), where I expect after x, the transparency is t
			// Now I need t to transform it into segments
			// consider a walk from -inf to +inf
			double current_position = negative_infinity;
			double current_transparency = 1.0;

			int count = results.size();
			if (results.begin()->first == negative_infinity)
			{
				count--;
			}
			if (results.rbegin()->first != positive_infinity)
			{
				count++;
			}
			cout << count << endl;
			int printed = 0;
			for (vector<pair<double, double> >::iterator p = results.begin(); p != results.end(); p++)
			{
				pair<double, double> event_point = *p;
				if (p->first > current_position)
				{
					cout << to_my_string(current_position) << " " << to_my_string(event_point.first) << " " << to_my_string(current_transparency);
					current_position = event_point.first;
					printed++;
					if (printed != count)
					{
						cout << endl;
					}
				}
				current_transparency = event_point.second;
			}
			if (current_position != positive_infinity)
			{
				cout << to_my_string(current_position) << " " << to_my_string(positive_infinity) << " " << to_my_string(1.0);
			}
		}
        if (c != (number_of_cases - 1))
        {
            cout << endl;
            cout << endl;
        }
    }

	cout << endl;
    return 0;
}