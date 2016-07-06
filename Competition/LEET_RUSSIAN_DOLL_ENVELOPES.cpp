#include "stdafx.h"

// https://leetcode.com/problems/russian-doll-envelopes/

#include "LEET_RUSSIAN_DOLL_ENVELOPES.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

namespace _LEET_RUSSIAN_DOLL_ENVELOPES
{
    bool lessWidth(pair<int, int> e1, pair<int, int> e2)
    {
        return e1.first < e2.first || e1.first == e2.first && e1.second > e2.second;
    }
    class tree
    {
    public:
        tree();
        void insert(int a, int b);
        int query(int a) const;
    private:
        class node
        {
        public:
            node(int a, int b);
            node* insert(int a, int b);
            void update();
            int balance() const;
            int query(int a) const;
            int m_a;
            int m_b;
            int m_max_b;
            node* m_left;
            node* m_right;
            int m_height;
        };
        node* m_root;
    };

    tree::tree() : m_root(nullptr)
    {

    }

    void tree::insert(int a, int b)
    {
        if (this->m_root == nullptr)
        {
            this->m_root = new node(a, b);
        }
        else
        {
            this->m_root = this->m_root->insert(a, b);
        }
    }

    int tree::query(int a) const
    {
        if (this->m_root == nullptr)
        {
            return 0;
        }
        else
        {
            return this->m_root->query(a);
        }
    }

    tree::node::node(int a, int b) : m_a(a), m_b(b), m_max_b(b), m_left(nullptr), m_right(nullptr), m_height(1)
    {

    }

    int tree::node::balance() const
    {
        int left_height = this->m_left == nullptr ? 0 : this->m_left->m_height;
        int right_height = this->m_right == nullptr ? 0 : this->m_right->m_height;
        return right_height - left_height;
    }

    tree::node* tree::node::insert(int a, int b)
    {
        if (this == nullptr)
        {
            return new node(a, b);
        }
        else
        {
            if (a == this->m_a)
            {
                this->m_b = max(this->m_b, b);
            }
            else if (a < this->m_a)
            {
                this->m_left = this->m_left->insert(a, b);
            }
            else if (a > this->m_a)
            {
                this->m_right = this->m_right->insert(a, b);
            }
            this->update();
            if (this->balance() == 2)
            {
                if (this->m_right->balance() >= 0)
                {
                    node* a = this;
                    node* b = this->m_right;
                    node* c = b->m_left;
                    b->m_left = a;
                    a->m_right = c;
                    a->update();
                    b->update();
                    return b;
                }
                else if (this->m_right->balance() == -1)
                {
                    node* a = this;
                    node* b = this->m_right;
                    node* c = b->m_left;
                    node* d = c->m_left;
                    node* e = c->m_right;
                    c->m_left = a;
                    c->m_right = b;
                    a->m_right = d;
                    b->m_left = e;
                    a->update();
                    b->update();
                    c->update();
                    return c;
                }
            }
            else if (this->balance() == -2)
            {
                if (this->m_left->balance() <= 0)
                {
                    node* a = this;
                    node* b = this->m_left;
                    node* c = b->m_right;
                    b->m_right = a;
                    a->m_left = c;
                    a->update();
                    b->update();
                    return b;
                }
                else if (this->m_left->balance() == 1)
                {
                    node* a = this;
                    node* b = this->m_left;
                    node* c = b->m_right;
                    node* d = c->m_right;
                    node* e = c->m_left;
                    c->m_right = a;
                    c->m_left = b;
                    a->m_left = d;
                    b->m_right = e;
                    a->update();
                    b->update();
                    c->update();
                    return c;
                }
            }
            return this;
        }
    }

    void tree::node::update()
    {
        int max_b = this->m_b;
        int height = 1;
        if (this->m_left != nullptr)
        {
            max_b = max(max_b, this->m_left->m_max_b);
            height = max(height, this->m_left->m_height + 1);
        }
        if (this->m_right != nullptr)
        {
            max_b = max(max_b, this->m_right->m_max_b);
            height = max(height, this->m_right->m_height + 1);
        }
        this->m_max_b = max_b;
        this->m_height = height;
    }

    int tree::node::query(int a) const
    {
        if (this == nullptr)
        {
            return 0;
        }
        else if (a <= this->m_a)
        {
            return this->m_left->query(a);
        }
        else
        {
            int result = this->m_right->query(a);
            result = max(result, this->m_b);
            if (this->m_left != nullptr)
            {
                result = max(result, this->m_left->m_max_b);
            }

            return result;
        }
    }
    class Solution {
    public:
        int maxEnvelopes(vector<pair<int, int>>& envelopes)
        {
            if (envelopes.size() == 0)
            {
                return 0;
            }

            sort(envelopes.begin(), envelopes.end(), lessWidth);
            tree t;
            // The chain length of the first envelop has to be 1
            t.insert(envelopes[0].second, 1);
            int max_chain_length = 1;
            for (size_t i = 1; i < envelopes.size(); i++)
            {
                // The chain length of the kth envelop is, within the set of envelop that has less height before me
                // (they are guaranteed to have less width by the sorting), the maximum chain length + 1
                int chain_length = t.query(envelopes[i].second) + 1;
                max_chain_length = max(max_chain_length, chain_length);
                t.insert(envelopes[i].second, chain_length);
            }

            return max_chain_length;
        }
    };
};

using namespace _LEET_RUSSIAN_DOLL_ENVELOPES;

int LEET_RUSSIAN_DOLL_ENVELOPES()
{
    Solution solution;
    vector<pair<int, int>> envelops;
    /*
    envelops.push_back(make_pair(5, 4));
    envelops.push_back(make_pair(6, 4));
    envelops.push_back(make_pair(6, 7));
    envelops.push_back(make_pair(2, 3));
    */
    /*
    envelops.push_back(make_pair(4, 5));
    envelops.push_back(make_pair(4, 6));
    envelops.push_back(make_pair(6, 7));
    envelops.push_back(make_pair(2, 3));
    envelops.push_back(make_pair(1, 1));
    */
    /*
    envelops.push_back(make_pair(1, 1));
    envelops.push_back(make_pair(1, 1));
    envelops.push_back(make_pair(1, 1));
    */
    envelops.push_back(make_pair(46, 89));
    envelops.push_back(make_pair(50, 53));
    envelops.push_back(make_pair(52, 68));
    envelops.push_back(make_pair(72, 45));
    envelops.push_back(make_pair(77, 81));
    cout << solution.maxEnvelopes(envelops) << endl;
    return 0;
}