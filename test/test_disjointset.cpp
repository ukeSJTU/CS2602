#include <gtest/gtest.h>

#include "DisjointSet.h"

using namespace datastructures;

// 测试构造函数和初始化
TEST(DisjointSetTest, Initialization)
{
    DisjointSet ds(5);

    // 检查每个元素是否初始化为独立集合
    for (int i = 1; i <= 5; ++i) {
        EXPECT_EQ(ds.find(i), i);  // 每个元素的根应该是自己
    }
}

// 测试 union_sets 操作
TEST(DisjointSetTest, UnionOperation)
{
    DisjointSet ds(5);

    // 合并 1 和 2
    ds.union_sets(1, 2);
    EXPECT_EQ(ds.find(1), ds.find(2));  // 1 和 2 应该在同一个集合中

    // 合并 3 和 4
    ds.union_sets(3, 4);
    EXPECT_EQ(ds.find(3), ds.find(4));  // 3 和 4 应该在同一个集合中

    // 合并 2 和 3
    ds.union_sets(2, 3);
    EXPECT_EQ(ds.find(1), ds.find(4));  // 1, 2, 3, 4 应该在同一个集合中
}

// 测试路径压缩
TEST(DisjointSetTest, PathCompression)
{
    DisjointSet ds(5);

    ds.union_sets(1, 2);
    ds.union_sets(2, 3);
    ds.union_sets(3, 4);

    // 检查路径压缩是否生效
    int root = ds.find(1);
    EXPECT_EQ(root, ds.find(2));
    EXPECT_EQ(root, ds.find(3));
    EXPECT_EQ(root, ds.find(4));
}

// 测试多次 union_sets 操作
TEST(DisjointSetTest, MultipleUnions)
{
    DisjointSet ds(10);

    ds.union_sets(1, 2);
    ds.union_sets(3, 4);
    ds.union_sets(5, 6);
    ds.union_sets(7, 8);
    ds.union_sets(2, 4);  // 合并 1-2 和 3-4
    ds.union_sets(6, 8);  // 合并 5-6 和 7-8

    EXPECT_EQ(ds.find(1), ds.find(3));
    EXPECT_EQ(ds.find(5), ds.find(7));
    EXPECT_NE(ds.find(1), ds.find(5));

    ds.union_sets(1, 5);  // 合并所有集合
    EXPECT_EQ(ds.find(1), ds.find(5));
}

// 测试边界条件
TEST(DisjointSetTest, BoundaryCondition)
{
    DisjointSet ds(1);         // 只有一个元素的集合
    EXPECT_EQ(ds.find(1), 1);  // 唯一的元素的根是自己

    ds.union_sets(1, 1);       // 合并自身
    EXPECT_EQ(ds.find(1), 1);  // 根不变
}
