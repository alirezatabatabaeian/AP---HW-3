#ifndef BST_H
#define BST_H
#include <compare>
#include <iomanip>
#include <iostream>
class BST {
public:
    class Node {
    public:
        Node(int value, Node* left, Node* right);
        Node();
        Node(const Node& node);
        std::partial_ordering operator<=>(int _value) const;
        bool operator==(int _value) const;
        friend std::ostream& operator<<(std::ostream& cout, const BST::Node& node);

        int value;
        Node* left;
        Node* right;
    };

    Node*& get_root() { return root; }
    void bfs(std::function<void(Node*& node)> func);
    //  size_t length();
    //  bool add_node(int value);
    //  Node** find_node(int value);
    //  Node** find_parrent(int value);
    //  Node** find_successor(int value);
    //  bool delete_node(int value);

private:
    Node* root;
};

#endif // BST_H