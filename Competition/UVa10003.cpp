#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=944

#include "UVa10003.h"

#include <iostream>
#include <vector>

using namespace std;

int UVa10003()
{
    while (true)
    {
        int stick_length;
        int num_cuts;
        cin >> stick_length;
        if (stick_length == 0)
        {
            break;
        }
        cin >> num_cuts;
        vector<int> endpoints;
        endpoints.resize(num_cuts + 2);
        endpoints[0] = 0;
        for (int i = 1; i <= num_cuts; i++)
        {
            int cut;
            cin >> cut;
            endpoints[i] = cut;
        }
        endpoints[num_cuts + 1] = stick_length;

        vector<vector<int> > opt;
        opt.resize(endpoints.size());
        for (unsigned int i = 0; i < endpoints.size(); i++)
        {
            opt[i].resize(endpoints.size());
        }

        // Initialization - minimal cost of cutting a segment with no cutting point in it is 0
        for (unsigned int i = 0; i < endpoints.size() - 1; i++)
        {
            opt[i][i + 1] = 0;
        }

        for (unsigned int gap = 2; gap <= endpoints.size() - 1; gap++)
        {
            for (unsigned int i = 0; i + gap < endpoints.size(); i++)
            {
                int j = i + gap;
                int segment_length = endpoints[j] - endpoints[i];
                bool first = true;
                int min = -1;
                for (int k = i + 1; k < j; k++)
                {
                    int cost = opt[i][k] + opt[k][j];;
                    if (first)
                    {
                        min = cost;
                        first = false;
                    }
                    else
                    {
                        if (cost < min)
                        {
                            min = cost;
                        }
                    }
                }
                opt[i][j] = segment_length + min;
            }
        }

        cout << "The minimum cutting is " << opt[0][endpoints.size() - 1] << "." << endl;
    }

    return 0;
}