#include "bst.h"

BST::Node::Node(int _value, Node* _left, Node* _right)
    : value { _value }
    , left { _left }
    , right { _right }
{
}

BST::Node::Node()
    : value {}
    , left { nullptr }
    , right { nullptr }
{
}

BST::Node::Node(const Node& node)
    : value { node.value }
    , left { node.left }
    , right { node.right }
{
}

