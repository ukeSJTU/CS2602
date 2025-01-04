#include <iostream>

#include "AVLTree.h"

using namespace datastructures;

int main()
{
    AvlTree<int> avlTree;
    int n;

    // 读取节点数量
    std::cout << "请输入要插入AVL树的整数个数: ";
    std::cin >> n;

    std::cout << "请输入 " << n << " 个整数，使用空格分隔: ";
    for (int i = 0; i < n; ++i) {
        int value;
        std::cin >> value;
        avlTree.insertValue(value);
    }

    // 输出中序遍历结果
    std::cout << "AVL 树的中序遍历结果: ";
    avlTree.inOrder();
    std::cout << std::endl;

    return 0;
}