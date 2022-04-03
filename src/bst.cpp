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

BST::BST()
    : root { nullptr }
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

void BST::bfs(std::function<void(Node*& node)> func) const
{
    std::vector<Node*> Vec { root };
    // Vec[0](root);
    while (Vec.empty() == 0) {
        Node* node = Vec[size(Vec) - 1];
        Vec.pop_back();
        if (node) {
            func(node);
            if ((*node).left) {
                Vec.push_back((*node).left);
            }
            if ((*node).right) {
                Vec.push_back((*node).right);
            }
        }
    }
}

size_t BST::length()const
{
    size_t num {};
    bfs([&num](BST::Node*& node) { num++; });
    return num;
}

bool BST::add_node(int _value)
{
    if (!root) {
        root = new Node(_value, nullptr, nullptr);
        return true;
    } else {
        Node* node { root };
        while (true) {
            if (_value == (*node).value) {
                return false;
            } else if (_value > (*node).value) {
                if (!(*node).right) {
                    (*node).right = new Node(_value, nullptr, nullptr);
                    return true;
                } else {
                    node = (*node).right;
                }

            } else if (_value < (*node).value) {
                if (!(*node).left) {
                    (*node).left = new Node(_value, nullptr, nullptr);
                    return true;
                } else {
                    node = (*node).left;
                }
            }
        }
    }
    return true;
}

std::ostream& operator<<(std::ostream& out, const BST& bst)
{
    std::cout << std::string(80, '*') << std::endl;
    bst.bfs([&out](BST::Node*& node) { out << std::setw(20) << std::left << node << "=> "
                                           << "Value:" << std::setw(5) << std::left << node->value
                                           << "Left:" << std::setw(20) << std::left << node->left
                                           << "Right:" << std::setw(20) << std::left << node->right
                                           << std::endl; });
    std::cout << "binary search tree size: " << bst.length() << std::endl;
    std::cout << std::string(80, '*') << std::endl;
    return out;
}
