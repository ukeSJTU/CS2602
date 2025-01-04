#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "BaseNode.h"
#include "BinaryTree.h"

namespace datastructures
{

/**
 * @class AvlTreeNode
 * @brief Node class for the AVL Tree, inherits from BaseNode.
 * @tparam elemType The type of the data stored in the node.
 */
template <class elemType>
class AvlTreeNode : public BaseNode<elemType, AvlTreeNode<elemType>>
{
   public:
    /**
     * @brief Default constructor.
     */
    AvlTreeNode()
        : BaseNode<elemType, AvlTreeNode<elemType>>(elemType(), nullptr, nullptr), height(1)
    {
    }

    /**
     * @brief Parameterized constructor.
     * @param value The data value.
     * @param leftChild Pointer to the left child.
     * @param rightChild Pointer to the right child.
     * @param h Initial height of this node.
     */
    AvlTreeNode(const elemType& value, AvlTreeNode<elemType>* leftChild = nullptr,
                AvlTreeNode<elemType>* rightChild = nullptr, int h = 1)
        : BaseNode<elemType, AvlTreeNode<elemType>>(value), height(h)
    {
        this->left = leftChild;
        this->right = rightChild;
    }

    /// Height of the subtree rooted at this node.
    int height;
};

/**
 * @class AvlTree
 * @brief AVL (self-balancing) Tree class, inherits from BTree and provides
 *        AVL-specific insert and remove operations.
 * @tparam elemType The type of the data stored in the tree.
 *
 * This class demonstrates how to extend a basic binary tree to an AVL tree
 * by overriding insertion and removal with rebalancing operations.
 */
template <class elemType>
class AvlTree : public BTree<elemType, AvlTreeNode<elemType>>
{
   public:
    /**
     * @brief Default constructor.
     */
    AvlTree() : BTree<elemType, AvlTreeNode<elemType>>() {}

    /**
     * @brief Destructor.
     */
    virtual ~AvlTree() {}

    /**
     * @brief Get the height of a subtree
     * @param node The root of the subtree
     * @return The height of the subtree, 0 if node is nullptr
     */
    int getNodeHeight(AvlTreeNode<elemType>* node) const
    {
        if (!node) return 0;
        return node->height;
    }

    /**
     * @brief Public interface to search for a value in the AVL tree.
     * @param value The value to search for.
     * @return True if found, false otherwise.
     */
    bool searchValue(const elemType& value) const
    {
        return searchNode(value, static_cast<AvlTreeNode<elemType>*>(this->root));
    }

    /**
     * @brief Public interface to insert a value into the AVL tree.
     * @param value The value to insert.
     */
    void insertValue(const elemType& value)
    {
        insertNode(value, static_cast<AvlTreeNode<elemType>*&>(this->root));
    }

    /**
     * @brief Public interface to remove a value from the AVL tree.
     * @param value The value to remove.
     */
    void removeValue(const elemType& value)
    {
        removeNode(value, static_cast<AvlTreeNode<elemType>*&>(this->root));
    }

   private:
    /**
     * @brief Searches for a value in the subtree rooted at @p node.
     * @param value The value to search for.
     * @param node The current subtree root.
     * @return True if found, false otherwise.
     */
    bool searchNode(const elemType& value, AvlTreeNode<elemType>* node) const
    {
        if (!node) return false;
        if (value == node->data)
            return true;
        else if (value < node->data)
            return searchNode(value, static_cast<AvlTreeNode<elemType>*>(node->left));
        else
            return searchNode(value, static_cast<AvlTreeNode<elemType>*>(node->right));
    }

    /**
     * @brief Inserts a value into the subtree rooted at @p node, rebalancing if necessary.
     * @param value The value to insert.
     * @param node The current subtree root (passed by reference so it can be updated).
     */
    void insertNode(const elemType& value, AvlTreeNode<elemType>*& node)
    {
        if (!node) {
            node = new AvlTreeNode<elemType>(value);
        } else if (value == node->data) {
            // Duplicate value, do nothing.
            return;
        } else if (value < node->data) {
            insertNode(value, static_cast<AvlTreeNode<elemType>*&>(node->left));
            // Check balance factor
            if (getHeight(static_cast<AvlTreeNode<elemType>*>(node->left)) -
                    getHeight(static_cast<AvlTreeNode<elemType>*>(node->right)) ==
                2) {
                if (value < static_cast<AvlTreeNode<elemType>*>(node->left)->data) {
                    rotateLeftLeft(node);
                } else {
                    rotateLeftRight(node);
                }
            }
        } else {
            insertNode(value, static_cast<AvlTreeNode<elemType>*&>(node->right));
            // Check balance factor
            if (getHeight(static_cast<AvlTreeNode<elemType>*>(node->right)) -
                    getHeight(static_cast<AvlTreeNode<elemType>*>(node->left)) ==
                2) {
                if (value > static_cast<AvlTreeNode<elemType>*>(node->right)->data) {
                    rotateRightRight(node);
                } else {
                    rotateRightLeft(node);
                }
            }
        }
        // Update height
        node->height = getMax(getHeight(static_cast<AvlTreeNode<elemType>*>(node->left)),
                              getHeight(static_cast<AvlTreeNode<elemType>*>(node->right))) +
                       1;
    }

