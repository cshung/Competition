#include "stdafx.h"

// https://leetcode.com/problems/data-stream-as-disjoint-intervals/

#include "LEET_DATA_STREAM_AS_DISJOINT_INTERVALS.h"
#include <map>
#include <set>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_DATA_STREAM_AS_DISJOINT_INTERVALS
{
    struct Interval
    {
        int start;
        int end;
        Interval() : start(0), end(0) {}
        Interval(int s, int e) : start(s), end(e) {}
    };
    class SummaryRanges
    {
    private:
        set<int> seen;
        map<int, Interval> intervals_by_s;
        map<int, Interval> intervals_by_e;
    public:
        SummaryRanges()
        {

        }

        void addNum(int val)
        {
            set<int>::iterator seen_probe = this->seen.find(val);
            if (seen_probe != this->seen.end())
            {
                return;
            }
            else
            {
                this->seen.insert(val);
            }

            map<int, Interval>::iterator s_probe = this->intervals_by_s.find(val + 1);
            map<int, Interval>::iterator e_probe = this->intervals_by_e.find(val - 1);

            int new_interval_s = val;
            int new_interval_e = val;

            bool s_probe_found = s_probe != this->intervals_by_s.end();
            bool e_probe_found = e_probe != this->intervals_by_e.end();

            if (s_probe_found)
            {
                Interval old_interval = s_probe->second;
                new_interval_e = old_interval.end;
                this->intervals_by_s.erase(old_interval.start);
                this->intervals_by_e.erase(old_interval.end);
            }

            if (e_probe_found)
            {
                Interval old_interval = e_probe->second;
                new_interval_s = old_interval.start;
                this->intervals_by_s.erase(old_interval.start);
                this->intervals_by_e.erase(old_interval.end);
            }

            Interval new_interval(new_interval_s, new_interval_e);
            this->intervals_by_s.insert(pair<int, Interval>(new_interval_s, new_interval));
            this->intervals_by_e.insert(pair<int, Interval>(new_interval_e, new_interval));
        }

        vector<Interval> getIntervals()
        {
            vector<Interval> s;
            for (map<int, Interval>::iterator i = this->intervals_by_s.begin(); i != this->intervals_by_s.end(); i++)
            {
                s.push_back(i->second);
            }
            return s;
        }
    };
};

using namespace _LEET_DATA_STREAM_AS_DISJOINT_INTERVALS;

int LEET_DATA_STREAM_AS_DISJOINT_INTERVALS()
{
    SummaryRanges s;
    int test[5] = { 1, 3, 7, 2, 6 };
    for (int i = 0; i < 5; i++)
    {
        s.addNum(test[i]);
        vector<Interval> intervals = s.getIntervals();
        for (vector<Interval>::iterator vi = intervals.begin(); vi != intervals.end(); vi++)
        {
            cout << "[" << vi->start << "," << vi->end << "] ";
        }
        cout << endl;
    }
    return 0;
}