#include "bst.h"

BST::Node::Node(int _value, Node* _left, Node* _right) // Node Constructor
    : value { _value }
    , left { _left }
    , right { _right }
{
}

BST::Node::Node() // Defult Node Constructor
    : value {}
    , left { nullptr }
    , right { nullptr }
{
}

BST::Node::Node(const Node& node) // Copy node
    : value { node.value }
    , left { node.left }
    , right { node.right }
{
}

BST::BST() // BST defult
    : root { nullptr }
{
}

BST::~BST() // BST Destructor
{
    std::vector<Node*> nodes;
    bfs([&nodes](BST::Node*& node) { nodes.push_back(node); });
    for (auto& node : nodes)
        delete node;
}

BST::BST(const BST& _bst) // BST copy constructor
    : root { nullptr }
{
    _bst.bfs([this](BST::Node*& node) { this->add_node((*node).value); });
}

BST::BST(BST&& _bst) // BST move constructor
    : root { nullptr }
{
    delete root;
    root = &(*_bst.root);
    _bst.root = nullptr;
}

std::ostream& operator<<(std::ostream& cout, const BST::Node& node) // define << operator for print
{
    cout << std::setw(20) << std::left << &node << "=> "
         << "Value:" << std::setw(5) << std::left << node.value
         << "Left:" << std::setw(20) << std::left << node.left
         << "Right:" << std::setw(20) << std::left << node.right;
    return cout;
}

BST& BST::operator=(BST& _bst) // = operator for copy
{
    if (this == &_bst) {
        return *this;
    } else {
        delete root;
        _bst.bfs([this](BST::Node*& node) { this->add_node((*node).value); });
        return *this;
    }
}

BST& BST::operator=(BST&& _bst) // = operator for move
{
    delete root;
    root = &(*_bst.root);
    _bst.root = nullptr;
    return *this;
}

std::partial_ordering BST::Node::operator<=>(int _value) const { return value <=> _value; } // define <=> operator

bool BST::Node::operator==(int _value) const { return value == _value; } // define compare operator for a node

void BST::bfs(std::function<void(Node*& node)> func) const // define bfs for running a function on a BST object
{
    std::vector<Node*> Vec { root };
    while (Vec.empty() == 0) { // iterate on nodes
        Node* node = Vec[0];
        Vec.erase(Vec.begin()); // erase a used note
        if (node) {
            func(node);
            if ((*node).left) {
                Vec.push_back((*node).left); // add child node using pushback to vector
            }
            if ((*node).right) {
                Vec.push_back((*node).right);
            }
        }
    }
}

size_t BST::length() const // find length of a BST object (number of nodes)
{
    size_t num {};
    bfs([&num](BST::Node*& node) { num++; });
    return num;
}

bool BST::add_node(int _value) // add a node
{
    if (!root) { // if not defined root
        root = new Node(_value, nullptr, nullptr); // add new root
        return true;
    } else {
        Node* node { root };
        while (true) { // iterate on nodes
            if (_value == (*node).value) { // do not add an existing node
                return false;
            } else if (_value > (*node).value) {
                if (!(*node).right) {
                    (*node).right = new Node(_value, nullptr, nullptr);
                    return true;
                } else {
                    node = (*node).right; // add node to right
                }

            } else if (_value < (*node).value) {
                if (!(*node).left) {
                    (*node).left = new Node(_value, nullptr, nullptr);
                    return true;
                } else {
                    node = (*node).left; // add node to left
                }
            }
        }
    }
    return true;
}

std::ostream& operator<<(std::ostream& out, const BST& bst) // define << operator
{
    std::cout << std::string(80, '*') << std::endl;
    bst.bfs([&out](BST::Node*& node) { out << std::setw(20) << std::left << node << "=> " // print nodes in one line
                                           << "Value:" << std::setw(5) << std::left << node->value
                                           << "Left:" << std::setw(20) << std::left << node->left
                                           << "Right:" << std::setw(20) << std::left << node->right
                                           << std::endl; });
    std::cout << "binary search tree size: " << bst.length() << std::endl;
    std::cout << std::string(80, '*') << std::endl;
    return out;
}

BST::Node** BST::find_node(int _value) // find a node in a tree
{
    BST::Node** temp { &root };
    while (true) { // using features of a tree
        if (*temp == nullptr) {
            return nullptr;
        } else if ((*temp)->value == _value) {
            return temp;
        } else if (_value > (*temp)->value) {
            if ((*temp)->right == nullptr) {
                return nullptr;
            } else {
                temp = &(*temp)->right; // return the address of node
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

BST::Node** BST::find_parrent(int _value) // find a parent of a node
{
    BST::Node** temp { &root };
    BST::Node** parrent { nullptr }; // save parent in here
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

BST::Node** BST::find_successor(int _value) // find successor of a node
{
    BST::Node** node { find_node(_value) };
    if (*node == nullptr) {
        return nullptr;
    } else if ((*node)->left == nullptr) { // if no left
        return node;
    } else {
        BST::Node** temp { &(*node)->left };
        while (true) {
            if ((*temp)->right == nullptr) { // if no right after one left
                return temp;
            } else {
                temp = &(*temp)->right;
            }
        }
    }
    return nullptr;
}

bool BST::delete_node(int _value) // delete a node
{
    BST::Node** node { find_node(_value) };
    if (node == nullptr) {
        return false;
    } else if (((*node)->left == nullptr) && ((*node)->right == nullptr)) { // delete a leaf
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

    } else if ((*node)->left == nullptr) { // delete a one child node(with right child)
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
    } else if ((*node)->right == nullptr) { // delete a one child node(with left child)
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
    } else { // delete a two children node
        BST::Node** successor { find_successor(_value) };
        BST::Node** successor_parrent { find_parrent((*successor)->value) };
        BST::Node** parrent { find_parrent(_value) };
        if ((*node)->right != nullptr) {
            (*successor)->right = (*node)->right;
        }
        if ((*node)->left != nullptr) {
            (*successor)->left = (*node)->left;
        }
        if (parrent != nullptr) { // if not to be the root
            if ((*node)->value > (*parrent)->value) {
                (*parrent)->right = *successor;
            } else if ((*node)->value < (*parrent)->value) {
                (*parrent)->left = *successor;
            }
        } else {
            root = *successor;
        }
        if ((*successor)->value > (*successor_parrent)->value) {
            (*successor_parrent)->right = nullptr;
        } else if ((*successor)->value < (*successor_parrent)->value) {
            (*successor_parrent)->left = nullptr;
        }
        return true;
    }
    return false;
}

BST& BST::operator++() // define ++a operator
{
    this->bfs([this](BST::Node*& node) { node->value++; });
    return *this;
}

BST BST::operator++(int) // define a++ operator
{
    BST temp { *this };
    this->bfs([this](BST::Node*& node) { node->value++; });
    return temp; // return a not changed version
}

BST::BST(std::initializer_list<int> _list) // to use initializing
    : root { nullptr }
{
    for (auto i : _list)
        add_node(i);
}