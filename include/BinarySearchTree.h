#ifndef BINARYSEARCHTREE_H_INCLUDED
#define BINARYSEARCHTREE_H_INCLUDED

#include "BinaryTree.h"

namespace datastructures
{

/**
 * @brief 二叉搜索树的节点类
 * @tparam elemType 数据类型
 */
template <class elemType>
class BSTNode : public BaseNode<elemType>
{
   public:
    using BaseNode<elemType>::left;
    using BaseNode<elemType>::right;
    using BaseNode<elemType>::data;

    int factor;  ///< 平衡因子

    /**
     * @brief 构造函数
     * @param data 节点数据
     */
    BSTNode(const elemType& d) : BaseNode<elemType>(d), factor(0) {}
};

/**
 * @brief 二叉搜索树类
 * @tparam elemType 数据类型
 */
template <class elemType>
class BinarySearchTree : public BTree<elemType, BSTNode<elemType>>
{
   private:
    using NodeType = BSTNode<elemType>;
    using BTree<elemType, NodeType>::root;

    /**
     * @brief 搜索私有方法
     * @param x 待查找的数据
     * @param t 当前节点
     * @return bool 是否找到目标数据
     */
    bool search(const elemType& x, NodeType* t) const;

    /**
     * @brief 插入私有方法
     * @param x 插入的数据
     * @param t 当前节点的引用
     */
    void insert(const elemType& x, NodeType*& t);

    /**
     * @brief 删除私有方法
     * @param x 删除的数据
     * @param t 当前节点的引用
     */
    void remove(const elemType& x, NodeType*& t);

   public:
    /**
     * @brief 构造函数
     */
    BinarySearchTree() : BTree<elemType, NodeType>() {}

    /**
     * @brief 查找目标数据
     * @param x 待查找的数据
     * @return bool 是否找到目标数据
     */
    bool search(const elemType& x) const { return search(x, root); }

    /**
     * @brief 插入数据
     * @param x 插入的数据
     */
    void insert(const elemType& x) { insert(x, root); }

    /**
     * @brief 删除数据
     * @param x 删除的数据
     */
    void remove(const elemType& x) { remove(x, root); }

    /**
     * @brief 层次遍历二叉搜索树
     */
    void levelTraverse() const { this->levelOrder(); }
};

template <class elemType>
bool BinarySearchTree<elemType>::search(const elemType& x, NodeType* t) const
{
    if (!t) return false;
    if (x == t->data) return true;
    return x < t->data ? search(x, static_cast<NodeType*>(t->left))
                       : search(x, static_cast<NodeType*>(t->right));
}

template <class elemType>
void BinarySearchTree<elemType>::insert(const elemType& x, NodeType*& t)
{
    if (!t) {
        t = new NodeType(x);
        return;
    }
    if (x == t->data) return;  // 已存在
    if (x < t->data)
        insert(x, reinterpret_cast<NodeType*&>(t->left));
    else
        insert(x, reinterpret_cast<NodeType*&>(t->right));
}

template <class elemType>
void BinarySearchTree<elemType>::remove(const elemType& x, NodeType*& t)
{
    if (!t) return;

    if (x < t->data)
        remove(x, reinterpret_cast<NodeType*&>(t->left));
    else if (x > t->data)
        remove(x, reinterpret_cast<NodeType*&>(t->right));
    else {
        // 找到目标节点
        if (!t->left || !t->right) {  // 单子节点或叶节点
            NodeType* oldNode = t;
            t = static_cast<NodeType*>(t->left ? t->left : t->right);
            delete oldNode;
        } else {
            // 两个子节点：找到左子树中最大的节点
            NodeType* maxLeft = static_cast<NodeType*>(t->left);
            while (maxLeft->right) maxLeft = static_cast<NodeType*>(maxLeft->right);

            t->data = maxLeft->data;
            remove(maxLeft->data, reinterpret_cast<NodeType*&>(t->left));
        }
    }
}

}  // namespace datastructures

#endif  // BINARYSEARCHTREE_H_INCLUDED
