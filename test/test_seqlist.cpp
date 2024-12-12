#include <gtest/gtest.h>

#include "SeqList.h"

// 使用 Google Test 的宏定义一个测试案例
TEST(SeqListTest, InsertTest)
{
    datastructures::SeqList<int> list;

    // 插入元素
    list.insert(1, 10);
    list.insert(2, 20);

    // 验证插入后的元素
    EXPECT_EQ(list.get(1), 10);
    EXPECT_EQ(list.get(2), 20);
}

TEST(SeqListTest, RemoveTest)
{
    datastructures::SeqList<int> list;

    // 插入元素
    list.insert(1, 10);
    list.insert(2, 20);

    int removedElement;
    list.remove(1, removedElement);

    // 验证删除后的情况
    EXPECT_EQ(removedElement, 10);
    EXPECT_EQ(list.get(1), 20);
}

TEST(SeqListTest, FindTest)
{
    datastructures::SeqList<int> list;

    list.insert(1, 10);
    list.insert(2, 20);

    // 验证查找功能
    EXPECT_EQ(list.find(10), 1);
    EXPECT_EQ(list.find(20), 2);
    EXPECT_EQ(list.find(30), 0);  // 未找到返回0
}

TEST(SeqListTest, OutOfBoundsTest)
{
    datastructures::SeqList<int> list;

    // 插入一个元素
    list.insert(1, 10);

    // 测试越界访问
    EXPECT_THROW(list.get(2), OutOfBound);  // 应该抛出异常
}
