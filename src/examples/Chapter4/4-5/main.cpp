#include <iostream>

#include "BinaryTree.h"
#include "SeqStack.h"

using namespace datastructures;

// 这是一个独立的非递归中序遍历函数，接收二叉树作为参数
template <class elemType>
void nonRecursiveInOrder(BTree<elemType> &tree)
{
    if (tree.isEmpty()) {
        return;
    }

    TreeNode<elemType> *currentNode = tree.getRoot();
    SeqStack<TreeNode<elemType> *> stack;

    // 从根节点开始
    while (currentNode != nullptr || !stack.isEmpty()) {
        // 到达最左节点，所有的左子节点入栈
        while (currentNode != nullptr) {
            stack.push(currentNode);
            currentNode = tree.getLeft(currentNode);
        }

        // 弹出栈顶节点，访问它的数据
        currentNode = stack.top();
        stack.pop();
        std::cout << tree.getData(currentNode) << " ";

        // 访问右子树
        currentNode = tree.getRight(currentNode);
    }
    std::cout << std::endl;
}

int main()
{
    // 创建二叉树
    BTree<int> tree;

    // 创建二叉树并插入数据，假设 flag 值为 -1 表示空节点
    tree.createTree(-1);

    // 输出中序遍历结果
    std::cout << "非递归中序遍历结果: ";
    nonRecursiveInOrder(tree);

    return 0;
}
