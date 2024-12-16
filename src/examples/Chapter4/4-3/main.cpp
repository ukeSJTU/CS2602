#include <iostream>

#include "BinaryTree.h"
#include "SeqStack.h"

using namespace datastructures;

// 这是一个独立的非递归前序遍历函数，接收二叉树作为参数
template <class elemType>
void nonRecursivePreOrder(BTree<elemType> &tree)
{
    if (tree.isEmpty()) {
        return;
    }

    TreeNode<elemType> *currentNode = tree.getRoot();
    SeqStack<TreeNode<elemType> *> stack;

    stack.push(currentNode);
    while (!stack.isEmpty()) {
        currentNode = stack.top();
        stack.pop();

        // 使用 BTree 的 getData 方法访问节点的数据
        std::cout << tree.getData(currentNode) << " ";

        // 先压右子节点，再压左子节点，保证左子节点先被访问
        if (tree.getRight(currentNode) != nullptr) {
            stack.push(tree.getRight(currentNode));
        }
        if (tree.getLeft(currentNode) != nullptr) {
            stack.push(tree.getLeft(currentNode));
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

    // 输出前序遍历结果
    std::cout << "非递归前序遍历结果: ";
    nonRecursivePreOrder(tree);

    return 0;
}
