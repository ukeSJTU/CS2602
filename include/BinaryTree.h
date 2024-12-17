#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <iostream>

#include "BaseNode.h"
#include "LinkQueue.h"
#include "SeqQueue.h"

namespace datastructures
{

// Forward declaration of TreeNode
template <class elemType>
class TreeNode;

// Forward declaration of BTree
template <class elemType, class nodeType>
class BTree;

/**
 * @brief 二叉树节点类
 * @tparam elemType 节点数据的类型
 */
template <class elemType>
class TreeNode : public BaseNode<elemType>
{
    friend class BTree<elemType, TreeNode<elemType>>;

   private:
    int leftFlag;   ///< 表示左指针类型，0表示左子节点，1表示前驱线索
    int rightFlag;  ///< 表示右指针类型，0表示右子节点，1表示后继线索

   public:
    using BaseNode<elemType>::left;
    using BaseNode<elemType>::right;
    using BaseNode<elemType>::data;

    /**
     * @brief 默认构造函数
     */
    TreeNode() : BaseNode<elemType>(elemType()), leftFlag(0), rightFlag(0) {}

    /**
     * @brief 带初值的构造函数
     */
    TreeNode(const elemType& e, TreeNode<elemType>* l = nullptr, TreeNode<elemType>* r = nullptr)
        : BaseNode<elemType>(e), leftFlag(0), rightFlag(0)
    {
        this->left = l;
        this->right = r;
    }
};

/**
 * @brief 二叉树类
 * @tparam elemType 节点数据的类型
 * @tparam nodeType 节点类型，默认为TreeNode<elemType>
 */
template <class elemType, class nodeType = TreeNode<elemType>>
class BTree
{
   private:
    int size(nodeType* t);
    int height(nodeType* t);
    void delTree(nodeType* t);
    void preOrder(nodeType* t, LinkQueue<elemType>* result = nullptr);
    void inOrder(nodeType* t, LinkQueue<elemType>* result = nullptr);
    void postOrder(nodeType* t, LinkQueue<elemType>* result = nullptr);

   protected:
    nodeType* root;  ///< 二叉树根节点指针

   public:
    BTree() : root(nullptr) {}

    BTree(LinkQueue<elemType>& dataQueue, const elemType& flag);
    BTree(SeqQueue<elemType>& dataQueue, const elemType& flag);

    virtual ~BTree() { delTree(); }

    void createTree(const elemType& flag);
    bool isEmpty() const { return root == nullptr; }
    nodeType* getRoot() const { return root; }
    int size() { return size(root); }
    int height() { return height(root); }
    void delTree()
    {
        delTree(root);
        root = nullptr;
    }

    /**
     * @brief 前序遍历二叉树
     * @param result 可选的LinkList指针，如果提供则将遍历结果存入链表而不是输出到控制台
     */
    void preOrder(LinkQueue<elemType>* result = nullptr) { preOrder(root, result); }

    /**
     * @brief 中序遍历二叉树
     * @param result 可选的LinkList指针，如果提供则将遍历结果存入链表而不是输出到控制台
     */
    void inOrder(LinkQueue<elemType>* result = nullptr) { inOrder(root, result); }

    /**
     * @brief 后序遍历二叉树
     * @param result 可选的LinkList指针，如果提供则将遍历结果存入链表而不是输出到控制台
     */
    void postOrder(LinkQueue<elemType>* result = nullptr) { postOrder(root, result); }

    /**
     * @brief 层次遍历二叉树
     * @param result 可选的LinkList指针，如果提供则将遍历结果存入链表而不是输出到控制台
     */
    void levelOrder(LinkQueue<elemType>* result = nullptr);

