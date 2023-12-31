#pragma once

#include <string>
#include <vector>

class SplayTree
{
public:
    bool insert(int value);
    bool contains(int value) const;
    bool remove(int value);
    std::size_t size() const;
    bool empty() const;
    std::vector<int> values() const;
    void print() const;
    SplayTree() = default;
    ~SplayTree();

private:
    struct Node;
    Node * root = nullptr;
    std::size_t sizeTree = 0;

    void splay(Node * node);
    bool splay(int value);
    void rotate(Node * node);
    bool find_lower_bound(int value, Node * node, Node *& ptr_value) const;
    void merge(Node * tree1, Node * tree2);
    void traverse(Node * begin, std::vector<int> & values) const;
    void print(const std::string & prefix, const Node * node, bool isLeft) const;
    Node * search_large_element(SplayTree::Node * node);
};
