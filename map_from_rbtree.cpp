#include <iomanip>
#include <iostream>
#include <sstream>
#include "map_from_rbtree.h"


Color GetColor(Node* node)
{
	if (node == nullptr)
	{
		return Color::Black;
	}
	return node->Color;
}


void SetColor(Node*& node, const Color color)
{
	if (node == nullptr)
	{
		return;
	}
	node->Color = color;
}

void switchColor(Node*& root) {
	if (root->Left->Color == root->Right->Color) {
		Color tmp = root->Color;
		root->Color = root->Left->Color;
		root->Left->Color = tmp;
		root->Right->Color = tmp;
	}
}


void RotateLeft(Node*& root, Node*& node)
{
	Node* rightChild = node->Right;
	node->Right = rightChild->Left;

	if (node->Right != nullptr)
	{
		node->Right->Parent = node;
	}

	rightChild->Parent = node->Parent;

	if (node->Parent == nullptr)
	{
		root = rightChild;
	}
	else if (node == node->Parent->Left)
	{
		node->Parent->Left = rightChild;
	}
	else
	{
		node->Parent->Right = rightChild;
	}

	rightChild->Left = node;
	node->Parent = rightChild;
}


void RotateRight(Node*& root, Node*& node)
{
	Node* leftChild = node->Left;
	node->Left = leftChild->Right;

	if (node->Left != nullptr)
	{
		node->Left->Parent = node;
	}

	leftChild->Parent = node->Parent;

	if (node->Parent == nullptr)
	{
		root = leftChild;
	}
	else if (node == node->Parent->Left)
	{
		node->Parent->Left = leftChild;
	}
	else
	{
		node->Parent->Right = leftChild;
	}

	leftChild->Right = node;
	node->Parent = leftChild;
}

void FixInsertRBTree(Node*& root, Node*& node)
{
	Node* parent = nullptr;
	Node* grandParent = nullptr;
	while (node != root &&
		GetColor(node) == Color::Red &&
		GetColor(node->Parent) == Color::Red)
	{
		parent = node->Parent;
		grandParent = parent->Parent;
		if (parent == grandParent->Left)
		{
			Node* uncle = grandParent->Right;
			if (GetColor(uncle) == Color::Red)
			{
				SetColor(uncle, Color::Black);
				SetColor(parent, Color::Black);
				SetColor(grandParent, Color::Red);
				node = grandParent;
			}
			else
			{
				if (node == parent->Right)
				{
					RotateLeft(root, parent);
					node = parent;
					parent = node->Parent;
				}
				RotateRight(root, grandParent);
				const Color color = grandParent->Color;
				grandParent->Color = parent->Color;
				parent->Color = color;
				node = parent;
			}
		}
		else
		{
			Node* uncle = grandParent->Left;
			if (GetColor(uncle) == Color::Red)
			{
				SetColor(uncle, Color::Black);
				SetColor(parent, Color::Black);
				SetColor(grandParent, Color::Red);
				node = grandParent;
			}
			else
			{
				if (node == parent->Left)
				{
					RotateRight(root, parent);
					node = parent;
					parent = node->Parent;
				}
				RotateLeft(root, grandParent);
				const Color color = grandParent->Color;
				grandParent->Color = parent->Color;
				parent->Color = color;
				node = parent;
			}
		}
	}

	SetColor(root, Color::Black);
}


Node* InsertNode(Node*& root, Node*& node)
{
	if (root == nullptr)
	{
		return node;
	}

	if (node->KEY < root->KEY)
	{
		root->Left = InsertNode(root->Left, node);
		root->Left->Parent = root;
	}
	else if (node->KEY > root->KEY)
	{
		root->Right = InsertNode(root->Right, node);
		root->Right->Parent = root;
	}
	else {
		throw std::exception("key already exists\n");
	}

	return root;
}

void InsertValue(Node*& root, std::string KEY, std::string Name)
{
	if (KEY == "" || Name == "") {
		throw std::exception("No Key or data!");
	}
	else {
		Node* node = new Node;
		node->KEY = key(KEY);
		node->Name = Name;
		root = InsertNode(root, node);
		FixInsertRBTree(root, node);
	}
}

void PrintTree(Node* node, const int indent)
{
	if (node == nullptr)
	{
		return;
	}

	if (node->Right)
	{
		PrintTree(node->Right, indent + 4);
	}

	if (indent)
	{
		std::cout << std::setw(indent) << ' ';
	}

	if (node->Right)
	{
		std::cout << " /\n" << std::setw(indent) << ' ';
	}
	/*if (node->Color == Color::Black)
	{
		std::cout << node->KEY.key_val << ' ' << node->Name << std::endl;
	}
	else*/ std::cout << node->KEY.key_val << ' ' << node->Name << std::endl;
	if (node->Left)
	{
		std::cout << std::setw(indent) << ' ' << " \\\n";
		PrintTree(node->Left, indent + 4);
	}
}
inline int DeleteCase1(Node*& root, Node*& node)
{
	if (node == nullptr)
	{
		return 1;
	}

	if (node == root)
	{
		if (node->Left == nullptr && node->Right == nullptr)
		{
			delete root;
			root = nullptr;
			return 1;
		}
		Node* current = root;
		root = root->Left != nullptr
			? root->Left
			: root->Right;
		SetColor(root, Color::Black);
		root->Parent = nullptr;
		delete current;
		return 1;
	}

	return 0;
}


inline void DeleteCase2(Node*& root, Node*& node)
{
	Node* child = node->Left != nullptr
		? node->Left
		: node->Right;

	if (node == node->Parent->Left)
	{
		node->Parent->Left = child;
		if (child != nullptr)
		{
			child->Parent = node->Parent;
		}
		SetColor(child, Color::Black);
		delete node;
	}
	else if (node == node->Parent->Right)
	{
		node->Parent->Right = child;
		if (child != nullptr)
		{
			child->Parent = node->Parent;
		}
		SetColor(child, Color::Black);
		delete node;
	}
}


