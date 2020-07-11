#include "stdafx.h"

// https://leetcode.com/problems/prison-cells-after-n-days/

#include "LEET_PRISON_CELLS_AFTER_N_DAYS.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_PRISON_CELLS_AFTER_N_DAYS
{
    class Solution {
    public:
        vector<int> prisonAfterNDays(vector<int>& cells, int N)
        {
            vector<vector<int>> cycles;
            vector<int> cycle1;
            cycle1.push_back(84);
            cycle1.push_back(124);
            cycle1.push_back(56);
            cycle1.push_back(18);
            cycle1.push_back(82);
            cycle1.push_back(114);
            cycle1.push_back(34);
            cycle1.push_back(42);
            cycle1.push_back(62);
            cycle1.push_back(28);
            cycle1.push_back(72);
            cycle1.push_back(74);
            cycle1.push_back(78);
            cycle1.push_back(68);
            cycles.push_back(cycle1);
            vector<int> cycle2;
            cycle2.push_back(86);
            cycle2.push_back(120);
            cycle2.push_back(50);
            cycle2.push_back(2);
            cycle2.push_back(122);
            cycle2.push_back(54);
            cycle2.push_back(8);
            cycle2.push_back(106);
            cycle2.push_back(30);
            cycle2.push_back(76);
            cycle2.push_back(64);
            cycle2.push_back(94);
            cycle2.push_back(108);
            cycle2.push_back(16);
            cycles.push_back(cycle2);
            vector<int> cycle3;
            cycle3.push_back(80);
            cycle3.push_back(118);
            cycle3.push_back(40);
            cycle3.push_back(58);
            cycle3.push_back(22);
            cycle3.push_back(88);
            cycle3.push_back(98);
            cycle3.push_back(10);
            cycle3.push_back(110);
            cycle3.push_back(20);
            cycle3.push_back(92);
            cycle3.push_back(104);
            cycle3.push_back(26);
            cycle3.push_back(70);
            cycles.push_back(cycle3);
            vector<int> cycle4;
            cycle4.push_back(90);
            cycle4.push_back(102);
            cycle4.push_back(0);
            cycle4.push_back(126);
            cycle4.push_back(60);
            cycle4.push_back(24);
            cycle4.push_back(66);
            cycles.push_back(cycle4);
            vector<int> cycle5;
            cycle5.push_back(116);
            cycle5.push_back(44);
            cycle5.push_back(48);
            cycle5.push_back(6);
            cycle5.push_back(112);
            cycle5.push_back(38);
            cycle5.push_back(32);
            cycle5.push_back(46);
            cycle5.push_back(52);
            cycle5.push_back(12);
            cycle5.push_back(96);
            cycle5.push_back(14);
            cycle5.push_back(100);
            cycle5.push_back(4);
            cycles.push_back(cycle5);
            vector<int> cycle6;
            cycle6.push_back(36);
            cycles.push_back(cycle6);
            int which_cycle[] = { 3, -1, 1, -1, 4, -1, 4, -1, 1, -1, 2, -1, 4, -1, 4, -1, 1, -1, 0, -1, 2, -1, 2, -1, 3, -1, 2, -1, 0, -1, 1, -1, 4, -1, 0, -1, 5, -1, 4, -1, 2, -1, 0, -1, 4, -1, 4, -1, 4, -1, 1, -1, 4, -1, 1, -1, 0, -1, 2, -1, 3, -1, 0, -1, 1, -1, 3, -1, 0, -1, 2, -1, 0, -1, 0, -1, 1, -1, 0, -1, 2, -1, 0, -1, 0, -1, 1, -1, 2, -1, 3, -1, 2, -1, 1, -1, 4, -1, 2, -1, 4, -1, 3, -1, 2, -1, 1, -1, 1, -1, 2, -1, 4, -1, 0, -1, 4, -1, 2, -1, 1, -1, 1, -1, 0, -1, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
            int where_cycle[] = { 2, 0, 3, 0, 13, 0, 3, 0, 6, 0, 7, 0, 9, 0, 11, 0, 13, 0, 3, 0, 9, 0, 4, 0, 5, 0, 12, 0, 9, 0, 8, 0, 6, 0, 6, 0, 0, 0, 5, 0, 2, 0, 7, 0, 1, 0, 7, 0, 2, 0, 2, 0, 8, 0, 5, 0, 2, 0, 3, 0, 4, 0, 8, 0, 10, 0, 6, 0, 13, 0, 13, 0, 10, 0, 11, 0, 9, 0, 12, 0, 0, 0, 4, 0, 0, 0, 0, 0, 5, 0, 0, 0, 10, 0, 11, 0, 10, 0, 6, 0, 12, 0, 1, 0, 11, 0, 7, 0, 12, 0, 8, 0, 4, 0, 5, 0, 0, 0, 1, 0, 1, 0, 4, 0, 1, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
            int next[] = { 126, 124, 122, 120, 116, 118, 112, 114, 106, 104, 110, 108, 96, 98, 100, 102, 86, 84, 82, 80, 92, 94, 88, 90, 66, 64, 70, 68, 72, 74, 76, 78, 46, 44, 42, 40, 36, 38, 32, 34, 58, 56, 62, 60, 48, 50, 52, 54, 6, 4, 2, 0, 12, 14, 8, 10, 18, 16, 22, 20, 24, 26, 28, 30, 94, 92, 90, 88, 84, 86, 80, 82, 74, 72, 78, 76, 64, 66, 68, 70, 118, 116, 114, 112, 124, 126, 120, 122, 98, 96, 102, 100, 104, 106, 108, 110, 14, 12, 10, 8, 4, 6, 0, 2, 26, 24, 30, 28, 16, 18, 20, 22, 38, 36, 34, 32, 44, 46, 40, 42, 50, 48, 54, 52, 56, 58, 60, 62, 62, 60, 58, 56, 52, 54, 48, 50, 42, 40, 46, 44, 32, 34, 36, 38, 22, 20, 18, 16, 28, 30, 24, 26, 2, 0, 6, 4, 8, 10, 12, 14, 110, 108, 106, 104, 100, 102, 96, 98, 122, 120, 126, 124, 112, 114, 116, 118, 70, 68, 66, 64, 76, 78, 72, 74, 82, 80, 86, 84, 88, 90, 92, 94, 30, 28, 26, 24, 20, 22, 16, 18, 10, 8, 14, 12, 0, 2, 4, 6, 54, 52, 50, 48, 60, 62, 56, 58, 34, 32, 38, 36, 40, 42, 44, 46, 78, 76, 74, 72, 68, 70, 64, 66, 90, 88, 94, 92, 80, 82, 84, 86, 102, 100, 98, 96, 108, 110, 104, 106, 114, 112, 118, 116, 120, 122, 124, 126 };

            int i = cells[0] << 7 |
                cells[1] << 6 |
                cells[2] << 5 |
                cells[3] << 4 |
                cells[4] << 3 |
                cells[5] << 2 |
                cells[6] << 1 |
                cells[7] << 0;

            while (N > 0 && which_cycle[i] == -1)
            {
                i = next[i];
                N--;
            }

            int j = cycles[which_cycle[i]][(where_cycle[i] + N) % cycles[which_cycle[i]].size()];
            vector<int> result;
            result.push_back((j & 128) == 0 ? 0 : 1);
            result.push_back((j & 64) == 0 ? 0 : 1);
            result.push_back((j & 32) == 0 ? 0 : 1);
            result.push_back((j & 16) == 0 ? 0 : 1);
            result.push_back((j & 8) == 0 ? 0 : 1);
            result.push_back((j & 4) == 0 ? 0 : 1);
            result.push_back((j & 2) == 0 ? 0 : 1);
            result.push_back((j & 1) == 0 ? 0 : 1);
            return result;
        }
    };
};

using namespace _LEET_PRISON_CELLS_AFTER_N_DAYS;

int LEET_PRISON_CELLS_AFTER_N_DAYS()
{
    int input_array[] = { 0,1,0,1,1,0,0,1 };
    vector<int> input(input_array, input_array + _countof(input_array));
    Solution s;
    for (auto i : s.prisonAfterNDays(input, 7))
    {
        cout << i << ",";
    }
    cout << endl;
    return 0;
}