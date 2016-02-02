#include "stdafx.h"

// https://leetcode.com/problems/clone-graph/

#include "LEET_CLONE_GRAPH.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_CLONE_GRAPH
{
    struct UndirectedGraphNode
    {
        int label;
        vector<UndirectedGraphNode *> neighbors;
        UndirectedGraphNode(int x) : label(x) {};
    };
    class Solution
    {
    private:
        UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node, map<UndirectedGraphNode*, UndirectedGraphNode*> context)
        {
            map<UndirectedGraphNode*, UndirectedGraphNode*>::iterator probe = context.find(node);
            if (probe == context.end())
            {
                UndirectedGraphNode* clone = new UndirectedGraphNode(node->label);
                context.insert(pair<UndirectedGraphNode*, UndirectedGraphNode*>(node, clone));
                for (size_t i = 0; i < node->neighbors.size(); i++)
                {
                    clone->neighbors.push_back(this->cloneGraph(node->neighbors[i], context));
                }
                return clone;
            }
            else
            {
                return probe->second;
            }
        }

    public:
        UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node)
        {
            map<UndirectedGraphNode*, UndirectedGraphNode*> context;
            return this->cloneGraph(node, context);
        }
    };
};

using namespace _LEET_CLONE_GRAPH;

int LEET_CLONE_GRAPH()
{
    UndirectedGraphNode a(1);
    UndirectedGraphNode b(2);
    a.neighbors.push_back(&b);
    b.neighbors.push_back(&a);
    Solution s;
    UndirectedGraphNode* c = s.cloneGraph(&a);
    cout << c->label << endl;
    cout << c->neighbors.size() << endl;
    cout << c->neighbors[0]->label << endl;
    cout << c->neighbors[0]->neighbors.size() << endl;
    cout << c->neighbors[0]->neighbors[0]->label << endl;
    return 0;
}