#ifndef NODE_H
#define NODE_H
#include "../Element.h"


class Node {
public:
    Node();

    explicit Node(Element element, Node *left=nullptr, Node *right=nullptr);

    Element getElement() const;
    void setElement(const Element &element);

    Node *_left;
    Node *_right;
private:
    Element _element;
};



#endif //NODE_H
