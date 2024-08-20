#include "Tree.h"
#include <utility>

Tree::Tree() = default;

Tree::~Tree() {
    deleteTree(root);
}

Tree::Tree(const Element& element) : root(new Node(std::move(element))){
}

Node* Tree::getRoot() const {
    return root;
}

bool Tree::insert(const Element &element) {
    bool inserted = false;
    root = insertRec(root, element, inserted);
    return inserted;
}

bool Tree::remove(const Element &element) {
    if(removeRec(root, element)) {
        cout << "Success remove\n";
        return true;
    }
    cout << "Failed remove\n";
    return false;
}

bool Tree::find(const Element &element) const {
    return findRec(root, element);
}

bool Tree::isEmpty() const {
    return !root;
}

void Tree::print(std::ostream& os) const {
    printRec(os, root);
}

void Tree::print() const {
    printRec(root);
}

void Tree::printTree(std::ostream& os) const {
    short space = 0;
    drawTree(os, root, space);
}

void Tree::printTree() const {
    short space = 0;
    drawTree(root, space);
}

Node* Tree::insertRec(Node*& node, const Element& element, bool& inserted) {
    if (node == nullptr) {
        inserted = true;
        return new Node(element);
    }

    if (element < node->getElement()) {
        node->_left = insertRec(node->_left, element, inserted);
    } else if (element > node->getElement()) {
        node->_right = insertRec(node->_right, element, inserted);
    }

    return node;
}

bool Tree::removeRec(Node *&node, const Element &element) {
    if(node == nullptr)
        return false;
    if(element < node->getElement())
        return removeRec(node->_left, element);
    if(element > node->getElement())
        return removeRec(node->_right, element);

    if(node->getElement() == element) {
        if(node->_left == nullptr)
            node = node->_right;
        else if(node->_right == nullptr)
            node = node->_left;
        else {
            removeMinRight(node->_right, node);
        }
        return true;
    }

    return false;
}


void Tree::removeMinRight(Node *&root, Node *&q) {
    if(root->_left != nullptr)
        removeMinRight(root->_left, q);
    else {
        q->setElement(root->getElement());
        root = root->_right;
    }
}

bool Tree::findRec(const Node *node, const Element &element) {
    if(node == nullptr)
        return false;

    if(element < node->getElement())
        return findRec(node->_left, element);
    if(element > node->getElement())
        return findRec(node->_right, element);
    if(element == node->getElement())
        return true;

    return false;
}

void Tree::deleteTree(Node *&node) {
    if(node != nullptr) {
        deleteTree(node->_left);
        deleteTree(node->_right);

        delete node;
        node = nullptr;
    }
}

void Tree::printRec(std::ostream& os, const Node* node) {
    if (node == nullptr)
        return;

    if (node->_right)
        printRec(os, node->_right);

    os << node->getElement() << " ";

    if (node->_left)
        printRec(os, node->_left);
}

void Tree::printRec(const Node *node) {
    if(node == nullptr)
        return;

    if(node->_right)
        printRec(node->_right);

    cout << node->getElement() << " ";

    if(node->_left)
        printRec(node->_left);

}

void Tree::drawTree(std::ostream& os, const Node* node, short space) {
    if (node != nullptr)
    {
        drawTree(os, node->_right, space + 4);

        for (int i = 1; i <= space; i++) {
            os << " ";
        }

        os << node->getElement() << " \n";

        drawTree(os, node->_left, space + 4);
    }
}

void Tree::drawTree(const Node *node, short space) {
    if(node != nullptr)
    {
        drawTree(node->_right, space + 4);

        for (int i = 1; i <= space; i++) {
            cout << " ";
        }

        cout << node->getElement() << " \n";

        drawTree(node->_left, space + 4);
    }
}
