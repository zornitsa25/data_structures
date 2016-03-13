#pragma once

#include "Tree.h"

Tree::Tree()
{
	this->nodes = 0;
}

Tree::~Tree()
{
	//clear explicitly !
}

bool Tree::isNumber(char ch)
{
	return ch >= '0' && ch <= '9';
}

Tree::Node* Tree::createNode(const int& data)
{
	Node* new_node = new Node();
	new_node->data = data;
	new_node->leftChild = new_node->sibling = NULL;
	return new_node;
}

Tree::Node* Tree::search(Node** root, int const& data)
{
	if (*root == NULL || (*root)->data == data)
	{
		return *root;
	}
	if (!(*root)->leftChild)
		return NULL;
	return searchStep((*root)->leftChild, data);
}

Tree::Node* Tree::searchStep(Node* node, int const& data)
{
	if (node == NULL)
	{
		return node;
	}
	if (node->data == data)
	{
		return node;
	}
	Node* curr = NULL;
	if (node->sibling)
	{
		curr = searchStep(node->sibling, data);
	}
	if (curr)
	{
		return curr;
	}
	if (node->leftChild != NULL)
	{
		curr = searchStep(node->leftChild, data);
	}
	return curr;
}

Tree::Node* Tree::insertChild(Node** root, int const& data, int const& key)
{
	if (*root == NULL)
	{
		if (key == NULL)
		{
			(*root) = createNode(data);
			nodes++;
			return *root;
		}
		else
		{
			(*root) = createNode(key);
			nodes++;
		}

	}
	Node* temp = search(root, key);
	if (temp == NULL)
	{
		return NULL;
	}
	if (temp->leftChild == NULL)
	{
		Node* new_node = createNode(data);
		temp->leftChild = new_node;
		nodes++;
		return new_node;
	}
	else if (temp->leftChild != NULL)
	{
		temp = temp->leftChild;
		Node* new_node = insertSibling(root, data, temp->data);
		temp->sibling = new_node;
		return new_node;
	}
}

Tree::Node* Tree::insertSibling(Node** root, int const& data, int const& key)
{
	Node* temp = search(root, key);
	Node* new_node = createNode(data);
	if (temp->sibling == NULL)
	{
		temp->sibling = new_node;
		nodes++;
		return new_node;
	}
	else
	{
		Node* tmp = temp->sibling;
		temp->sibling = new_node;
		new_node->sibling = tmp;
		nodes++;
		return new_node;
	}
}

void Tree::printTree(Node** root) const
{
	if (*root == NULL)
	{
		return;
	}
	Node* curr = (*root);

	while (curr)
	{
		cout << curr->data << " ";
		printTree(&curr->sibling);
		curr = curr->leftChild;
	}
}

void Tree::createTree(const string& str, Node** root)
{
	stack<int> numbers;
	int parent = 0;
	int child = 0;

	for (int i = 0; i < str.size() - 1; i++)
	{
		if (str[i] == '(')
		{
			++i;
			parent = 0;
			while (isNumber(str[i]))
			{
				parent = parent * 10 + str[i] - '0';
				i++;
			}
			if (numbers.empty())
			{
				this->insertChild(root, parent, NULL);
				numbers.push(parent);
			}
			else
			{
				int par = numbers.top();
				this->insertChild(root, parent, par);
				numbers.push(parent);
			}
		}
		if (str[i] == ')')
		{
			numbers.pop();
		}
	}
}

void Tree::clear(Node** root)
{
	if ((*root) == NULL)
		return;
	Node* curr_leftChild = (*root)->leftChild;
	Node* curr_sibling = (*root)->sibling;

	delete *root;
	*root = NULL;

	clear(&curr_leftChild);
	clear(&curr_sibling);
}

int Tree::getSize() const
{
	return this->nodes;
}

void Tree::treeBFS(Node** root)
{
	queue<Node*> queue;
	Node* traverse;

	queue.push((*root));

	while (!queue.empty())
	{
		traverse = queue.front();
		cout << traverse->data << endl;

		queue.pop();

		if (traverse->leftChild != NULL)
		{
			queue.push(traverse->leftChild);
			while (traverse->leftChild->sibling != NULL)
			{
				queue.push(traverse->leftChild->sibling);
				traverse->leftChild->sibling = traverse->leftChild->sibling->sibling;
			}
		}
	}
}
