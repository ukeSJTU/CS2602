#include "LinkList.h"
#include <iostream>

using namespace datastructures;

class MinStepsBinaryTree {
  private:
    int nodeCount; // 节点总数

    // 获取节点的父节点编号
    int getParent(int node) { return node / 2; }

  public:
    MinStepsBinaryTree(int n) : nodeCount(n) {}

    // 计算两节点间最短距离
    int findMinSteps(int a, int b) {
        if (a == b)
            return 0;

        int steps = 0;
        int node1 = a;
        int node2 = b;

        // 同时向上移动直到找到公共祖先
        while (node1 != node2) {
            // 编号大的节点向上移动一层
            if (node1 > node2) {
                node1 = getParent(node1);
                steps++;
            } else {
                node2 = getParent(node2);
                steps++;
            }
        }

        return steps;
    }
};

int main() {
    int n;
    std::cin >> n; // 节点数量

    LinkList<int> nodeList;
    nodeList.insert(0, 0); // 根节点

    // 读取层序遍历（由于是满二叉树且不需要构建树结构，可以直接跳过）
    for (int i = 1; i <= n; i++) {
        int value;
        std::cin >> value;
        nodeList.insert(i, value);
    }

    // 读取起点和终点
    int a, b;
    std::cin >> a >> b;

    int a_idx = nodeList.find(a);
    int b_idx = nodeList.find(b);

    MinStepsBinaryTree tree(n);
    std::cout << tree.findMinSteps(a_idx, b_idx) << std::endl;

    return 0;
}
