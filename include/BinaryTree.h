#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <cstddef>
#include <iostream>

#include "SeqQueue.h"
#include "SeqStack.h"

namespace datastructures {

// BTree 类的前向声明
template <class elemType> class BTree;

template <class elemType> class Node {
    friend class BTree<elemType>;

  private:
    elemType data;
    Node<elemType> *left, *right;
    int leftFlag;  // 用于表示是否是线索，0表示left为左子节点，1表示left为前驱线索
    int rightFlag; // 用于表示是否是线索，0表示right为右子节点，1表示right为后继线索

  public:
    Node() {
        left = nullptr;
        right = nullptr;
        leftFlag = 0;
        rightFlag = 0;
    };
    Node(const elemType &e, Node<elemType> *l = nullptr, Node<elemType> *r = nullptr) {
        data = e;
        left = l;
        right = r;
    }
};

template <class elemType> class BTree {
  private:
    int size(Node<elemType> *t);       // 求以t为根的二叉树的结点个数
    int height(Node<elemType> *t);     // 求以t为根的二叉树的高度
    void delTree(Node<elemType> *t);   // 删除以t为根的二叉树
    void preOrder(Node<elemType> *t);  // 前序遍历以t为根的二叉树
    void inOrder(Node<elemType> *t);   // 中序遍历以t为根的二叉树
    void postOrder(Node<elemType> *t); // 后序遍历以t为根的二叉树

  protected:
    Node<elemType> *root;

  public:
    BTree() { root = nullptr; }
    void createTree(const elemType &flag);       // 创建一棵二叉树
    int isEmpty() { return (root == nullptr); }; // 判断二叉树是否为空
    Node<elemType> *getRoot() { return root; }   // 返回根节点

    int size();        // 求二叉树的结点个数
    int height();      // 求二叉树的高度
    void delTree();    // 删除二叉树
    void preOrder();   // 前序遍历二叉树
    void inOrder();    // 中序遍历二叉树
    void postOrder();  // 后序遍历二叉树
    void levelOrder(); // 层次遍历二叉树

    // 获取指定节点的 data
    elemType getData(Node<elemType> *node) { return node->data; }

    // 获取指定节点的左子节点
    Node<elemType> *getLeft(Node<elemType> *node) { return node->left; }

    // 获取指定节点的右子节点
    Node<elemType> *getRight(Node<elemType> *node) { return node->right; }
};

template <class elemType> void BTree<elemType>::createTree(const elemType &flag) {
    SeqQueue<Node<elemType> *> nodeQueue;             // 用队列来实现层次遍历
    elemType nodeData, leftChildData, rightChildData; // 当前节点和左右子节点的值
    Node<elemType> *currentNode, *leftChildNode, *rightChildNode;

    std::cout << "请输入根节点的值：";
    std::cin >> nodeData;

    // 如果根节点的值等于 flag，表示树为空
    if (nodeData == flag) {
        root = nullptr;
        return;
    }

    // 创建根节点，并将其加入队列
    currentNode = new Node<elemType>(nodeData);
    root = currentNode;
    nodeQueue.enQueue(currentNode);

    // 开始按层次遍历构建树
    while (!nodeQueue.isEmpty()) {
        currentNode = nodeQueue.front(); // 获取当前节点
        nodeQueue.deQueue();             // 弹出队列中的当前节点

        std::cout << "请输入 " << currentNode->data << " 的左孩子和右孩子，"
                  << "用 " << flag << " 表示空节点：";
        std::cin >> leftChildData >> rightChildData;

        // 如果左子节点不为空，创建左子节点并加入队列
        if (leftChildData != flag) {
            leftChildNode = new Node<elemType>(leftChildData);
            currentNode->left = leftChildNode;
            nodeQueue.enQueue(leftChildNode); // 将左子节点加入队列
        }

        // 如果右子节点不为空，创建右子节点并加入队列
        if (rightChildData != flag) {
            rightChildNode = new Node<elemType>(rightChildData);
            currentNode->right = rightChildNode;
            nodeQueue.enQueue(rightChildNode); // 将右子节点加入队列
        }
    }
}

template <class elemType> int BTree<elemType>::size(Node<elemType> *t) {
    if (t == nullptr) {
        return 0;
    } else {
        return 1 + size(t->left) + size(t->right);
    }
}

template <class elemType> int BTree<elemType>::size() { return size(root); }

template <class elemType> int BTree<elemType>::height(Node<elemType> *t) {
    if (t == nullptr) {
        return 0;
    } else {
        int leftHeight = height(t->left);
        int rightHeight = height(t->right);
        return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
    }
}

template <class elemType> int BTree<elemType>::height() { return height(root); }

template <class elemType> void BTree<elemType>::delTree(Node<elemType> *t) {
    if (t != nullptr) {
        delTree(t->left);
        delTree(t->right);
        delete t;
    }
}

template <class elemType> void BTree<elemType>::delTree() {
    delTree(root);
    root = nullptr;
}

template <class elemType> void BTree<elemType>::preOrder() { preOrder(root); }

template <class elemType> void BTree<elemType>::preOrder(Node<elemType> *t) {
    if (t == nullptr) {
        return;
    }
    std ::cout << t->data << " ";
    preOrder(t->left);
    preOrder(t->right);
}

template <class elemType> void BTree<elemType>::inOrder() { inOrder(root); }

template <class elemType> void BTree<elemType>::inOrder(Node<elemType> *t) {
    if (t == nullptr) {
        return;
    }
    inOrder(t->left);
    std ::cout << t->data << " ";
    inOrder(t->right);
}

template <class elemType> void BTree<elemType>::postOrder() { postOrder(root); }

template <class elemType> void BTree<elemType>::postOrder(Node<elemType> *t) {
    if (t == nullptr) {
        return;
    }
    postOrder(t->left);
    postOrder(t->right);
    std ::cout << t->data << " ";
}

template <class elemType> void BTree<elemType>::levelOrder() {
    SeqQueue<Node<elemType> *> nodeQueue;
    Node<elemType> *currentNode;

    if (root == nullptr) {
        return;
    }

    nodeQueue.enQueue(root);
    while (!nodeQueue.isEmpty()) {
        currentNode = nodeQueue.front();
        nodeQueue.deQueue();
        std::cout << currentNode->data << " ";

        if (currentNode->left != nullptr) {
            nodeQueue.enQueue(currentNode->left);
        }
        if (currentNode->right != nullptr) {
            nodeQueue.enQueue(currentNode->right);
        }
    }
}

} // namespace datastructures

#endif // BINARY_TREE_H
