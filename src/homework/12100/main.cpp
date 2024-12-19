#include <iostream>

#include "HuffmanTree.h"
#include "PriorityQueue.h"

void calculateWeight(datastructures::HuffmanTreeNode<int> *root, int height, int &total)
{
    if (root == nullptr) {
        return;
    }

    if (root->data != 0) {
        total = total + height * root->weight;
    }

    calculateWeight(root->left, height + 1, total);
    calculateWeight(root->right, height + 1, total);
}

int main()
{
    int n;
    std::cin >> n;

    // 创建优先队列存储初始节点
    datastructures::PriorityQueue<datastructures::HuffmanTreeNode<int>> pq(n);

    // 读取权重并创建初始节点
    for (int i = 0; i < n; i++) {
        double weight;
        std::cin >> weight;
        // 创建新节点并加入优先队列
        datastructures::HuffmanTreeNode<int> node(i + 1, weight);
        pq.enQueue(node);
    }

    // 构建哈夫曼树
    datastructures::HuffmanTree<int> huffmanTree;
    huffmanTree.buildTree(pq);

    int total_weight = 0;
    calculateWeight(huffmanTree.getRoot(), 0, total_weight);

    std::cout << total_weight << std::endl;

    return 0;
}