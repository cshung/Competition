#include "stdafx.h"

// https://leetcode.com/problems/restore-ip-addresses/

#include "LEET_RESTORE_IP_ADDRESSES.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

namespace _LEET_RESTORE_IP_ADDRESSES
{
    class Solution
    {
    private:
        void restoreIpAddresses(string s, int begin, vector<int>& components, vector<string>& solution)
        {
            if (begin == s.size())
            {
                if (components.size() == 4)
                {
                    ostringstream sout;
                    sout << components[0] << "." << components[1] << "." << components[2] << "." << components[3];
                    solution.push_back(sout.str());
                }
                else
                {
                    // return
                }
            }
            else if (components.size() == 4)
            {
                // return
            }
            else
            {
                int value = s[begin++] - '0';
                components.push_back(value);
                this->restoreIpAddresses(s, begin, components, solution);
                components.pop_back();
                if (value == 0)
                {
                    return;
                }
                
                if (begin == s.size())
                {
                    return;
                }

                value = value * 10 +  s[begin++] - '0';
                components.push_back(value);
                this->restoreIpAddresses(s, begin, components, solution);
                components.pop_back();

                if (begin == s.size())
                {
                    return;
                }

                value = value * 10 + s[begin++] - '0';
                if (value > 255)
                {
                    return;
                }
                components.push_back(value);
                this->restoreIpAddresses(s, begin, components, solution);
                components.pop_back();
            }
        }
    public:
        vector<string> restoreIpAddresses(string s)
        {
            vector<string> solution;
            vector<int> components;
            restoreIpAddresses(s, 0, components, solution);
            return solution;
        }
    };
};

using namespace _LEET_RESTORE_IP_ADDRESSES;

int LEET_RESTORE_IP_ADDRESSES()
{
    Solution s;
    vector<string> solutions = s.restoreIpAddresses("25525511135");
    for (unsigned int i = 0; i < solutions.size(); i++)
    {
        cout << solutions[i] << endl;
    }
    return 0;
}