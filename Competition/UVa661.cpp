#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=8&page=show_problem&problem=602

#include "UVa661.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int UVa661()
{
    int num_devices;
    int num_operations;
    int capacity;

    int sequenceId = 1;
    while (true)
    {
        vector<int> consumptions;
        vector<int> operations;
        vector<bool> states;
        cin >> num_devices;
        cin >> num_operations;
        cin >> capacity;
        if (num_devices == 0 && num_operations == 0 && capacity == 0)
        {
            return 0;
        }

        for (int i = 0; i < num_devices; i++)
        {
            int current_consumption;
            cin >> current_consumption;
            consumptions.push_back(current_consumption);
            states.push_back(false);
        }

        for (int i = 0; i < num_operations; i++)
        {
            int current_operation;
            cin >> current_operation;
            operations.push_back(current_operation - 1); /* input device id starts with 1 */
        }

        int maxConsumption = 0;
        int currentConsumption = 0;
        bool blown = false;
        for (vector<int>::iterator operation_iterator = operations.begin(); !blown && operation_iterator != operations.end(); operation_iterator++)
        {
            int operating_device = *operation_iterator;
            bool operating_device_state = states[operating_device];
            if (operating_device_state)
            {
                currentConsumption -= consumptions[operating_device];
            }
            else
            {
                currentConsumption += consumptions[operating_device];
                maxConsumption = max(currentConsumption, maxConsumption);
                if (currentConsumption > capacity)
                {
                    blown = true;
                }
            }
            operating_device_state = !operating_device_state;
            states[operating_device] = operating_device_state;
        }
        cout << "Sequence " << sequenceId << endl;
        if (blown)
        {
            cout << "Fuse was blown." << endl;
        }
        else
        {
            cout << "Fuse was not blown." << endl;
            cout << "Maximal power consumption was " << maxConsumption << " amperes." << endl;
        }
        cout << endl;
        sequenceId++;
    }

    return 0;
}