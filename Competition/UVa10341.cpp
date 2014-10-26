#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1282

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

double evaluate(int p, int q, int r, int s, int t, int u, double x)
{
    return p * exp(-x) + q * sin(x) + r * cos(x) + s * tan(x) + t * x * x + u;
}

int UVa10341()
{
    int p, q, r, s, t, u;
    while (true)
    {
        cin >> p;
        if (cin.eof())
        {
            break;
        }
        cin >> q;
        cin >> r;
        cin >> s;
        cin >> t;
        cin >> u;
        double first = evaluate(p, q, r, s, t, u, 0);
        double second = evaluate(p, q, r, s, t, u, 1);
        if (first * second > 0)
        {
            cout << "No solution" << endl;
        }
        else
        {
            bool first_is_negative = first < 0;
            double left = 0;
            double right = 1;
            int i = 0;
            for (int i = 0; i < 100; i++) // way more than enough :)
            {
                double middle = (left + right) / 2;
                double middle_result = evaluate(p, q, r, s, t, u, middle);
                if (first_is_negative)
                {
                    if (middle_result < 0)
                    {
                        left = middle;
                    }
                    else
                    {
                        right = middle;
                    }
                }
                else
                {
                    if (middle_result < 0)
                    {
                        right = middle;
                    }
                    else
                    {
                        left = middle;                        
                    }
                }
            }
            std::cout << std::setprecision(4) << std::fixed << left << endl;
        }
    }
    return 0;
}