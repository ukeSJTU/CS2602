#include <gtest/gtest.h>
#include "LinkList.h"

using namespace datastructures;

TEST(LinkListTest, InsertTest)
{
    LinkList<int> list;

    // 插入元素
    list.insert(0, 10); // 插入 10 到位置 0
    list.insert(1, 20); // 插入 20 到位置 1
    list.insert(2, 30); // 插入 30 到位置 2

    // 验证插入后的元素
    EXPECT_EQ(list.get(0), 10);
    EXPECT_EQ(list.get(1), 20);
    EXPECT_EQ(list.get(2), 30);
}

TEST(LinkListTest, RemoveTest)
{
    LinkList<int> list;

    // 插入元素
    list.insert(0, 10); // 插入 10 到位置 0
    list.insert(1, 20); // 插入 20 到位置 1

    int removedElement;
    list.remove(0, removedElement); // 删除位置 0 的元素

    // 验证删除后的情况
    EXPECT_EQ(removedElement, 10);
    EXPECT_EQ(list.get(0), 20); // 位置 0 应该是 20
}

TEST(LinkListTest, FindTest)
{
    LinkList<int> list;

    list.insert(0, 10); // 插入 10 到位置 0
    list.insert(1, 20); // 插入 20 到位置 1

    // 验证查找功能
    EXPECT_EQ(list.find(10), 0);  // 查找 10，应返回索引 0
    EXPECT_EQ(list.find(20), 1);  // 查找 20，应返回索引 1
    EXPECT_EQ(list.find(30), -1); // 查找 30，未找到，应返回 -1
}

TEST(LinkListTest, OutOfBoundsTest)
{
    LinkList<int> list;

    // 插入一个元素
    list.insert(0, 10);

    // 测试越界访问
    EXPECT_THROW(list.get(1), OutOfBound); // 应该抛出 OutOfBound 异常
}

TEST(LinkListTest, ReverseTest)
{
    LinkList<int> list;

    // 插入元素
    list.insert(0, 10); // 插入 10 到位置 0
    list.insert(1, 20); // 插入 20 到位置 1
    list.insert(2, 30); // 插入 30 到位置 2

    // 反转链表
    list.reverse();

    // 验证反转后的顺序
    EXPECT_EQ(list.get(0), 30); // 反转后，位置 0 应该是 30
    EXPECT_EQ(list.get(1), 20); // 反转后，位置 1 应该是 20
    EXPECT_EQ(list.get(2), 10); // 反转后，位置 2 应该是 10
}

TEST(LinkListTest, ClearTest)
{
    LinkList<int> list;

    // 插入元素
    list.insert(0, 10); // 插入 10 到位置 0
    list.insert(1, 20); // 插入 20 到位置 1

    // 清空链表
    list.clear();

    // 验证链表是否清空
    EXPECT_EQ(list.length(), 0); // 链表长度应该为 0
    EXPECT_TRUE(list.isEmpty()); // 链表应该为空
}
