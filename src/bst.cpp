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

std::ostream& operator<<(std::ostream& cout, const BST::Node& node)
{
    cout << std::setw(20) << std::left << &node << "=> "
         << "Value:" << std::setw(5) << std::left << node.value
         << "Left:" << std::setw(20) << std::left << node.left
         << "Right:" << std::setw(20) << std::left << node.right;
    return cout;
}

std::partial_ordering BST::Node::operator<=>(int _value) const { return value <=> _value; }

bool BST::Node::operator==(int _value) const { return value == _value; }

void BST::bfs(std::function<void(Node*& node)> func){
    while(node != ){

    }
}
