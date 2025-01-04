#include <gtest/gtest.h>

#include "AVLTree.h"

using namespace datastructures;

class AVLTreeTest : public ::testing::Test
{
   protected:
    AvlTree<int> avl;

    void SetUp() override
    {
        // Create a balanced AVL tree:
        //       4
        //     /   \
        //    2     6
        //   / \   / \
        //  1   3 5   7
        avl.insertValue(4);
        avl.insertValue(2);
        avl.insertValue(6);
        avl.insertValue(1);
        avl.insertValue(3);
        avl.insertValue(5);
        avl.insertValue(7);
    }
};

TEST_F(AVLTreeTest, Construction)
{
    EXPECT_FALSE(avl.isEmpty());
    EXPECT_EQ(avl.size(), 7);
    EXPECT_EQ(avl.height(), 3);
}

TEST_F(AVLTreeTest, Search)
{
    // Test existing values
    EXPECT_TRUE(avl.searchValue(4));  // root
    EXPECT_TRUE(avl.searchValue(1));  // leaf
    EXPECT_TRUE(avl.searchValue(6));  // internal node

    // Test non-existing values
    EXPECT_FALSE(avl.searchValue(0));
    EXPECT_FALSE(avl.searchValue(8));
    EXPECT_FALSE(avl.searchValue(-1));
}

TEST_F(AVLTreeTest, InsertAndBalance)
{
    avl.insertValue(0);  // Should not trigger rotation
    EXPECT_TRUE(avl.searchValue(0));
    EXPECT_EQ(avl.height(), 4);  // Height should increase by 1

    // Test LL rotation
    avl.insertValue(-1);
    EXPECT_TRUE(avl.searchValue(-1));
    EXPECT_EQ(avl.height(), 4);

    // Test RR rotation
    avl.insertValue(8);
    avl.insertValue(9);  // Should trigger rotation
    EXPECT_TRUE(avl.searchValue(9));
    EXPECT_EQ(avl.height(), 4);

    // Test LR rotation
    AvlTree<int> lrTree;
    lrTree.insertValue(3);
    lrTree.insertValue(1);
    lrTree.insertValue(2);  // Should trigger LR rotation
    EXPECT_EQ(lrTree.height(), 2);

    // Test RL rotation
    AvlTree<int> rlTree;
    rlTree.insertValue(3);
    rlTree.insertValue(5);
    rlTree.insertValue(4);  // Should trigger RL rotation
    EXPECT_EQ(rlTree.height(), 2);

    // Verify tree structure through traversal
    LinkQueue<int> result;
    avl.inOrder(&result);

    int expected[] = {-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (int i = 0; i < 11; i++) {
        EXPECT_EQ(result.front(), expected[i]);
        result.deQueue();
    }
    EXPECT_TRUE(result.isEmpty());
}

TEST_F(AVLTreeTest, RemoveAndBalance)
{
    // Remove leaf node
    avl.removeValue(1);
    EXPECT_FALSE(avl.searchValue(1));
    EXPECT_EQ(avl.size(), 6);

    // Remove node with one child
    avl.removeValue(6);
    EXPECT_FALSE(avl.searchValue(6));
    EXPECT_EQ(avl.size(), 5);
    EXPECT_TRUE(avl.searchValue(7));  // Child should still exist

    // Remove node with two children
    avl.removeValue(2);
    EXPECT_FALSE(avl.searchValue(2));
    EXPECT_EQ(avl.size(), 4);
    EXPECT_TRUE(avl.searchValue(3));  // Children should still exist

    // Remove root
    avl.removeValue(4);
    EXPECT_FALSE(avl.searchValue(4));
    EXPECT_EQ(avl.size(), 3);

    // Verify final tree structure and balance
    EXPECT_LE(avl.height(), 2);  // Tree should remain balanced

    LinkQueue<int> result;
    avl.inOrder(&result);

    int expected[] = {3, 5, 7};
    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(result.front(), expected[i]);
        result.deQueue();
    }
    EXPECT_TRUE(result.isEmpty());
}

TEST_F(AVLTreeTest, EmptyTree)
{
    AvlTree<int> emptyAvl;
    EXPECT_TRUE(emptyAvl.isEmpty());
    EXPECT_EQ(emptyAvl.size(), 0);
    EXPECT_EQ(emptyAvl.height(), 0);
    EXPECT_FALSE(emptyAvl.searchValue(1));

    // Operations on empty tree
    emptyAvl.removeValue(1);  // Should not crash
    EXPECT_EQ(emptyAvl.size(), 0);

    // Insert into empty tree
    emptyAvl.insertValue(1);
    EXPECT_FALSE(emptyAvl.isEmpty());
    EXPECT_EQ(emptyAvl.size(), 1);
    EXPECT_TRUE(emptyAvl.searchValue(1));
}

TEST_F(AVLTreeTest, ComplexBalancing)
{
    // Create a more complex scenario that requires multiple rotations
    AvlTree<int> complexAvl;
    int values[] = {10, 20, 30, 40, 50, 25};

    for (int val : values) {
        complexAvl.insertValue(val);
        EXPECT_TRUE(complexAvl.searchValue(val));

        // Verify AVL property: height difference <= 1
        auto leftNode = static_cast<AvlTreeNode<int>*>(complexAvl.getLeft(complexAvl.getRoot()));
        auto rightNode = static_cast<AvlTreeNode<int>*>(complexAvl.getRight(complexAvl.getRoot()));
        int leftHeight = complexAvl.getNodeHeight(leftNode);
        int rightHeight = complexAvl.getNodeHeight(rightNode);

        EXPECT_LE(abs(leftHeight - rightHeight), 1);
    }

    // Remove elements and check balance
    for (int val : values) {
        complexAvl.removeValue(val);
        EXPECT_FALSE(complexAvl.searchValue(val));

        if (!complexAvl.isEmpty()) {
            auto leftNode =
                static_cast<AvlTreeNode<int>*>(complexAvl.getLeft(complexAvl.getRoot()));
            auto rightNode =
                static_cast<AvlTreeNode<int>*>(complexAvl.getRight(complexAvl.getRoot()));
            int leftHeight = complexAvl.getNodeHeight(leftNode);
            int rightHeight = complexAvl.getNodeHeight(rightNode);

            EXPECT_LE(abs(leftHeight - rightHeight), 1);
        }
    }
}