    elemType getData(nodeType* node) const { return node->data; }
    nodeType* getLeft(nodeType* node) const { return static_cast<nodeType*>(node->left); }
    nodeType* getRight(nodeType* node) const { return static_cast<nodeType*>(node->right); }
};

// Implementation of member functions

template <class elemType, class nodeType>
void BTree<elemType, nodeType>::createTree(const elemType& flag)
{
    SeqQueue<nodeType*> nodeQueue;
    elemType nodeData, leftChildData, rightChildData;
    nodeType *currentNode, *leftChildNode, *rightChildNode;

    std::cout << "请输入根节点的值：";
    std::cin >> nodeData;

    if (nodeData == flag) {
        root = nullptr;
        return;
    }

    currentNode = new nodeType(nodeData);
    root = currentNode;
    nodeQueue.enQueue(currentNode);

    while (!nodeQueue.isEmpty()) {
        currentNode = nodeQueue.front();
        nodeQueue.deQueue();

        std::cout << "请输入 " << currentNode->data << " 的左孩子和右孩子，"
                  << "用 " << flag << " 表示空节点：";
        std::cin >> leftChildData >> rightChildData;

        if (leftChildData != flag) {
            leftChildNode = new nodeType(leftChildData);
            currentNode->left = leftChildNode;
            nodeQueue.enQueue(leftChildNode);
        }

        if (rightChildData != flag) {
            rightChildNode = new nodeType(rightChildData);
            currentNode->right = rightChildNode;
            nodeQueue.enQueue(rightChildNode);
        }
    }
}

template <class elemType, class nodeType>
int BTree<elemType, nodeType>::size(nodeType* t)
{
    if (t == nullptr) return 0;
    return 1 + size(static_cast<nodeType*>(t->left)) + size(static_cast<nodeType*>(t->right));
}

template <class elemType, class nodeType>
int BTree<elemType, nodeType>::height(nodeType* t)
{
    if (t == nullptr) return 0;
    int leftHeight = height(static_cast<nodeType*>(t->left));
    int rightHeight = height(static_cast<nodeType*>(t->right));
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

template <class elemType, class nodeType>
void BTree<elemType, nodeType>::delTree(nodeType* t)
{
    if (t != nullptr) {
        delTree(static_cast<nodeType*>(t->left));
        delTree(static_cast<nodeType*>(t->right));
        delete t;
    }
}

template <class elemType, class nodeType>
void BTree<elemType, nodeType>::preOrder(nodeType* t, LinkQueue<elemType>* result)
{
    if (t == nullptr) return;
    if (result)
        result->enQueue(t->data);
    else
        std::cout << t->data << " ";
    preOrder(static_cast<nodeType*>(t->left), result);
    preOrder(static_cast<nodeType*>(t->right), result);
}

template <class elemType, class nodeType>
void BTree<elemType, nodeType>::inOrder(nodeType* t, LinkQueue<elemType>* result)
{
    if (t == nullptr) return;
    inOrder(static_cast<nodeType*>(t->left), result);
    if (result)
        result->enQueue(t->data);
    else
        std::cout << t->data << " ";
    inOrder(static_cast<nodeType*>(t->right), result);
}

template <class elemType, class nodeType>
void BTree<elemType, nodeType>::postOrder(nodeType* t, LinkQueue<elemType>* result)
{
    if (t == nullptr) return;
    postOrder(static_cast<nodeType*>(t->left), result);
    postOrder(static_cast<nodeType*>(t->right), result);
    if (result)
        result->enQueue(t->data);
    else
        std::cout << t->data << " ";
}

template <class elemType, class nodeType>
void BTree<elemType, nodeType>::levelOrder(LinkQueue<elemType>* result)
{
    if (root == nullptr) return;

    SeqQueue<nodeType*> nodeQueue;
    nodeQueue.enQueue(root);

    while (!nodeQueue.isEmpty()) {
        nodeType* currentNode = nodeQueue.front();
        nodeQueue.deQueue();

        if (result)
            result->enQueue(currentNode->data);
        else
            std::cout << currentNode->data << " ";

        if (currentNode->left) nodeQueue.enQueue(static_cast<nodeType*>(currentNode->left));
        if (currentNode->right) nodeQueue.enQueue(static_cast<nodeType*>(currentNode->right));
    }
}

template <class elemType, class nodeType>
BTree<elemType, nodeType>::BTree(LinkQueue<elemType>& dataQueue, const elemType& flag)
{
    if (dataQueue.isEmpty()) {
        root = nullptr;
        return;
    }

    LinkQueue<nodeType*> nodeQueue;
    elemType nodeData = dataQueue.front();
    dataQueue.deQueue();

    if (nodeData == flag) {
        root = nullptr;
        return;
    }

    root = new nodeType(nodeData);
    nodeQueue.enQueue(root);

    while (!dataQueue.isEmpty()) {
        nodeType* currentNode = nodeQueue.front();
        nodeQueue.deQueue();

        if (!dataQueue.isEmpty()) {
            elemType leftData = dataQueue.front();
            dataQueue.deQueue();

            if (leftData != flag) {
                currentNode->left = new nodeType(leftData);
                nodeQueue.enQueue(static_cast<nodeType*>(currentNode->left));
            }
        }

        if (!dataQueue.isEmpty()) {
            elemType rightData = dataQueue.front();
            dataQueue.deQueue();

            if (rightData != flag) {
                currentNode->right = new nodeType(rightData);
                nodeQueue.enQueue(static_cast<nodeType*>(currentNode->right));
            }
        }
    }
}

template <class elemType, class nodeType>
BTree<elemType, nodeType>::BTree(SeqQueue<elemType>& dataQueue, const elemType& flag)
{
    if (dataQueue.isEmpty()) {
        root = nullptr;
        return;
    }

    SeqQueue<nodeType*> nodeQueue;
    elemType nodeData = dataQueue.front();
    dataQueue.deQueue();

    if (nodeData == flag) {
        root = nullptr;
        return;
    }

    root = new nodeType(nodeData);
    nodeQueue.enQueue(root);

    while (!dataQueue.isEmpty()) {
        nodeType* currentNode = nodeQueue.front();
        nodeQueue.deQueue();

        if (!dataQueue.isEmpty()) {
            elemType leftData = dataQueue.front();
            dataQueue.deQueue();

            if (leftData != flag) {
                currentNode->left = new nodeType(leftData);
                nodeQueue.enQueue(static_cast<nodeType*>(currentNode->left));
            }
        }

        if (!dataQueue.isEmpty()) {
            elemType rightData = dataQueue.front();
            dataQueue.deQueue();

            if (rightData != flag) {
                currentNode->right = new nodeType(rightData);
                nodeQueue.enQueue(static_cast<nodeType*>(currentNode->right));
            }
        }
    }
}

}  // namespace datastructures

#endif  // BINARY_TREE_H
