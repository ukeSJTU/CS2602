#include <cmath>
#include <iostream>

#include "BinarySearchTree.h"
#include "LinkQueue.h"

using namespace datastructures;

int main()
{
    long long value;
    BinarySearchTree<long long> tree;
    while (std::cin >> value) {
        tree.insert(value);
    }

    LinkQueue<long long> inOrderQueue;
    tree.inOrder(&inOrderQueue);

    long long prev = inOrderQueue.front();
    inOrderQueue.deQueue();
    long long current = inOrderQueue.front();
    inOrderQueue.deQueue();

    long long min_diff = std::abs(current - prev);

    while (!inOrderQueue.isEmpty()) {
        prev = current;
        current = inOrderQueue.front();
        inOrderQueue.deQueue();
        if (std::abs(current - prev) < min_diff) {
            min_diff = std::abs(current - prev);
        }
    }

    std::cout << min_diff << std::endl;
    return 0;
}