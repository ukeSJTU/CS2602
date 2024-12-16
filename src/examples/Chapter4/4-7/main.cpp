#include <iostream>

#include "BinaryTree.h"
#include "SeqStack.h"

using namespace datastructures;

// 这是一个独立的非递归后序遍历函数，接收二叉树作为参数
template <class elemType>
void nonRecursivePostOrder(BTree<elemType> &tree)
{
    if (tree.isEmpty()) {
        return;
    }

    TreeNode<elemType> *currentNode = tree.getRoot();
    SeqStack<TreeNode<elemType> *> stack;
    TreeNode<elemType> *lastVisited = nullptr;

    while (!stack.isEmpty() || currentNode != nullptr) {
        if (currentNode != nullptr) {
            stack.push(currentNode);
            currentNode = tree.getLeft(currentNode);
        } else {
            TreeNode<elemType> *peekNode = stack.top();

            // 如果右子树为空或右子树已经访问过，访问当前节点
            if (tree.getRight(peekNode) == nullptr || tree.getRight(peekNode) == lastVisited) {
                std::cout << tree.getData(peekNode) << " ";
                stack.pop();
                lastVisited = peekNode;
            } else {
                // 否则，访问右子树
                currentNode = tree.getRight(peekNode);
            }
        }
    }
    std::cout << std::endl;
}

int main()
{
    // 创建二叉树
    BTree<int> tree;

    // 创建二叉树并插入数据，假设 flag 值为 -1 表示空节点
    tree.createTree(-1);

    // 输出后序遍历结果
    std::cout << "非递归后序遍历结果: ";
    nonRecursivePostOrder(tree);

    return 0;
}