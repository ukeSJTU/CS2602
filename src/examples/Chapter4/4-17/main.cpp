#include <iostream>

#include "HuffmanTree.h"

int main()
{
    // 示例数据
    const int n = 6;                                // 叶子节点数
    char data[n] = {'A', 'B', 'C', 'D', 'E', 'F'};  // 节点的值
    double weights[n] = {3, 8, 10, 12, 50, 4};      // 节点的权重

    // 构建哈夫曼树
    datastructures::HuffmanTree<char> huffmanTree;
    huffmanTree.buildTree(data, weights, n);

    huffmanTree.disp();

    return 0;
}
