#include <gtest/gtest.h>

#include "PriorityQueue.h"

using namespace datastructures;

TEST(PriorityQueueTest, EmptyQueue)
{
    PriorityQueue<int> pq;
    EXPECT_TRUE(pq.isEmpty());
    EXPECT_THROW(pq.front(), OutOfBound);
    EXPECT_THROW(pq.deQueue(), OutOfBound);
}

TEST(PriorityQueueTest, InsertAndRetrieve)
{
    PriorityQueue<int> pq;
    pq.enQueue(5);
    pq.enQueue(3);
    pq.enQueue(8);

    EXPECT_EQ(pq.front(), 3);
    pq.deQueue();
    EXPECT_EQ(pq.front(), 5);
}

TEST(PriorityQueueTest, BuildFromArray)
{
    int arr[] = {10, 20, 5, 6};
    PriorityQueue<int> pq(arr, 4);
    EXPECT_EQ(pq.front(), 5);
}

TEST(PriorityQueueTest, ResizeQueue)
{
    PriorityQueue<int> pq(2);
    pq.enQueue(10);
    pq.enQueue(20);
    pq.enQueue(5);
    EXPECT_EQ(pq.front(), 5);
}