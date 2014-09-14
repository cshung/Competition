#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1082

#include "UVa10141.h"

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct proposal
{
    string name;
    double price;
    int num_met_requirements;
    vector<string> met_requirements;
};

int UVa10141()
{
    int rfp_count = 0;
    string dummy;
    while (true)
    {
        int num_requirements;
        int num_proposals;
        cin >> num_requirements;
        cin >> num_proposals;
        if (num_requirements == 0 && num_proposals == 0)
        {
            return 0;
        }
        getline(cin, dummy); // consume the end line        
        vector<string> requirements;
        for (int r = 0; r < num_requirements; r++)
        {
            string requirement;
            getline(cin, requirement);
            requirements.push_back(requirement);
        }
        vector<proposal*> proposals;
        for (int p = 0; p < num_proposals; p++)
        {
            proposal* current_proposal = new proposal();
            proposals.push_back(current_proposal);
            getline(cin, current_proposal->name);
            cin >> current_proposal->price;
            cin >> current_proposal->num_met_requirements;
            getline(cin, dummy); // consume the end line
            for (int pr = 0; pr < current_proposal->num_met_requirements; pr++)
            {
                string met_requirement;
                getline(cin, met_requirement);
                current_proposal->met_requirements.push_back(met_requirement);
            }
        }

        int max_met_requirements = -1;

        // Compute required compliance level
        for (vector<proposal*>::iterator p = proposals.begin(); p != proposals.end(); p++)
        {
            max_met_requirements = max(max_met_requirements, (*p)->num_met_requirements);
        }

        proposal* best_proposal = NULL;

        for (vector<proposal*>::iterator p = proposals.begin(); p != proposals.end(); p++)
        {
            proposal* current_proposal = *p;
            if (best_proposal == NULL)
            {
                if (current_proposal->num_met_requirements == max_met_requirements)
                {
                    best_proposal = current_proposal;
                }
            }
            else
            {
                if ((current_proposal->num_met_requirements == max_met_requirements) && (current_proposal->price < best_proposal->price))
                {
                    best_proposal = current_proposal;
                }
            }
        }

        if (rfp_count != 0)
        {
            cout << endl;
        }

        cout << "RFP #" << ++rfp_count << endl;
        cout << best_proposal->name << endl;

        for (vector<proposal*>::iterator p = proposals.begin(); p != proposals.end(); p++)
        {
            delete *p;
        }
    }
    return 0;
}