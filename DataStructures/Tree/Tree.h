#pragma once

#include <iostream>
#include <iostream>
#include <queue>
#include <stack>
using namespace std;

class Tree
{
public:
	struct Node
	{
		int data; // used as a key
		Node* leftChild;
		Node* sibling;

		Node::Node()
		{
			data = 0;
			leftChild = NULL;
			sibling = NULL;
		}
	};

	Tree();
	~Tree();

	bool isNumber(char ch);
	Node* createNode(const int& data);
	Node* search(Node** root, int const& data);
	Node* searchStep(Node* node, int const& data);
	Node* insertChild(Node** root, int const& data, int const& key);
	Node* insertSibling(Node** root, int const& data, int const& key);
	void printTree(Node** root) const;
	void createTree(const string& str, Node** root);
	void clear(Node** root);
	int getSize() const;
	void treeBFS(Node** root);

private:
	size_t nodes;
};