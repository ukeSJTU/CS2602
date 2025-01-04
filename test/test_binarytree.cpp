#include <gtest/gtest.h>

#include "BinaryTree.h"

using namespace datastructures;

TEST(BTreeTest, Construction)
{
    // 构造一个队列, 准备二叉树数据
    LinkQueue<int> queue;
    queue.enQueue(1);  // root
    queue.enQueue(2);  // left child
    queue.enQueue(3);  // right child
    queue.enQueue(4);  // left child of 2
    queue.enQueue(0);  // right child of 2 (0 as flag)
    queue.enQueue(0);  // left child of 3 (0 as flag)
    queue.enQueue(5);  // right child of 3

    BTree<int> tree(queue, 0);

    // 做断言
    EXPECT_FALSE(tree.isEmpty());
    EXPECT_EQ(tree.getRoot()->data, 1);
    EXPECT_EQ(tree.getRoot()->left->data, 2);
    EXPECT_EQ(tree.getRoot()->right->data, 3);
    EXPECT_EQ(tree.getRoot()->left->left->data, 4);
    EXPECT_EQ(tree.getRoot()->right->right->data, 5);

    EXPECT_EQ(tree.size(), 5);
    EXPECT_EQ(tree.height(), 3);
}

TEST(BTreeTest, Traversal)
{
    // 构造一个队列, 准备二叉树数据
    LinkQueue<int> queue;
    queue.enQueue(1);  // root
    queue.enQueue(2);  // left child
    queue.enQueue(3);  // right child
    queue.enQueue(4);  // left child of 2
    queue.enQueue(0);  // right child of 2 (0 as flag)
    queue.enQueue(0);  // left child of 3 (0 as flag)
    queue.enQueue(5);  // right child of 3

    BTree<int> tree(queue, 0);

    LinkQueue<int> result;

    // Test preorder traversal
    tree.preOrder(&result);
    EXPECT_EQ(result.front(), 1);
    result.deQueue();
    EXPECT_EQ(result.front(), 2);
    result.deQueue();
    EXPECT_EQ(result.front(), 4);
    result.deQueue();
    EXPECT_EQ(result.front(), 3);
    result.deQueue();
    EXPECT_EQ(result.front(), 5);
    result.deQueue();
    EXPECT_TRUE(result.isEmpty());

    // Test inorder traversal
    tree.inOrder(&result);
    EXPECT_EQ(result.front(), 4);
    result.deQueue();
    EXPECT_EQ(result.front(), 2);
    result.deQueue();
    EXPECT_EQ(result.front(), 1);
    result.deQueue();
    EXPECT_EQ(result.front(), 3);
    result.deQueue();
    EXPECT_EQ(result.front(), 5);
    result.deQueue();
    EXPECT_TRUE(result.isEmpty());

    // Test postorder traversal
    tree.postOrder(&result);
    EXPECT_EQ(result.front(), 4);
    result.deQueue();
    EXPECT_EQ(result.front(), 2);
    result.deQueue();
    EXPECT_EQ(result.front(), 5);
    result.deQueue();
    EXPECT_EQ(result.front(), 3);
    result.deQueue();
    EXPECT_EQ(result.front(), 1);
    result.deQueue();
    EXPECT_TRUE(result.isEmpty());

    // Test level order traversal
    tree.levelOrder(&result);
    EXPECT_EQ(result.front(), 1);
    result.deQueue();
    EXPECT_EQ(result.front(), 2);
    result.deQueue();
    EXPECT_EQ(result.front(), 3);
    result.deQueue();
    EXPECT_EQ(result.front(), 4);
    result.deQueue();
    EXPECT_EQ(result.front(), 5);
    result.deQueue();
    EXPECT_TRUE(result.isEmpty());
}

TEST(BTreeTest, EmptyTree)
{
    BTree<int> emptyTree;
    EXPECT_TRUE(emptyTree.isEmpty());
    EXPECT_EQ(emptyTree.size(), 0);
    EXPECT_EQ(emptyTree.height(), 0);

    LinkQueue<int> result;
    emptyTree.preOrder(&result);
    EXPECT_TRUE(result.isEmpty());
    emptyTree.inOrder(&result);
    EXPECT_TRUE(result.isEmpty());
    emptyTree.postOrder(&result);
    EXPECT_TRUE(result.isEmpty());
    emptyTree.levelOrder(&result);
    EXPECT_TRUE(result.isEmpty());
}
