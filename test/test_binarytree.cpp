#include <gtest/gtest.h>

#include "BinaryTree.h"

using namespace datastructures;

class BinaryTreeTest : public ::testing::Test
{
   protected:
    BTree<int> tree;
    LinkQueue<int> queue;

    void SetUp() override
    {
        // Setup a simple binary tree using queue
        queue.enQueue(1);  // root
        queue.enQueue(2);  // left child
        queue.enQueue(3);  // right child
        queue.enQueue(4);  // left child of 2
        queue.enQueue(0);  // right child of 2 (0 as flag)
        queue.enQueue(0);  // left child of 3 (0 as flag)
        queue.enQueue(5);  // right child of 3
        tree = BTree<int>(queue, 0);
    }
};

TEST_F(BinaryTreeTest, Construction)
{
    EXPECT_FALSE(tree.isEmpty());
    EXPECT_EQ(tree.size(), 5);
    EXPECT_EQ(tree.height(), 3);
}

TEST_F(BinaryTreeTest, Traversal)
{
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

TEST_F(BinaryTreeTest, EmptyTree)
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
