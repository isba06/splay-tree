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
        left = nullptr;
        right = nullptr;
    }
};

SplayTree::SplayTree(Node * node)
    : root(node)
{
}

SplayTree::SplayTree(int value)
    : root(new Node(value))
{
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
    if (root == nullptr)
        return true;
    else
        return false;
}

bool SplayTree::contains(int value) const
{
    Node * node = root;
    if (find(value, root, node)) {
        const_cast<SplayTree *>(this)->splay(node);
        return true;
    }
    return false;
}

bool SplayTree::find(int value, Node * node, Node *& ptr_value) const
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
            else
                return false;
        }
        if (node->key > value) {
            if (node->left != nullptr)
                node = node->left;
            else
                return false;
        }
    }
    return false;
}

SplayTree::Node * search_large_element(SplayTree::Node * node)
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
    else if (tree_left->right == nullptr)
        new_root = tree_left;
    else
        new_root = search_large_element(tree_left);
    splay(new_root);
    new_root->right = tree_right;
    if (tree_right)
        tree_right->parent = new_root;
}

bool SplayTree::remove(int value)
{
    Node * node;
    if (find(value, root, node)) {
        if (node->left == nullptr && node->right == nullptr) {
            if (root == node) {
                delete node;
                this->root = nullptr;
                sizeTree--;
                return true;
            }
            node->parent->left == node ? node->parent->left = nullptr : node->parent->right = nullptr;
            delete node;
            sizeTree--;
            return true;
        }
        splay(node);
        merge(node->left, node->right);
        delete node;
        sizeTree--;
        return true;
    }
    else
        return false;
}

void SplayTree::deleteTree(Node * node)
{
    if (node) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
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
        if (node->right != nullptr)
            node->right->parent = parent;
        node->right = parent;
        parent->parent = node;
        if (parent == root) {
            node->parent = nullptr;
            root = node;
        }
        else {
            if (gparent->left == parent)
                gparent->left = node;
            else
                gparent->right = node;
            node->parent = gparent;
        }
    }
    if (parent->right == node) {
        parent->right = node->left;
        if (node->left != nullptr)
            node->left->parent = parent;
        node->left = parent;
        parent->parent = node;
        if (parent == root) {
            node->parent = nullptr;
            root = node;
        }
        else {
            if (gparent->left == parent)
                gparent->left = node;
            else
                gparent->right = node;
            node->parent = gparent;
        }
    }
}

bool isZigZig(SplayTree::Node * node)
{
    if (node->parent != nullptr) {
        if (node->parent->parent->left != nullptr && node == node->parent->parent->left->left)
            return true;
        if (node->parent->parent->right != nullptr && node == node->parent->parent->right->right)
            return true;
    }
    return false;
}

bool isZigZag(SplayTree::Node * node)
{
    if (node->parent != nullptr) {
        if (node->parent->parent->left != nullptr && node == node->parent->parent->left->right)
            return true;
        if (node->parent->parent->right != nullptr && node == node->parent->parent->right->left)
            return true;
    }
    return false;
}

bool SplayTree::splay(Node * node)
{
    while (node != root) {
        if (node->parent == root) {
            rotate(node);
            return true;
        }
        if (node->parent != root && isZigZig(node)) {
            rotate(node->parent);
            rotate(node);
        }
        if (node->parent != root && isZigZag(node)) {
            rotate(node);
            rotate(node);
        }
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
    Node * node = root;
    Node * ptr_new_node = new Node(value);
    while (true) {
        if (node->key < value) {
            if (node->right == nullptr) {
                node->right = ptr_new_node;
                ptr_new_node->parent = node;
                splay(ptr_new_node);
                sizeTree++;
                return true;
            }
            node = node->right;
            continue;
        }
        if (node->key > value) {
            if (node->left == nullptr) {
                node->left = ptr_new_node;
                ptr_new_node->parent = node;
                splay(ptr_new_node);
                sizeTree++;
                return true;
            }
            node = node->left;
            continue;
        }
        if (node->key == value) {
            delete ptr_new_node;
            return false;
        }
    }
}
