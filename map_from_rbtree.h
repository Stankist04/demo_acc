#pragma once

#ifndef RBTREE_H
#define RBTREE_H

#include <iostream>

enum class Color
{
    Red,
    Black,
    DoubleBlack
};

class key
{
public:
    std::string key_val;
    key() {
        this->key_val = "";
    }
    key(std::string val) {
        this->key_val = val;
    }
    bool operator <(key& key2) {
        int i = this->key_val.compare(key2.key_val);
        if (i > 0) return false;
        else if (i == 0) return false;
        else return true;
    }
    bool operator >(key& key2) {
        int i = this->key_val.compare(key2.key_val);
        if (i > 0) return true;
        else if (i == 0) return false;
        else return false;
    }
    bool operator == (key& key2) {
        int i = this->key_val.compare(key2.key_val);
        if (i > 0) return false;
        else if (i == 0) return true;
        else return false;
    }
};

struct Node
{
    key KEY;
    Color Color = Color::Red;
    Node* Left = nullptr;
    Node* Right = nullptr;
    Node* Parent = nullptr;
    std::string Name = "";
};


struct RBTree
{
    Node* Root = nullptr;
};

void RotateLeft(Node*& root, Node*& node);

void RotateRight(Node*& root, Node*& node);

void FixInsertRBTree(Node*& root, Node*& node);

void FixDeleteRBTree(Node*& root, Node*& node);

Color GetColor(Node* node);

void SetColor(Node*& node, Color color);

void InsertValue(Node*& root, std::string KEY, std::string Name);

Node* InsertNode(Node*& root, Node*& node);

Node* DeleteNode(Node*& root, std::string KEY);

void DeleteValue(Node*& root, std::string KEY);

Node* MinValueNode(Node*& node);

Node* Find(Node* node, std::string KEY);

void FreeTree(Node* node);

void PrintTree(Node* node, const int indent);

#endif //RBTREE_H
