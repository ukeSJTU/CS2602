#include <gtest/gtest.h>

#include "LinkQueue.h"

// 测试队列的构造与初始化
TEST(LinkQueueTest, ConstructorTest)
{
    datastructures::LinkQueue<int> queue;
    EXPECT_TRUE(queue.isEmpty());
    EXPECT_FALSE(queue.isFull());
}

// 测试队列的入队操作
TEST(LinkQueueTest, EnQueueTest)
{
    datastructures::LinkQueue<int> queue;

    queue.enQueue(10);
    queue.enQueue(20);

    // 验证队列状态
    EXPECT_FALSE(queue.isEmpty());
    EXPECT_EQ(queue.front(), 10);  // 队列头部应为第一个入队的元素
}

// 测试队列的出队操作
TEST(LinkQueueTest, DeQueueTest)
{
    datastructures::LinkQueue<int> queue;

    queue.enQueue(10);
    queue.enQueue(20);

    queue.deQueue();

    // 验证队列状态
    EXPECT_EQ(queue.front(), 20);  // 队列头部应为下一个元素
    queue.deQueue();
    EXPECT_TRUE(queue.isEmpty());  // 队列应为空
}

// 测试队列为空时的异常处理
TEST(LinkQueueTest, EmptyQueueTest)
{
    datastructures::LinkQueue<int> queue;

    // 验证空队列操作是否抛出异常
    EXPECT_TRUE(queue.isEmpty());
    EXPECT_THROW(queue.front(), OutOfBound);
    EXPECT_THROW(queue.deQueue(), OutOfBound);
}

// 测试混合入队和出队的操作
TEST(LinkQueueTest, MixedOperationsTest)
{
    datastructures::LinkQueue<int> queue;

    queue.enQueue(10);
    queue.enQueue(20);
    queue.deQueue();
    queue.enQueue(30);
    queue.enQueue(40);

    // 验证队列内容
    EXPECT_EQ(queue.front(), 20);  // 队列头部应为20
    queue.deQueue();
    EXPECT_EQ(queue.front(), 30);  // 队列头部应为30
    queue.deQueue();
    EXPECT_EQ(queue.front(), 40);  // 队列头部应为40
    queue.deQueue();
    EXPECT_TRUE(queue.isEmpty());  // 队列应为空
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}