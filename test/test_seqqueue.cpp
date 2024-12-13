#include <gtest/gtest.h>

#include "SeqQueue.h"

// 测试队列的构造与初始化
TEST(SeqQueueTest, ConstructorTest)
{
    datastructures::SeqQueue<int> queue(5);
    EXPECT_TRUE(queue.isEmpty());
    EXPECT_FALSE(queue.isFull());
}

// 测试队列的入队操作
TEST(SeqQueueTest, EnQueueTest)
{
    datastructures::SeqQueue<int> queue(5);

    queue.enQueue(10);
    queue.enQueue(20);

    // 验证队列状态
    EXPECT_FALSE(queue.isEmpty());
    EXPECT_EQ(queue.front(), 10);  // 队列头部应为第一个入队的元素
}

// 测试队列的出队操作
TEST(SeqQueueTest, DeQueueTest)
{
    datastructures::SeqQueue<int> queue(5);

    queue.enQueue(10);
    queue.enQueue(20);

    // 移除队列头部元素
    queue.deQueue();

    // 验证队列状态
    EXPECT_EQ(queue.front(), 20);  // 队列头部应为下一个元素
    queue.deQueue();
    EXPECT_TRUE(queue.isEmpty());  // 队列应为空
}

// 测试队列的扩容功能
TEST(SeqQueueTest, DoubleSpaceTest)
{
    datastructures::SeqQueue<int> queue(2);

    queue.enQueue(10);
    queue.enQueue(20);

    // 触发扩容
    queue.enQueue(30);

    // 验证队列内容是否正确
    EXPECT_EQ(queue.front(), 10);  // 队列头部应保持不变
    queue.deQueue();
    EXPECT_EQ(queue.front(), 20);  // 队列头部应更新为第二个元素
}

// 测试队列为空时的异常处理
TEST(SeqQueueTest, EmptyQueueTest)
{
    datastructures::SeqQueue<int> queue;

    // 验证是否正确抛出异常
    EXPECT_TRUE(queue.isEmpty());
    EXPECT_THROW(queue.front(), OutOfBound);
    EXPECT_THROW(queue.deQueue(), OutOfBound);
}

// 测试队列已满时的状态
TEST(SeqQueueTest, FullQueueTest)
{
    // 值得注意的是，initSize为n，实际上只能存储n-1个元素，否则就会触发doubleSpace
    datastructures::SeqQueue<int> queue(4);

    queue.enQueue(10);
    queue.enQueue(20);
    queue.enQueue(30);

    // 验证队列已满状态
    EXPECT_TRUE(queue.isFull());
}

// 测试混合入队和出队的操作
TEST(SeqQueueTest, MixedOperationsTest)
{
    datastructures::SeqQueue<int> queue(3);

    queue.enQueue(10);
    queue.enQueue(20);
    queue.deQueue();
    queue.enQueue(30);
    queue.enQueue(40);

    // 队列头部应为20，后续顺序应为30, 40
    EXPECT_EQ(queue.front(), 20);
    queue.deQueue();
    EXPECT_EQ(queue.front(), 30);
    queue.deQueue();
    EXPECT_EQ(queue.front(), 40);
    queue.deQueue();
    EXPECT_TRUE(queue.isEmpty());
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}