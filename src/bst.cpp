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
    while (Vec.empty() == 0) {
        Node* node = Vec[0];
        Vec.erase(Vec.begin());
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

size_t BST::length() const
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

BST::Node** BST::find_node(int _value)
{
    BST::Node** temp { &root };
    while (true) {
        if (*temp == nullptr) {
            return nullptr;
        } else if ((*temp)->value == _value) {
            return temp;
        } else if (_value > (*temp)->value) {
            if ((*temp)->right == nullptr) {
                return nullptr;
            } else {
                temp = &(*temp)->right;
            }
        } else if (_value < (*temp)->value) {
            if ((*temp)->left == nullptr) {
                return nullptr;
            } else {
                temp = &(*temp)->left;
            }
        }
    }
    return nullptr;
}

BST::Node** BST::find_parrent(int _value)
{
    BST::Node** temp { &root };
    BST::Node** parrent { nullptr };
    while (true) {
        if (*temp == nullptr) {
            return nullptr;
        } else if (root->value == _value) {
            return nullptr;
        } else if ((*temp)->value == _value) {
            return parrent;
        } else if (_value > (*temp)->value) {
            if ((*temp)->right == nullptr) {
                return nullptr;
            } else {
                parrent = temp;
                temp = &(*temp)->right;
            }
        } else if (_value < (*temp)->value) {
            if ((*temp)->left == nullptr) {
                return nullptr;
            } else {
                parrent = temp;
                temp = &(*temp)->left;
            }
        }
    }
    return nullptr;
}

BST::Node** BST::find_successor(int _value)
{
    BST::Node** node { find_node(_value) };
    if (*node == nullptr) {
        return nullptr;
    } else if ((*node)->left == nullptr) {
        return node;
    } else {
        BST::Node** temp { &(*node)->left };
        while (true) {
            if ((*temp)->right == nullptr) {
                return temp;
            } else {
                temp = &(*temp)->right;
            }
        }
    }
    return nullptr;
}

bool BST::delete_node(int _value)
{
    BST::Node** node { find_node(_value) };
    if (*node == nullptr) {
        return false;
    } else if (((*node)->left == nullptr) && ((*node)->right == nullptr)) {
        BST::Node** parrent { find_parrent(_value) };
        if (_value > (*parrent)->value) {
            (*parrent)->right = nullptr;
            // delete node;
            return true;
        } else if (_value < (*parrent)->value) {
            (*parrent)->left = nullptr;
            // delete node;
            return true;
        }

    } else if ((*node)->left == nullptr) {
        BST::Node** parrent { find_parrent(_value) };
        if (_value > (*parrent)->value) {
            (*parrent)->right = (*node)->right;
            // delete node;
            return true;
        } else if (_value < (*parrent)->value) {
            (*parrent)->left = (*node)->right;
            // delete node;
            return true;
        }
    } else if ((*node)->right == nullptr) {
        BST::Node** parrent { find_parrent(_value) };
        if (_value > (*parrent)->value) {
            (*parrent)->right = (*node)->left;
            // delete node;
            return true;
        } else if (_value < (*parrent)->value) {
            (*parrent)->left = (*node)->left;
            // delete node;
            return true;
        }
    } else {
        BST::Node** successor { find_successor(_value) };
        BST::Node** successor_parrent { find_parrent((*successor)->value) };
        BST::Node** parrent { find_parrent(_value) };
        if ((*successor)->value > (*successor_parrent)->value) {
            (*successor_parrent)->right = nullptr;
        } else if ((*successor)->value) < (*successor_parrent)->value)
            {
                (*successor_parrent)->left = nullptr;
            }
        if ((*node)->value) > (*parrent)->value)
            {
                (*parrent)->right = *successor;
            }
        else if ((*node)->value) < (*parrent)->value)
            {
                (*parrent)->left = *successor;
            }
        if ((*node)->right != nullptr) {
            (*successor)->right = (*node)->right;
        }
        if ((*node)->left != nullptr) {
            (*successor)->left = (*node)->left;
        }
    }
}