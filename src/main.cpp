#include "SplayTree.h"

#include <iostream>

int main()
{
    SplayTree tree;
    for (int i = 10; i > 0; --i) {
        tree.insert(i);
    }
    tree.print();

    for (const auto value : tree.values()) {
        std::cout << value << std::endl; // 1 .. 10
    }
    return 0;
}
