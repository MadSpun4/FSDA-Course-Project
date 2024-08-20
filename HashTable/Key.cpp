#include "Key.h"

Key::Key(Tree *tree) : _status(0), _tree(tree)
{
}

Tree *Key::getTree() const
{
    return _tree;
}

short Key::getStatus() const
{
    return _status;
}

void Key::setStatus(const short status)
{
    _status = status;
}
