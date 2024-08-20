#include "Node.h"

#include <utility>

Node::Node() : _left(nullptr), _right(nullptr) {}

Node::Node(Element element, Node *left, Node *right) : _left(left), _right(right), _element(std::move(element)){
}

Element Node::getElement() const {
    return _element;
}

void Node::setElement(const Element &element) {
    _element = element;
}
