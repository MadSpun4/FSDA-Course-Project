#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>

#include "Key.h"

using namespace std;

class HashTable {
public:
    HashTable(unsigned size);
    bool insert(const Element &element);
    bool remove(const Element &element);
    unsigned find(const Element &element) const;

    void print(std::ostream& os) const;
    void print() const;

    // Для печати красивого дерева в app
    void printTree(std::ostream& os, unsigned short index) const;
    void printTree(unsigned short index) const;

    void inputFile(const string &path);

    Element getElement(unsigned index) const;
    const std::vector<Key*>& getKeys() const;

    bool validateData(const std::string &nameSupplier, const std::string &articul, const std::string &nameProduct);

private:
    unsigned hashFunction(const Element &element) const;

private:
    vector<Key*>table;
    unsigned countElements{};
};



#endif //HASHTABLE_H
