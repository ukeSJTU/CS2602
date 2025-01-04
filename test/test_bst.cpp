#include <gtest/gtest.h>

#include "BinarySearchTree.h"

using namespace datastructures;

class BinarySearchTreeTest : public ::testing::Test
{
   protected:
    BinarySearchTree<int> bst;

    void SetUp() override
    {
        // Create a balanced BST:
        //       4
        //     /   \
        //    2     6
        //   / \   / \
        //  1   3 5   7
        bst.insert(4);
        bst.insert(2);
        bst.insert(6);
        bst.insert(1);
        bst.insert(3);
        bst.insert(5);
        bst.insert(7);
    }
};

TEST_F(BinarySearchTreeTest, Construction)
{
    EXPECT_FALSE(bst.isEmpty());
    EXPECT_EQ(bst.size(), 7);
    EXPECT_EQ(bst.height(), 3);
}

TEST_F(BinarySearchTreeTest, Search)
{
    // Test existing values
    EXPECT_TRUE(bst.search(4));  // root
    EXPECT_TRUE(bst.search(1));  // leaf
    EXPECT_TRUE(bst.search(6));  // internal node

    // Test non-existing values
    EXPECT_FALSE(bst.search(0));
    EXPECT_FALSE(bst.search(8));
    EXPECT_FALSE(bst.search(-1));
}

TEST_F(BinarySearchTreeTest, Insert)
{
    // Insert new values
    bst.insert(8);
    EXPECT_TRUE(bst.search(8));
    EXPECT_EQ(bst.size(), 8);

    // Insert duplicate value
    bst.insert(8);
    EXPECT_EQ(bst.size(), 8);  // Size shouldn't change

    // Verify the tree structure through traversal
    LinkQueue<int> result;
    bst.inOrder(&result);

    int expected[] = {1, 2, 3, 4, 5, 6, 7, 8};
    for (int i = 0; i < 8; i++) {
        EXPECT_EQ(result.front(), expected[i]);
        result.deQueue();
    }
    EXPECT_TRUE(result.isEmpty());
}

TEST_F(BinarySearchTreeTest, Remove)
{
    // Remove leaf node
    bst.remove(1);
    EXPECT_FALSE(bst.search(1));
    EXPECT_EQ(bst.size(), 6);

    // Remove node with one child
    bst.remove(6);
    EXPECT_FALSE(bst.search(6));
    EXPECT_EQ(bst.size(), 5);
    EXPECT_TRUE(bst.search(7));  // Child should still exist

    // Remove node with two children
    bst.remove(2);
    EXPECT_FALSE(bst.search(2));
    EXPECT_EQ(bst.size(), 4);
    EXPECT_TRUE(bst.search(3));  // Children should still exist

    // Remove root
    bst.remove(4);
    EXPECT_FALSE(bst.search(4));
    EXPECT_EQ(bst.size(), 3);

    // Verify final tree structure
    LinkQueue<int> result;
    bst.inOrder(&result);

    int expected[] = {3, 5, 7};
    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(result.front(), expected[i]);
        result.deQueue();
    }
    EXPECT_TRUE(result.isEmpty());
}

TEST_F(BinarySearchTreeTest, EmptyTree)
{
    BinarySearchTree<int> emptyBst;
    EXPECT_TRUE(emptyBst.isEmpty());
    EXPECT_EQ(emptyBst.size(), 0);
    EXPECT_EQ(emptyBst.height(), 0);
    EXPECT_FALSE(emptyBst.search(1));

    // Operations on empty tree
    emptyBst.remove(1);  // Should not crash
    EXPECT_EQ(emptyBst.size(), 0);

    // Insert into empty tree
    emptyBst.insert(1);
    EXPECT_FALSE(emptyBst.isEmpty());
    EXPECT_EQ(emptyBst.size(), 1);
    EXPECT_TRUE(emptyBst.search(1));
}

TEST_F(BinarySearchTreeTest, Traversal)
{
    LinkQueue<int> result;

    // Test inorder traversal (should be sorted)
    bst.inOrder(&result);
    int expected[] = {1, 2, 3, 4, 5, 6, 7};
    for (int i = 0; i < 7; i++) {
        EXPECT_EQ(result.front(), expected[i]);
        result.deQueue();
    }
    EXPECT_TRUE(result.isEmpty());

    // Test level order traversal
    bst.levelTraverse();  // This just tests that it doesn't crash
}
