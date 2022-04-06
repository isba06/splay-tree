#pragma once
#include <iostream>
#include <vector>
struct Node
{
    int key;
    Node * parent = nullptr;
    Node * left = nullptr;
    Node * right = nullptr;

    Node() = default;
    Node(int value)
        : key(value)
    {
    }
    ~Node()
    {
        parent = nullptr;
        left = nullptr;
        right = nullptr;
    }
};

class SplayTree
{
    Node * root = nullptr;

public:
    inline Node * getRoot() const
    {
        return root;
    }
    bool splay(Node * node);
    void rotate(Node * node);
    bool find(int value, Node * node, Node *& ptr_value) const;
    bool insert(int value);
    void merge(Node * tree1, Node * tree2);
    void traverse(Node * begin, std::size_t & count) const;
    void traverse(Node * begin, std::vector<int> & values) const;
    bool contains(int value) const;
    bool remove(int value);
    std::size_t size() const;
    bool empty() const;
    std::vector<int> values() const;
    void print(const std::string & prefix, const Node * node, bool isLeft) const;
    inline void print() const
    {
        print("", root, false);
    }
    SplayTree() = default;
    SplayTree(Node * _root)
        : root(_root)
    {
    }
    ~SplayTree()
    {
        delete root;
        root = nullptr;
    }
};
