#include "stdafx.h"

// https://leetcode.com/problems/lru-cache/

#include "LEET_LRU_CACHE.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

namespace _LEET_LRU_CACHE
{
    class LRUCache
    {
    private:
        struct Node
        {
            Node* prev;
            Node* next;
            int key;
            int value;
        };
        Node* m_front;
        Node* m_back;
        int m_capacity;
        unordered_map<int, Node*> m_cache;

        void ExtractNodeFromList(Node* n)
        {
            n->next->prev = n->prev;
            n->prev->next = n->next;
        }

        void EnqueueNode(Node* n)
        {
            n->prev = this->m_front;
            n->next = this->m_front->next;
            n->prev->next = n;
            n->next->prev = n;
        }
    public:
        LRUCache(int capacity) : m_capacity(capacity)
        {
            this->m_front = new Node();
            this->m_back = new Node();
            this->m_front->prev = this->m_back->next = nullptr;
            this->m_front->next = this->m_back;
            this->m_back->prev = this->m_front;
        }

        int get(int key)
        {
            auto probe = this->m_cache.find(key);
            if (probe == this->m_cache.end())
            {
                return -1;
            }
            else
            {
                Node* item_node = probe->second;
                this->ExtractNodeFromList(item_node);
                this->EnqueueNode(item_node);
                return item_node->value;
            }
        }

        void set(int key, int value)
        {
            if (this->m_capacity > 0)
            {
                auto probe = this->m_cache.find(key);
                if (probe == this->m_cache.end())
                {
                    Node* new_item_node;
                    if (this->m_cache.size() == this->m_capacity)
                    {
                        // Full cache, evict the least recently used item
                        Node* least_recently_used_node = this->m_back->prev;
                        int least_recently_used_key = least_recently_used_node->key;

                        this->m_cache.erase(least_recently_used_key);
                        this->ExtractNodeFromList(least_recently_used_node);

                        // Reuse the node to avoid allocation
                        new_item_node = least_recently_used_node;
                    }
                    else
                    {
                        new_item_node = new Node();
                    }

                    new_item_node->key = key;
                    new_item_node->value = value;
                    this->m_cache.insert(pair<int, Node*>(key, new_item_node));
                    EnqueueNode(new_item_node);
                }
                else
                {
                    Node* old_item_node = probe->second;
                    old_item_node->value = value;
                    this->ExtractNodeFromList(old_item_node);
                    this->EnqueueNode(old_item_node);
                }
            }
        }
    };
};

using namespace _LEET_LRU_CACHE;

int LEET_LRU_CACHE()
{

    return 0;
}