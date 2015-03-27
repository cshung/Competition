#include "stdafx.h"

// https://leetcode.com/problems/surrounded-regions/

#include "LEET_SURROUNDED_REGIONS.h"
#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

namespace _LEET_SURROUNDED_REGIONS
{
    class Node
    {
    public:
        int x;
        int y;
        Node* p;
        int s;
    };

    Node* Find(Node* node)
    {
        if (node->p != node)
        {
            node->p = Find(node->p);
        }
        return node->p;
    }

    void Union(Node* x, Node* y)
    {
        Node* xRoot = Find(x);
        Node* yRoot = Find(y);
        if (xRoot == yRoot)
        {
            return;
        }

        if (xRoot->s < yRoot->s)
        {
            xRoot->p = yRoot;
        }
        else if (xRoot->s > yRoot->s)
        {
            yRoot->p = xRoot;
        }
        else
        {
            yRoot->p = xRoot;
            xRoot->s++;
        }
    }

    class Solution {
    public:
        void solve(vector<vector<char> > &board)
        {
            int numRows = board.size();
            if (numRows > 0)
            {
                int numCols = board[0].size();

                // 
                // Using the Disjoint Set Union Found algorithm to find out the 
                // connected segments 
                // 

                // Step 1: Initialize each item as a set by itself
                Node** nodes = new Node*[numRows * numCols];
                for (int i = 0; i < numRows; i++)
                {
                    for (int j = 0; j < numCols; j++)
                    {
                        nodes[i * numCols + j] = new Node();
                        nodes[i * numCols + j]->x = i;
                        nodes[i * numCols + j]->y = j;
                        nodes[i * numCols + j]->p = nodes[i * numCols + j];
                        nodes[i * numCols + j]->s = 1;
                    }
                }

                // Merge all the horizontally linked sets
                for (int i = 0; i < numRows; i++)
                {
                    for (int j = 0; j < numCols - 1; j++)
                    {
                        if (board[i][j] == board[i][j + 1])
                        {
                            Union(nodes[i * numCols + j], nodes[i * numCols + j + 1]);
                        }
                    }
                }

                // Merge all the vertically linked sets
                for (int j = 0; j < numCols; j++)
                {
                    for (int i = 0; i < numRows - 1; i++)
                    {
                        if (board[i][j] == board[i + 1][j])
                        {
                            Union(nodes[i * numCols + j], nodes[i * numCols + j + numCols]);
                        }
                    }
                }

                set<Node*> badSets;

                // Top edge
                for (int j = 0; j < numCols; j++)
                {
                    if (board[0][j] == 'O')
                    {
                        badSets.insert(Find(nodes[(0) * numCols + j]));
                    }
                }

                // Bottom edge
                for (int j = 0; j < numCols; j++)
                {
                    if (board[numRows - 1][j] == 'O')
                    {
                        badSets.insert(Find(nodes[(numRows - 1) * numCols + j]));
                    }
                }

                // Left edge
                for (int i = 0; i < numRows; i++)
                {
                    if (board[i][0] == 'O')
                    {
                        badSets.insert(Find(nodes[i * numCols + 0]));
                    }
                }

                // Right edge
                for (int i = 0; i < numRows; i++)
                {
                    if (board[i][numCols - 1] == 'O')
                    {
                        badSets.insert(Find(nodes[i * numCols + (numCols - 1)]));
                    }
                }

                for (int i = 0; i < numRows; i++)
                {
                    for (int j = 0; j < numCols; j++)
                    {
                        if (board[i][j] == 'O')
                        {
                            Node* rep = Find(nodes[i * numCols + j]);
                            if (badSets.find(rep) != badSets.end())
                            {
                                board[i][j] = 'Y';
                            }
                        }
                    }

                }

                for (int i = 0; i < numRows; i++)
                {
                    for (int j = 0; j < numCols; j++)
                    {
                        if (board[i][j] == 'Y')
                        {
                            board[i][j] = 'O';
                        }
                        else
                        {
                            board[i][j] = 'X';
                        }
                    }
                }


                // Last step: Free the memory used for the algorithm
                for (int i = 0; i < numRows; i++)
                {
                    for (int j = 0; j < numCols; j++)
                    {
                        delete nodes[i * numCols + j];
                    }
                }
                delete[] nodes;
            }
        }
    };
};

using namespace _LEET_SURROUNDED_REGIONS;

int LEET_SURROUNDED_REGIONS()
{
    Solution solution;
    vector<vector<char> > board;
    vector<char> row1;
    vector<char> row2;
    vector<char> row3;
    char* boardData = "XOXOXOXOX";
    row1.assign(boardData, boardData + 3);
    row2.assign(boardData + 3, boardData + 6);
    row3.assign(boardData + 6, boardData + 9);
    board.push_back(row1);
    board.push_back(row2);
    board.push_back(row3);
    solution.solve(board);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
