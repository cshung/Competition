#include "stdafx.h"

// https://leetcode.com/problems/convert-bst-to-greater-tree

#include "LEET_CONVERT_BST_TO_GREATER_TREE.h"
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace _LEET_CONVERT_BST_TO_GREATER_TREE
{
	struct TreeNode
	{
		int val;
		TreeNode* left;
		TreeNode* right;
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
	};

	class ReverseOrderIterator
	{
	private:
		int m_state;
		TreeNode* m_current;
		TreeNode* root;
		ReverseOrderIterator* m_rightIterator;
		ReverseOrderIterator* m_leftIterator;
	public:
		ReverseOrderIterator(TreeNode* root)
		{
			this->root = root;
			this->m_state = 1;
		}

		bool MoveNext()
		{
			if (this->m_state == 2)
			{
				goto label2;
			}
			else if (this->m_state == 3)
			{
				goto label3;
			}
			else if (this->m_state == 4)
			{
				goto label4;
			}
			if (root == nullptr)
			{
				return false;
			}
			this->m_rightIterator = new ReverseOrderIterator(root->right);
			while (this->m_rightIterator->MoveNext())
			{
				this->m_state = 2;
				this->m_current = this->m_rightIterator->Current();
				return true;
			label2:
				{

				}
			}
			delete this->m_rightIterator;
			this->m_state = 3;
			this->m_current = root;
			return true;
		label3:
			this->m_leftIterator = new ReverseOrderIterator(root->left);
			while (this->m_leftIterator->MoveNext())
			{
				this->m_state = 4;
				this->m_current = this->m_leftIterator->Current();
				return true;
			label4:
				{

				}
			}
			delete this->m_leftIterator;
			return false;
		}

		TreeNode* Current()
		{
			return this->m_current;
		}
	};

	class Solution
	{
	public:
		TreeNode* convertBST(TreeNode* root)
		{
			bool first = true;
			int sum = 0;
			int last_value_before = 0;
			int last_value_change = 0;

			ReverseOrderIterator* iterator = new ReverseOrderIterator(root);
			while (iterator->MoveNext())
			{
				TreeNode* current_node = iterator->Current();
				if (first)
				{
					sum = last_value_before = last_value_change = current_node->val;
					first = false;
				}
				else
				{
					int current_value = current_node->val;
					sum = sum + current_value;
					if (current_value == last_value_before)
					{
						current_node->val = last_value_change;
					}
					else
					{
						last_value_before = current_value;
						current_node->val = last_value_change = sum;
					}
				}
			}
			delete iterator;
			return root;
		}
	};
};

using namespace _LEET_CONVERT_BST_TO_GREATER_TREE;

int LEET_CONVERT_BST_TO_GREATER_TREE()
{
	TreeNode a(2);
	TreeNode b(1);
	TreeNode c(2);
	a.left = &b;
	a.right = &c;
	b.left = c.left = nullptr;
	b.right = c.right = nullptr;
	Solution s;
	s.convertBST(&a);
	cout << b.val << endl;
	cout << a.val << endl;
	cout << c.val << endl;
	return 0;
}