#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <cstddef>
#include <iostream>

#include "SeqQueue.h"
#include "SeqStack.h"

namespace datastructures
{

// BTree 类的前向声明
template <class elemType>
class BTree;

/**
 * @brief 二叉树节点类
 *
 * @tparam elemType 节点数据的类型
 */
template <class elemType>
class Node
{
    friend class BTree<elemType>;

   private:
    elemType data;                 ///< 节点数据
    Node<elemType> *left, *right;  ///< 左右子节点指针
    int leftFlag;                  ///< 表示左指针类型，0表示左子节点，1表示前驱线索
    int rightFlag;                 ///< 表示右指针类型，0表示右子节点，1表示后继线索

   public:
    /**
     * @brief 默认构造函数
     */
    Node()
    {
        left = nullptr;
        right = nullptr;
        leftFlag = 0;
        rightFlag = 0;
    }

    /**
     * @brief 带初值的构造函数
     *
     * @param e 节点数据
     * @param l 左子节点指针，默认为空
     * @param r 右子节点指针，默认为空
     */
    Node(const elemType &e, Node<elemType> *l = nullptr, Node<elemType> *r = nullptr)
    {
        data = e;
        left = l;
        right = r;
    }
};

/**
 * @brief 二叉树类
 *
 * @tparam elemType 节点数据的类型
 */
template <class elemType>
class BTree
{
   private:
    /**
     * @brief 求以t为根的二叉树的节点个数
     *
     * @param t 二叉树根节点
     * @return int 节点个数
     */
    int size(Node<elemType> *t);

    /**
     * @brief 求以t为根的二叉树的高度
     *
     * @param t 二叉树根节点
     * @return int 树的高度
     */
    int height(Node<elemType> *t);

    /**
     * @brief 删除以t为根的二叉树
     *
     * @param t 二叉树根节点
     */
    void delTree(Node<elemType> *t);

    /**
     * @brief 前序遍历以t为根的二叉树
     *
     * @param t 二叉树根节点
     */
    void preOrder(Node<elemType> *t);

    /**
     * @brief 中序遍历以t为根的二叉树
     *
     * @param t 二叉树根节点
     */
    void inOrder(Node<elemType> *t);

    /**
     * @brief 后序遍历以t为根的二叉树
     *
     * @param t 二叉树根节点
     */
    void postOrder(Node<elemType> *t);

   protected:
    Node<elemType> *root;  ///< 二叉树根节点指针

   public:
    /**
     * @brief 默认构造函数
     */
    BTree() { root = nullptr; }

    /**
     * @brief 创建一棵二叉树
     *
     * @param flag 用于标记空节点的特殊值
     */
    void createTree(const elemType &flag);

    /**
     * @brief 判断二叉树是否为空
     *
     * @return int 返回1表示为空，0表示不为空
     */
    int isEmpty() { return (root == nullptr); }

    /**
     * @brief 获取二叉树的根节点
     *
     * @return Node<elemType>* 根节点指针
     */
    Node<elemType> *getRoot() { return root; }

    /**
     * @brief 求二叉树的节点个数
     *
     * @return int 节点个数
     */
    int size();

    /**
     * @brief 求二叉树的高度
     *
     * @return int 树的高度
     */
    int height();

    /**
     * @brief 删除二叉树
     */
    void delTree();

    /**
     * @brief 前序遍历二叉树
     */
    void preOrder();

    /**
     * @brief 中序遍历二叉树
     */
    void inOrder();

    /**
     * @brief 后序遍历二叉树
     */
    void postOrder();

    /**
     * @brief 层次遍历二叉树
     */
    void levelOrder();

    /**
     * @brief 获取指定节点的数据
     *
     * @param node 节点指针
     * @return elemType 节点数据
     */
    elemType getData(Node<elemType> *node) { return node->data; }

    /**
     * @brief 获取指定节点的左子节点
     *
     * @param node 节点指针
     * @return Node<elemType>* 左子节点指针
     */
    Node<elemType> *getLeft(Node<elemType> *node) { return node->left; }

    /**
     * @brief 获取指定节点的右子节点
     *
     * @param node 节点指针
     * @return Node<elemType>* 右子节点指针
     */
    Node<elemType> *getRight(Node<elemType> *node) { return node->right; }
};

template <class elemType>
void BTree<elemType>::createTree(const elemType &flag)
{
    SeqQueue<Node<elemType> *> nodeQueue;              // 用队列来实现层次遍历
    elemType nodeData, leftChildData, rightChildData;  // 当前节点和左右子节点的值
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
        currentNode = nodeQueue.front();  // 获取当前节点
        nodeQueue.deQueue();              // 弹出队列中的当前节点

        std::cout << "请输入 " << currentNode->data << " 的左孩子和右孩子，"
                  << "用 " << flag << " 表示空节点：";
        std::cin >> leftChildData >> rightChildData;

        // 如果左子节点不为空，创建左子节点并加入队列
        if (leftChildData != flag) {
            leftChildNode = new Node<elemType>(leftChildData);
            currentNode->left = leftChildNode;
            nodeQueue.enQueue(leftChildNode);  // 将左子节点加入队列
        }

        // 如果右子节点不为空，创建右子节点并加入队列
        if (rightChildData != flag) {
            rightChildNode = new Node<elemType>(rightChildData);
            currentNode->right = rightChildNode;
            nodeQueue.enQueue(rightChildNode);  // 将右子节点加入队列
        }
    }
}

template <class elemType>
int BTree<elemType>::size(Node<elemType> *t)
{
    if (t == nullptr) {
        return 0;
    } else {
        return 1 + size(t->left) + size(t->right);
    }
}

template <class elemType>
int BTree<elemType>::size()
{
    return size(root);
}

template <class elemType>
int BTree<elemType>::height(Node<elemType> *t)
{
    if (t == nullptr) {
        return 0;
    } else {
        int leftHeight = height(t->left);
        int rightHeight = height(t->right);
        return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
    }
}

template <class elemType>
int BTree<elemType>::height()
{
    return height(root);
}

template <class elemType>
void BTree<elemType>::delTree(Node<elemType> *t)
{
    if (t != nullptr) {
        delTree(t->left);
        delTree(t->right);
        delete t;
    }
}

template <class elemType>
void BTree<elemType>::delTree()
{
    delTree(root);
    root = nullptr;
}

template <class elemType>
void BTree<elemType>::preOrder()
{
    preOrder(root);
}

template <class elemType>
void BTree<elemType>::preOrder(Node<elemType> *t)
{
    if (t == nullptr) {
        return;
    }
    std ::cout << t->data << " ";
    preOrder(t->left);
    preOrder(t->right);
}

template <class elemType>
void BTree<elemType>::inOrder()
{
    inOrder(root);
}

template <class elemType>
void BTree<elemType>::inOrder(Node<elemType> *t)
{
    if (t == nullptr) {
        return;
    }
    inOrder(t->left);
    std ::cout << t->data << " ";
    inOrder(t->right);
}

template <class elemType>
void BTree<elemType>::postOrder()
{
    postOrder(root);
}

template <class elemType>
void BTree<elemType>::postOrder(Node<elemType> *t)
{
    if (t == nullptr) {
        return;
    }
    postOrder(t->left);
    postOrder(t->right);
    std ::cout << t->data << " ";
}

template <class elemType>
void BTree<elemType>::levelOrder()
{
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

}  // namespace datastructures

#endif  // BINARY_TREE_H
