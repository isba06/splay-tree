#include "SplayTree.h"

#include <algorithm>
#include <iostream>

struct SplayTree::Node
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
        delete left;
        delete right;
    }
};

SplayTree::~SplayTree()
{
    delete root;
}

void SplayTree::print(const std::string & prefix, const Node * node, bool isLeft) const
{
    if (node != nullptr) {
        std::cout << prefix;
        std::cout << (isLeft ? "├──" : "└──");
        std::cout << node->key << std::endl;
        print(prefix + (isLeft ? "│   " : "    "), node->left, true);
        print(prefix + (isLeft ? "│   " : "    "), node->right, false);
    }
}

void SplayTree::print() const
{
    print("", root, false);
}

bool SplayTree::empty() const
{
    return root == nullptr;
}

bool SplayTree::contains(int value) const
{
    return const_cast<SplayTree *>(this)->splay(value);
}

bool SplayTree::find_lower_bound(int value, Node * node, Node *& ptr_value) const
{
    if (node == nullptr) {
        return false;
    }
    while (true) {
        if (node->key == value) {
            ptr_value = node;
            return true;
        }
        if (node->key < value) {
            if (node->right != nullptr)
                node = node->right;
            else {
                ptr_value = node;
                return false;
            }
        }
        if (node->key > value) {
            if (node->left != nullptr)
                node = node->left;
            else {
                ptr_value = node;
                return false;
            }
        }
    }
}

SplayTree::Node * SplayTree::search_large_element(SplayTree::Node * node)
{
    while (node && node->right) {
        node = node->right;
    }
    return node;
}

void SplayTree::merge(Node * tree_left, Node * tree_right)
{
    Node * new_root;
    if (tree_left == nullptr) {
        this->root = tree_right;
        this->root->parent = nullptr;
        return;
    }
    if (tree_left->right == nullptr) {
        new_root = tree_left;
    }
    else {
        new_root = search_large_element(tree_left);
    }
    splay(new_root);
    new_root->right = tree_right;
    if (tree_right) {
        tree_right->parent = new_root;
    }
}

bool SplayTree::remove(int value)
{
    Node * node;
    if (!find_lower_bound(value, root, node)) {
        return false;
    }
    if (node->left == nullptr && node->right == nullptr) {
        if (root == node) {
            delete node;
            this->root = nullptr;
            sizeTree--;
            return true;
        }
        (node->parent->left == node ? node->parent->left : node->parent->right) = nullptr;
        node->left = nullptr;
        node->right = nullptr;
        delete node;
        sizeTree--;
        return true;
    }
    splay(node);
    merge(node->left, node->right);
    node->left = nullptr;
    node->right = nullptr;
    delete node;
    sizeTree--;
    return true;
}

void SplayTree::traverse(Node * begin, std::vector<int> & values) const
{
    if (begin) {
        traverse(begin->left, values);
        values.emplace_back(begin->key);
        traverse(begin->right, values);
    }
}

std::vector<int> SplayTree::values() const
{
    std::vector<int> val;
    val.reserve(sizeTree);
    traverse(root, val);
    return val;
}

std::size_t SplayTree::size() const
{
    return sizeTree;
}

void SplayTree::rotate(Node * node)
{
    Node * parent = node->parent;
    Node * gparent = node->parent->parent;
    if (parent->left == node) {
        parent->left = node->right;
        if (node->right != nullptr) {
            node->right->parent = parent;
        }
        node->right = parent;
    }
    else {
        parent->right = node->left;
        if (node->left != nullptr) {
            node->left->parent = parent;
        }
        node->left = parent;
    }
    parent->parent = node;
    if (parent == root) {
        root = node;
        root->parent = nullptr;
    }
    else {
        if (gparent->left == parent) {
            gparent->left = node;
        }
        else {
            gparent->right = node;
        }
        node->parent = gparent;
    }
}

void SplayTree::splay(Node * node)
{
    while (node != root) {
        if (node->parent != root && (node->parent->left == node) == (node->parent->parent->left == node->parent)) {
            rotate(node->parent);
        }
        rotate(node);
    }
}

bool SplayTree::splay(int value)
{
    Node * node;
    if (find_lower_bound(value, root, node)) {
        splay(node);
        return true;
    }
    return false;
}

bool SplayTree::insert(int value)
{
    if (root == nullptr) {
        root = new Node(value);
        sizeTree++;
        return true;
    }
    Node * node;
    if (!find_lower_bound(value, root, node)) {
        Node * ptr_new_node = new Node(value);
        if (node->key < value) {
            node->right = ptr_new_node;
            ptr_new_node->parent = node;
            splay(ptr_new_node);
            sizeTree++;
            return true;
        }
        node->left = ptr_new_node;
        ptr_new_node->parent = node;
        splay(ptr_new_node);
        sizeTree++;
        return true;
    }
    return false;
}
