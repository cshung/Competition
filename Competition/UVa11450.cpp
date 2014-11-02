#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=2445

#include "UVa11450.h"

#include <iostream>
#include <vector>

using namespace std;

int UVa11450()
{
    int number_of_cases;
    cin >> number_of_cases;
    for (int c = 0; c < number_of_cases; c++)
    {
        int budget;
        int num_garments_types;
        cin >> budget;
        cin >> num_garments_types;
        vector<vector<int> > garments;
        garments.resize(num_garments_types);
        for (int gt = 0; gt < num_garments_types; gt++)
        {
            int num_garments;
            cin >> num_garments;
            garments[gt].resize(num_garments);
            for (int g = 0; g < num_garments; g++)
            {
                int garment_price;
                cin >> garment_price;
                garments[gt][g] = garment_price;
            }
        }

        // Dynamic programming
        int** opt = new int*[budget + 1];
        for (int b = 0; b <= budget; b++)
        {
            opt[b] = new int[num_garments_types];
        }

        // OPT(b, 0) = the maximum price of last garment type less than or equals to b
        for (int current_budget = 0; current_budget <= budget; current_budget++)
        {
            int current_best_spent = -1; 
            for (unsigned int g = 0; g < garments[0].size(); g++)
            {
                int current_price = garments[0][g];
                if (current_price <= current_budget)
                {
                    if (current_price > current_best_spent)
                    {
                        current_best_spent = current_price;
                    }
                }
            }
            opt[current_budget][0] = current_best_spent;
        }

        // OPT(b, n) = for each affordable garment of type n, price(n) + OPT(b - price(n), n - 1)
        for (unsigned int gt = 1; gt < garments.size(); gt++)
        {
            for (int current_budget = 0; current_budget <= budget; current_budget++)
            {
                int current_best_spent = -1; 
                for (unsigned int g = 0; g < garments[gt].size(); g++)
                {
                    int current_price = garments[gt][g];
                    if (current_price <= current_budget)
                    {
                        if (opt[current_budget - current_price][gt - 1] != -1)
                        {
                            int current_spent = current_price + opt[current_budget - current_price][gt - 1];
                            if (current_spent > current_best_spent)
                            {
                                current_best_spent = current_spent;
                            }
                        }
                    }
                }
                opt[current_budget][gt] = current_best_spent;
            }
        }

        int optimal = opt[budget][num_garments_types - 1];

        if (optimal == -1)
        {
            cout << "no solution" << endl;
        }
        else
        {
            cout << optimal << endl;
        }

        for (int b = 0; b <= budget; b++)
        {
            delete[] opt[b];
        }
        delete[] opt;
    }

    return 0;
}