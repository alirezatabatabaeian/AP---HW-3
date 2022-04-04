#ifndef BST_H
#define BST_H
#include <compare>
#include <functional>
#include <initializer_list>
#include <iomanip>
#include <iostream>
#include <vector>
class BST {
public:
    class Node {
    public:
        Node(int value, Node* left, Node* right);
        Node();
        Node(const Node& node);
        std::partial_ordering operator<=>(int value) const;
        bool operator==(int value) const;
        friend std::ostream& operator<<(std::ostream& cout, const BST::Node& node);

        int value;
        Node* left;
        Node* right;
    };

    BST();
    ~BST();
    BST(const BST& bst);
    BST(BST&& bst);
    Node*& get_root() { return root; }
    void bfs(std::function<void(Node*& node)> func) const;
    size_t length() const;
    bool add_node(int value);
    Node** find_node(int value);
    Node** find_parrent(int value);
    Node** find_successor(int value);
    bool delete_node(int value);
    BST(std::initializer_list<int>);
    friend std::ostream& operator<<(std::ostream& cout, const BST& bst);
    BST& operator=(BST& bst);
    BST& operator=(BST&& bst);

private:
    Node* root;
};

#endif // BST_H