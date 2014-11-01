#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1611

#include "UVa10670.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Agency
{
    string s;
    int reduce_one_price;
    int reduce_half_price;
    int min_cost;
};

bool less_agency(Agency first, Agency second)
{
    if (first.min_cost != second.min_cost)
    {
        return first.min_cost < second.min_cost;
    }
    else
    {
        return first.s < second.s;
    }
}

int UVa10670()
{
    int num_cases;
    cin >> num_cases;
    for (int c = 0; c < num_cases; c++)
    {
        int workload, target, num_agencies;
        cin >> workload;
        cin >> target;
        cin >> num_agencies;

        vector<Agency> agencies;
        for (int i = 0; i < num_agencies; i++)
        {
            Agency agency;
            char c = cin.get(); // Consume the endline
            while (true)
            {
                c = cin.get();
                if (c != ':')
                {
                    agency.s.push_back(c);
                }
                else
                {
                    break;
                }
            }
            cin >> agency.reduce_one_price;
            cin >> c;
            cin >> agency.reduce_half_price;
            agencies.push_back(agency);
        }

        for (vector<Agency>::iterator ai = agencies.begin(); ai != agencies.end(); ai++)
        {
            ai->min_cost = 0;
            int remaining_work = workload;
            while (remaining_work > target)
            {
                if (remaining_work / 2 >= target)
                {
                    int work_done = remaining_work - remaining_work / 2;
                    int reduce_one_plan_price = ai->reduce_one_price * work_done;
                    int reduce_half_plan_price = ai->reduce_half_price;
                    if (reduce_half_plan_price < reduce_one_plan_price)
                    {
                        remaining_work -= work_done;
                        ai->min_cost += reduce_half_plan_price;
                    }
                    else
                    {
                        // If half prices is not better than one price now, it will never be.
                        ai->min_cost += ai->reduce_one_price * (remaining_work - target);
                        remaining_work = target;
                    }
                } else
                {
                    // If reducing half is doing more than target, it will always be
                    ai->min_cost += ai->reduce_one_price * (remaining_work - target);
                    remaining_work = target;
                }
            }
        }

        sort(agencies.begin(), agencies.end(), less_agency);
        cout << "Case " << (c + 1) << endl;
        for (vector<Agency>::iterator ai = agencies.begin(); ai != agencies.end(); ai++)
        {
            cout << ai->s << " " << ai->min_cost << endl;
        }
    }

    return 0;
}