#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=810

#include "UVa869.h"

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>
#include <iomanip>

using namespace std;

int UVa869()
{
    int test_case = 0;

    while (true)
    {
        test_case++;
        int number_of_stones;
        cin >> number_of_stones;
        if (number_of_stones == 0)
        {
            break;
        }
        vector<pair<int, int>> stones;
        stones.resize(number_of_stones);
        for (int i = 0; i < number_of_stones; i++)
        {
            int x;
            int y;
            cin >> x;
            cin >> y;
            stones[i] = pair<int, int>(x, y);
        }

        int number_of_nodes = number_of_stones;

        vector<vector<double> > adjacency_matrix;
        vector<vector<double> > minimax_distances;
        adjacency_matrix.resize(number_of_nodes);
        minimax_distances.resize(number_of_nodes);
        for (int src = 0; src < number_of_nodes; src++)
        {
            adjacency_matrix[src].resize(number_of_nodes);
            minimax_distances[src].resize(number_of_nodes);

            for (int dst = 0; dst < number_of_nodes; dst++)
            {
                int x_diff = stones[src].first - stones[dst].first; 
                int y_diff = stones[src].second - stones[dst].second; 
                adjacency_matrix[src][dst] = sqrt(x_diff * x_diff + y_diff * y_diff);
                minimax_distances[src][dst] = adjacency_matrix[src][dst];
            }
        }

        for (int k = 0; k < number_of_nodes; k++)
        {
            for (int src = 0; src < number_of_nodes; src++)
            {
                for (int dst = 0; dst < number_of_nodes; dst++)
                {
                    double current_minimax_distance = minimax_distances[src][dst];
                    double propose_minimax_distance = max(minimax_distances[src][k], minimax_distances[k][dst]);
                    if (propose_minimax_distance < current_minimax_distance)
                    {
                        minimax_distances[src][dst] = propose_minimax_distance;
                    }
                }
            }
        }

        cout << "Scenario #" << test_case << endl;
        cout << "Frog Distance = " << setprecision(3) << fixed << minimax_distances[0][1] << endl;
        cout << endl;
    }
    return 0;
}