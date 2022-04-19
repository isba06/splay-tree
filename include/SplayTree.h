#pragma once

#include <vector>

class SplayTree
{
public:
    struct Node;

    bool insert(int value);
    bool contains(int value) const;
    bool remove(int value);
    std::size_t size() const;
    bool empty() const;
    std::vector<int> values() const;
    void print(const std::string & prefix, const Node * node, bool isLeft) const;
    void print() const;
    SplayTree() = default;
    SplayTree(Node * node);
    SplayTree(int value);
    ~SplayTree()
    {
        deleteTree(root);
    }

private:
    Node * root = nullptr;
    std::size_t sizeTree = 0;

    bool splay(Node * node);
    void rotate(Node * node);
    bool find(int value, Node * node, Node *& ptr_value) const;
    void merge(Node * tree1, Node * tree2);
    void deleteTree(Node * begin);
    void traverse(Node * begin, std::vector<int> & values) const;
};
