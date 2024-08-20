#ifndef KEY_H
#define KEY_H
#include "../Tree/Tree.h"

class Key
{
public:
    Key();
    Key(Tree *tree);
    Tree *getTree() const;

    short getStatus() const;
    void setStatus(short status);

private:
    short _status;
    Tree *_tree;
};

#endif // KEY_H
