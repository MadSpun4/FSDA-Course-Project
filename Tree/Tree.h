#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include "../Element.h"
#include "Node.h"

using namespace std;

class Tree {
public:
    Tree();
    ~Tree();
    explicit Tree(const Element& element);

    bool insert(const Element &element);
    bool remove(const Element &element);
    bool find(const Element &element) const;
    bool isEmpty() const;

    void print(std::ostream& os) const; // Вывод в app
    void print() const;

    void printTree(std::ostream& os) const; // Вывод в app
    void printTree() const;

    Node* getRoot() const;

private:
    static Node* insertRec(Node *&node, const Element &element, bool& inserted);
    static bool removeRec(Node *&node, const Element &element);
    static void removeMinRight(Node *&root, Node *&q);
    static bool findRec(const Node *node, const Element &element);
    static void deleteTree(Node *&node);

    static void printRec(std::ostream& os, const Node* node); // Вывод в app
    static void printRec(const Node *node);

    // Для вывода красивого дерева в app
    static void drawTree(std::ostream& os, const Node* node, short space); // Вывод в app
    static void drawTree(const Node *node, short space);

private:
    Node* root{};
};

#endif //TREE_H
