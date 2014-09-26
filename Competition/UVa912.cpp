#include "stdafx.h"

// http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=849

#include "UVa912.h"

#include <iostream>
#include <list>
#include <string>
#include <map>
#include <cstdlib>

using namespace std;

struct element
{
    element(char c)
    {
        this->is_number = false;
        this->c = c;
    }

    element(int n)
    {
        this->is_number = true;
        this->n = n;
    }

    bool is_number;
    char c;
    int n;
};

void input(int dna_length, list<element>& dna1, map<int, int>& disjoint_sets)
{    
    for (int i = 0; i < dna_length; i++)
    {
        string s;
        getline(cin, s);
        if (s[0] >= 'A' && s[0] <= 'D')
        {
            dna1.push_back(element(s[0]));
        }
        else
        {
            int n = atoi(s.c_str());
            map<int, int>::iterator probe = disjoint_sets.find(n);
            if (probe == disjoint_sets.end())
            {
                disjoint_sets.insert(pair<int, int>(n, -1));
            }

            dna1.push_back(element(n));
        }
    }
}

int find(map<int, int>& disjoint_sets, int i)
{
    if (disjoint_sets[i] < 0)
    {
        return i;
    }
    else
    {
        return (disjoint_sets[i] = find(disjoint_sets, disjoint_sets[i]));
    }
}

int UVa912()
{
    bool first = true;
    while (true)
    {
        int dna_length;
        cin >> dna_length;
        string dummy;
        getline(cin, dummy);
        if (cin.eof())
        {
            break;
        }

        list<element> dna1;
        list<element> dna2;
        map<int, int> disjoint_sets;
        map<int, char> mapped_to;

        input(dna_length, dna1, disjoint_sets);
        input(dna_length, dna2, disjoint_sets);

        list<element>::iterator i1 = dna1.begin();
        list<element>::iterator i2 = dna2.begin();

        bool valid = true;
        for (int i = 0; i < dna_length; i++)
        {
            element e1 = *i1;
            element e2 = *i2;

            if (e1.is_number)
            {
                if (e2.is_number)
                {
                    int e1_root = find(disjoint_sets, e1.n);
                    int e2_root = find(disjoint_sets, e2.n);
                    if (e1_root != e2_root)
                    {
                        map<int, char>::iterator probe1 = mapped_to.find(e1_root);
                        map<int, char>::iterator probe2 = mapped_to.find(e2_root);
                        bool mapped = false;
                        char should = ' ';
                        if (probe1 != mapped_to.end())
                        {
                            mapped = true;
                            should = probe1->second;
                        }
                        if (probe2 != mapped_to.end())
                        {
                            if (mapped)
                            {
                                if (probe2->second != should)
                                {
                                    valid = false;
                                    break;
                                }
                                else
                                {
                                    continue;
                                }
                            }
                            else
                            {
                                mapped = true;
                                should = probe2->second;
                            }
                        }

                        // Naive union for now (no size tracking)
                        disjoint_sets[e2_root] = e1_root;
                        if (mapped)
                        {
                            if (probe1 == mapped_to.end())
                            {
                                mapped_to.insert(pair<int, char>(e1_root, should));
                            }
                        }
                    }
                }
                else
                {
                    int representative_number = find(disjoint_sets, e1.n);
                    map<int, char>::iterator probe = mapped_to.find(representative_number);
                    if (probe == mapped_to.end())
                    {
                        mapped_to.insert(pair<int, char>(representative_number, e2.c));
                    }
                    else
                    {
                        if (probe->second != e2.c)
                        {
                            valid = false;
                            break;
                        }
                    }
                }
            }
            else
            {
                if (e2.is_number)
                {
                    int representative_number = find(disjoint_sets, e2.n);
                    map<int, char>::iterator probe = mapped_to.find(representative_number);
                    if (probe == mapped_to.end())
                    {
                        mapped_to.insert(pair<int, char>(representative_number, e1.c));
                    }
                    else
                    {
                        if (probe->second != e1.c)
                        {
                            valid = false;
                            break;
                        }
                    }
                }
                else
                {
                    if (e1.c != e2.c) {
                        valid = false;
                        break;
                    }
                }
            }

            i1++;
            i2++;
        }

        if (first)
        {
            first = false;
        }
        else
        {
            cout << endl;
        }
        if (valid)
        {
            cout << "YES" << endl;
            for (map<int, int>::iterator ni = disjoint_sets.begin(); ni != disjoint_sets.end(); ni++)
            {
                int rep = find(disjoint_sets, ni->first);
                map<int, char>::iterator probe = mapped_to.find(rep);
                if (probe != mapped_to.end())
                {
                    cout << ni->first << " " << probe->second << endl;
                }
            }
        }
        else
        {
            cout << "NO" << endl;
        }
        
    }
    return 0;
}