inline int DeleteCase3(Node*& root, Node*& sibling, Node*& parent, Node*& pointer)
{
	sibling = parent->Right;
	if (GetColor(sibling) == Color::Red)
	{
		SetColor(sibling, Color::Black);
		SetColor(parent, Color::Red);
		RotateLeft(root, parent);
	}
	else if (GetColor(sibling) != Color::Red)
	{
		if (GetColor(sibling->Left) == Color::Black &&
			GetColor(sibling->Right) == Color::Black)
		{
			SetColor(sibling, Color::Red);
			if (GetColor(parent) == Color::Red)
			{
				SetColor(parent, Color::Black);
			}
			else if (GetColor(parent) != Color::Red)
			{
				SetColor(parent, Color::DoubleBlack);
			}
			pointer = parent;
		}
		else if (GetColor(sibling->Left) != Color::Black
			|| GetColor(sibling->Right) != Color::Black)
		{
			if (GetColor(sibling->Right) == Color::Black)
			{
				SetColor(sibling->Left, Color::Black);
				SetColor(sibling, Color::Red);
				RotateRight(root, sibling);
				sibling = parent->Right;
			}
			SetColor(sibling, parent->Color);
			SetColor(parent, Color::Black);
			SetColor(sibling->Right, Color::Black);
			RotateLeft(root, parent);
			//break;
			return 1;
		}
	}
	return 0;
}


inline int DeleteCase4(Node*& root, Node*& sibling, Node*& parent, Node*& pointer)
{
	sibling = parent->Left;
	if (GetColor(sibling) == Color::Red)
	{
		SetColor(sibling, Color::Black);
		SetColor(parent, Color::Red);
		RotateRight(root, parent);
	}
	else if (GetColor(sibling) == Color::Black)
	{
		if (GetColor(sibling->Left) == Color::Black &&
			GetColor(sibling->Right) == Color::Black)
		{
			SetColor(sibling, Color::Red);
			if (GetColor(parent) == Color::Red)
			{
				SetColor(parent, Color::Black);
			}
			else if (GetColor(parent) == Color::Black)
			{
				SetColor(parent, Color::Black);
			}
			pointer = parent;
		}
		else if (GetColor(sibling->Left) != Color::Black
			|| GetColor(sibling->Right) != Color::Black)
		{
			if (GetColor(sibling->Left) == Color::Black)
			{
				SetColor(sibling->Right, Color::Black);
				SetColor(sibling, Color::Red);
				RotateLeft(root, sibling);
				sibling = parent->Left;
			}
			SetColor(sibling, parent->Color);
			SetColor(parent, Color::Black);
			SetColor(sibling->Left, Color::Black);
			RotateRight(root, parent);
			//break;
			return 1;
		}
	}
	return 0;
}


void FixDeleteRBTree(Node*& root, Node*& node)
{
	//node == root || node == nullptr.
	if (DeleteCase1(root, node) == 1)
	{
		return;
	}

	if (GetColor(node) == Color::Red
		|| GetColor(node->Left) == Color::Red
		|| GetColor(node->Right) == Color::Red)
	{
		DeleteCase2(root, node);
	}
	else if (GetColor(node) != Color::Red
		&& GetColor(node->Left) != Color::Red
		&& GetColor(node->Right) != Color::Red)
	{
		Node* sibling = nullptr;
		Node* parent = nullptr;
		Node* pointer = node;
		SetColor(pointer, Color::DoubleBlack);
		while (pointer != root && GetColor(pointer) == Color::DoubleBlack)
		{
			parent = pointer->Parent;
			if (pointer == parent->Left)
			{
				if (DeleteCase3(root, sibling, parent, pointer) == 1)
				{
					break;
				}

			}
			else if (pointer != parent->Left)
			{
				if (DeleteCase4(root, sibling, parent, pointer) == 1)
				{
					break;
				}
			}
		}

		if (node == node->Parent->Left)
		{
			node->Parent->Left = nullptr;
		}
		else if (node == node->Parent->Right)
		{
			node->Parent->Right = nullptr;
		}
		delete node;
		SetColor(root, Color::Black);
	}
}

Node* MinValueNode(Node*& node)
{
	Node* pointer = node;

	while (pointer->Left != nullptr)
	{
		pointer = pointer->Left;
	}

	return pointer;
}

Node* DeleteNode(Node*& root, std::string KEY)
{
	if (root == nullptr)
	{
		return root;
	}
	key new_key = key(KEY);
	if (new_key < root->KEY)
	{
		return DeleteNode(root->Left, KEY);
	}

	if (new_key > root->KEY)
	{
		return DeleteNode(root->Right, KEY);
	}

	if (root->Left == nullptr || root->Right == nullptr)
	{
		return root;
	}

	Node* temp = MinValueNode(root->Right);
	root->KEY = temp->KEY;
	return DeleteNode(root->Right, temp->KEY.key_val);
}


void DeleteValue(Node*& root, std::string KEY)
{
	Node* node = DeleteNode(root, KEY);
	FixDeleteRBTree(root, node);
}





Node* Find(Node* node, std::string KEY)
{
	if (node == nullptr)
	{
		throw std::exception("Does not exist\n");
	}

	if (node->KEY.key_val == KEY)
	{
		return node;
	}

	if (node->KEY.key_val > KEY)
	{
		return Find(node->Left, KEY);
	}

	return Find(node->Right, KEY);
}


void FreeTree(Node* node)
{
	if (node == nullptr)
	{
		return;
	}

	FreeTree(node->Left);
	FreeTree(node->Right);
	delete node;
}