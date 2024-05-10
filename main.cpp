
#include <iomanip>
#include <iostream>
#include <sstream>
#include "map_from_rbtree.h"


int main()
{
	/*rbNode start = rbNode(5);
	rbNode* ptr = &start;
	rbTree test = rbTree(ptr);
	int i;
	test.InsertValue(ptr, 3);
	test.InsertValue(ptr, 8);
	test.InsertValue(ptr, 6);
	test.InsertValue(ptr, 10);
	test.InsertValue(ptr, 4);
	test.InsertValue(ptr, 2);
	test.PrintTree(ptr, 3);
	std::cin >> i;*/
	int i;
	RBTree* tree = new RBTree;
	Node* found = new Node;
	InsertValue(tree->Root, "anton", "test");
	InsertValue(tree->Root,"boris", "test");
	InsertValue(tree->Root,"vadim", "test");
	InsertValue(tree->Root,"gosha", "test");
	InsertValue(tree->Root, "dima", "test");
	InsertValue(tree->Root,"egor", "test");
	InsertValue(tree->Root,"Zhora", "test");
	InsertValue(tree->Root,"Zelya", "test");
	InsertValue(tree->Root,"Igor", "test");
	InsertValue(tree->Root,"Kiril", "test");
	InsertValue(tree->Root,"Lenya", "test");
	InsertValue(tree->Root,"Misha", "test");
	InsertValue(tree->Root, "Nikita", "13");
	InsertValue(tree->Root, "Oleg", "test");
	InsertValue(tree->Root, "Pasha", "test");
	InsertValue(tree->Root, "Roma", "test");
	InsertValue(tree->Root, "semen", "test");
	PrintTree(tree->Root, 5);
	found = Find(tree->Root, "Nikita");
	std::cout << std::endl;
	std::cout << found->Name << std::endl;
	/*key test1 = key("nina");
	key test2 = key("nina");
	key test3 = key("max");
	std::cout << (test1 < test2) << std::endl;
	std::cout << (test1 > test2) << std::endl;
	std::cout << (test1 == test2) << std::endl;
	std::cout << (test1 < test3) << std::endl;
	std::cout << (test1 > test3) << std::endl;
	std::cout << (test1 == test3) << std::endl;*/

	std::cin >> i;
}

