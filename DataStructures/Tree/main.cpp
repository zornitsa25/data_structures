// zornitsa chopova

#include <iostream>
#include <string>
#include <stack>
using namespace std;

#include "Tree.h"

int main(int argc, char** argv)
{
	// test (5{(9{})(1{(4{})(7{})(3{})})})
	Tree::Node* root = NULL;
	Tree tree;

	string str;
	for (int i = 0; i < argc; ++i) 
	{
		cin >> str;
	}

	tree.createTree(str, &root);
	// tree.printTree(&root);
	tree.clear(&root);

	system("pause");
	return 0;
}