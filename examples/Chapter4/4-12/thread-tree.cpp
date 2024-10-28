#include <iostream>
#include "btree.h"

int main()
{

    BTree<char> tree;
    char flag = '#';

    tree.createTree(flag);
    std::cout << std::endl;

    Node<char> *first;
    first = tree.threadMid();

    std::cout << "visit midThreadtree in mid order:" << std::endl;
    tree.threadMidVisit(first);

    std::cout << "visit midThreadtree in pre order:" << std::endl;
    tree.threadMidePreVisit();

    return 0;
}