    /**
     * @brief Removes a value from the subtree rooted at @p node, rebalancing if necessary.
     * @param value The value to remove.
     * @param node The current subtree root (passed by reference so it can be updated).
     */
    void removeNode(const elemType& value, AvlTreeNode<elemType>*& node)
    {
        if (!node)
            return;  // Not found
        else if (value < node->data) {
            // In left subtree
            removeNode(value, static_cast<AvlTreeNode<elemType>*&>(node->left));
            // Rebalance
            if (getHeight(static_cast<AvlTreeNode<elemType>*>(node->right)) -
                    getHeight(static_cast<AvlTreeNode<elemType>*>(node->left)) ==
                2) {
                AvlTreeNode<elemType>* rightChild =
                    static_cast<AvlTreeNode<elemType>*>(node->right);
                if (getHeight(static_cast<AvlTreeNode<elemType>*>(rightChild->right)) >
                    getHeight(static_cast<AvlTreeNode<elemType>*>(rightChild->left))) {
                    rotateRightRight(node);
                } else {
                    rotateRightLeft(node);
                }
            }
        } else if (value > node->data) {
            // In right subtree
            removeNode(value, static_cast<AvlTreeNode<elemType>*&>(node->right));
            // Rebalance
            if (getHeight(static_cast<AvlTreeNode<elemType>*>(node->left)) -
                    getHeight(static_cast<AvlTreeNode<elemType>*>(node->right)) ==
                2) {
                AvlTreeNode<elemType>* leftChild = static_cast<AvlTreeNode<elemType>*>(node->left);
                if (getHeight(static_cast<AvlTreeNode<elemType>*>(leftChild->left)) >
                    getHeight(static_cast<AvlTreeNode<elemType>*>(leftChild->right))) {
                    rotateLeftLeft(node);
                } else {
                    rotateLeftRight(node);
                }
            }
        } else {
            // Found the node to remove
            if (!node->left || !node->right) {
                // If it has at most one child
                AvlTreeNode<elemType>* tmpNode = node;
                node = (node->left) ? static_cast<AvlTreeNode<elemType>*>(node->left)
                                    : static_cast<AvlTreeNode<elemType>*>(node->right);
                delete tmpNode;
                return;
            } else {
                // Node has two children, find the inorder successor (min in right subtree)
                AvlTreeNode<elemType>* successor = static_cast<AvlTreeNode<elemType>*>(node->right);
                while (successor->left)
                    successor = static_cast<AvlTreeNode<elemType>*>(successor->left);
                // Replace current node's data with successor's data
                node->data = successor->data;
                // Remove successor's data from right subtree
                removeNode(successor->data, static_cast<AvlTreeNode<elemType>*&>(node->right));
            }
        }
        // If node is not null, update height
        if (node) {
            node->height = getMax(getHeight(static_cast<AvlTreeNode<elemType>*>(node->left)),
                                  getHeight(static_cast<AvlTreeNode<elemType>*>(node->right))) +
                           1;
        }
    }

    /**
     * @brief Returns the height of a node in the AVL tree.
     * @param node Pointer to the node.
     * @return The height of the node, 0 if node is @c nullptr.
     */
    int getHeight(AvlTreeNode<elemType>* node) const
    {
        if (!node) return 0;
        return node->height;
    }

    /**
     * @brief Returns the maximum of two integer values.
     * @param a First integer.
     * @param b Second integer.
     * @return The larger of @p a and @p b.
     */
    int getMax(int a, int b) const { return (a > b) ? a : b; }

    /**
     * @brief AVL LL rotation (Right rotation).
     * @param node Reference to the subtree root needing rotation.
     */
    void rotateLeftLeft(AvlTreeNode<elemType>*& node)
    {
        AvlTreeNode<elemType>* newRoot = static_cast<AvlTreeNode<elemType>*>(node->left);
        node->left = newRoot->right;
        newRoot->right = node;
        node->height = getMax(getHeight(static_cast<AvlTreeNode<elemType>*>(node->left)),
                              getHeight(static_cast<AvlTreeNode<elemType>*>(node->right))) +
                       1;
        newRoot->height =
            getMax(getHeight(static_cast<AvlTreeNode<elemType>*>(newRoot->left)), node->height) + 1;
        node = newRoot;
    }

    /**
     * @brief AVL RR rotation (Left rotation).
     * @param node Reference to the subtree root needing rotation.
     */
    void rotateRightRight(AvlTreeNode<elemType>*& node)
    {
        AvlTreeNode<elemType>* newRoot = static_cast<AvlTreeNode<elemType>*>(node->right);
        node->right = newRoot->left;
        newRoot->left = node;
        node->height = getMax(getHeight(static_cast<AvlTreeNode<elemType>*>(node->left)),
                              getHeight(static_cast<AvlTreeNode<elemType>*>(node->right))) +
                       1;
        newRoot->height =
            getMax(getHeight(static_cast<AvlTreeNode<elemType>*>(newRoot->right)), node->height) +
            1;
        node = newRoot;
    }

    /**
     * @brief AVL LR rotation (Double rotation: Right rotation on left child, then Left rotation).
     * @param node Reference to the subtree root needing rotation.
     */
    void rotateLeftRight(AvlTreeNode<elemType>*& node)
    {
        rotateRightRight(static_cast<AvlTreeNode<elemType>*&>(node->left));
        rotateLeftLeft(node);
    }

    /**
     * @brief AVL RL rotation (Double rotation: Left rotation on right child, then Right rotation).
     * @param node Reference to the subtree root needing rotation.
     */
    void rotateRightLeft(AvlTreeNode<elemType>*& node)
    {
        rotateLeftLeft(static_cast<AvlTreeNode<elemType>*&>(node->right));
        rotateRightRight(node);
    }
};

}  // namespace datastructures

#endif  // AVL_TREE_H
