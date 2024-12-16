#include <gtest/gtest.h>

#include "BinaryTree.h"
#include "LinkQueue.h"

using namespace datastructures;

TEST(BTreeTest, CreateTreeTest)
{
    BTree<int> tree;

    // 模拟输入
    std::stringstream input("1 2 3 -1 -1 4 5 -1 -1 -1 -1");
    std::cin.rdbuf(input.rdbuf());

    tree.createTree(-1);

    // 验证层次遍历结果
    testing::internal::CaptureStdout();
    tree.levelOrder();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "1 2 3 4 5 ");
}

TEST(BTreeTest, SizeTest)
{
    BTree<int> tree;

    // 创建二叉树
    std::stringstream input("1 2 3 -1 -1 4 5 -1 -1 -1 -1");
    std::cin.rdbuf(input.rdbuf());
    tree.createTree(-1);

    EXPECT_EQ(tree.size(), 5);  // 二叉树的节点个数应该是 5
}

TEST(BTreeTest, HeightTest)
{
    BTree<int> tree;

    // 创建二叉树
    std::stringstream input("1 2 3 -1 -1 4 5 -1 -1 -1 -1");
    std::cin.rdbuf(input.rdbuf());
    tree.createTree(-1);

    EXPECT_EQ(tree.height(), 3);  // 二叉树的高度应该是 3
}

TEST(BTreeTest, PreOrderTest)
{
    BTree<int> tree;

    // 创建二叉树
    std::stringstream input("1 2 3 -1 -1 4 5 -1 -1 -1 -1");
    std::cin.rdbuf(input.rdbuf());
    tree.createTree(-1);

    // 验证前序遍历结果
    testing::internal::CaptureStdout();
    tree.preOrder();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "1 2 3 4 5 ");
}

TEST(BTreeTest, InOrderTest)
{
    BTree<int> tree;

    // 创建二叉树
    std::stringstream input("1 2 3 -1 -1 4 5 -1 -1 -1 -1");
    std::cin.rdbuf(input.rdbuf());
    tree.createTree(-1);

    // 验证中序遍历结果
    testing::internal::CaptureStdout();
    tree.inOrder();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "2 1 4 3 5 ");
}

TEST(BTreeTest, PostOrderTest)
{
    BTree<int> tree;

    // 创建二叉树
    std::stringstream input("1 2 3 -1 -1 4 5 -1 -1 -1 -1");
    std::cin.rdbuf(input.rdbuf());
    tree.createTree(-1);

    // 验证后序遍历结果
    testing::internal::CaptureStdout();
    tree.postOrder();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "2 4 5 3 1 ");
}

TEST(BTreeTest, LevelOrderTest)
{
    BTree<int> tree;

    // 创建二叉树
    std::stringstream input("1 2 3 -1 -1 4 5 -1 -1 -1 -1");
    std::cin.rdbuf(input.rdbuf());
    tree.createTree(-1);

    // 验证层次遍历结果
    testing::internal::CaptureStdout();
    tree.levelOrder();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "1 2 3 4 5 ");
}

TEST(BTreeTest, ClearTest)
{
    BTree<int> tree;

    // 创建二叉树
    std::stringstream input("1 2 3 -1 -1 4 5 -1 -1 -1 -1");
    std::cin.rdbuf(input.rdbuf());
    tree.createTree(-1);

    tree.delTree();  // 清空二叉树

    EXPECT_TRUE(tree.isEmpty());  // 验证二叉树是否为空
    EXPECT_EQ(tree.size(), 0);    // 节点个数应该为 0
    EXPECT_EQ(tree.height(), 0);  // 高度应该为 0
}

TEST(BTreeTest, InitializationFromLinkQueueTest)
{
    LinkQueue<int> dataQueue;

    // 构造队列数据
    dataQueue.enQueue(1);
    dataQueue.enQueue(2);
    dataQueue.enQueue(3);
    dataQueue.enQueue(-1);
    dataQueue.enQueue(-1);
    dataQueue.enQueue(4);
    dataQueue.enQueue(5);

    BTree<int> tree(dataQueue, -1);  // 使用 LinkQueue 初始化二叉树

    // 验证层次遍历结果
    testing::internal::CaptureStdout();
    tree.levelOrder();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "1 2 3 4 5 ");
}

TEST(BTreeTest, InitializationFromSeqQueueTest)
{
    SeqQueue<int> dataQueue;

    // 构造队列数据
    dataQueue.enQueue(1);
    dataQueue.enQueue(2);
    dataQueue.enQueue(3);
    dataQueue.enQueue(-1);
    dataQueue.enQueue(-1);
    dataQueue.enQueue(4);
    dataQueue.enQueue(5);

    BTree<int> tree(dataQueue, -1);  // 使用 SeqQueue 初始化二叉树

    // 验证层次遍历结果
    testing::internal::CaptureStdout();
    tree.levelOrder();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "1 2 3 4 5 ");
}

TEST(BTreeTest, EmptyTreeTest)
{
    BTree<int> tree;

    // 创建空树
    std::stringstream input("-1");
    std::cin.rdbuf(input.rdbuf());
    tree.createTree(-1);

    EXPECT_TRUE(tree.isEmpty());  // 验证二叉树为空
    EXPECT_EQ(tree.size(), 0);    // 节点个数为 0
    EXPECT_EQ(tree.height(), 0);  // 高度为 0
}