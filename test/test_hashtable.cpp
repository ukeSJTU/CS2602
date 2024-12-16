#include <gtest/gtest.h>

#include <string>

#include "HashTable.h"

using namespace datastructures;

// 整数哈希函数
int hashFunctionInt(const int& x) { return x; }

// 字符串哈希函数
int hashFunctionString(const std::string& str)
{
    int hash = 0;
    for (char c : str) {
        hash = hash * 31 + c;
    }
    return hash;
}

// 浮点数哈希函数
int hashFunctionFloat(const float& x)
{
    return static_cast<int>(x * 1000);  // 简单的浮点数哈希函数
}

// 测试整数哈希表
TEST(HashTableTest, IntInsert)
{
    HashTable<int> table(10, hashFunctionInt);
    EXPECT_TRUE(table.insert(5));
    EXPECT_TRUE(table.insert(15));
    EXPECT_FALSE(table.insert(5));  // 重复插入
}

TEST(HashTableTest, IntFind)
{
    HashTable<int> table(10, hashFunctionInt);
    table.insert(5);
    table.insert(15);
    EXPECT_TRUE(table.find(5));
    EXPECT_TRUE(table.find(15));
    EXPECT_FALSE(table.find(25));  // 不存在的元素
}

TEST(HashTableTest, IntRemove)
{
    HashTable<int> table(10, hashFunctionInt);
    table.insert(5);
    table.insert(15);
    EXPECT_TRUE(table.remove(5));
    EXPECT_FALSE(table.find(5));     // 删除后查找
    EXPECT_FALSE(table.remove(25));  // 删除不存在的元素
}

TEST(HashTableTest, IntFullTable)
{
    HashTable<int> table(3, hashFunctionInt);
    EXPECT_TRUE(table.insert(1));
    EXPECT_TRUE(table.insert(2));
    EXPECT_TRUE(table.insert(3));
    EXPECT_FALSE(table.insert(4));  // 插入失败，表已满
}

// 测试字符串哈希表
TEST(HashTableTest, StringInsert)
{
    HashTable<std::string> table(10, hashFunctionString);
    EXPECT_TRUE(table.insert("hello"));
    EXPECT_TRUE(table.insert("world"));
    EXPECT_FALSE(table.insert("hello"));  // 重复插入
}

TEST(HashTableTest, StringFind)
{
    HashTable<std::string> table(10, hashFunctionString);
    table.insert("hello");
    table.insert("world");
    EXPECT_TRUE(table.find("hello"));
    EXPECT_TRUE(table.find("world"));
    EXPECT_FALSE(table.find("test"));  // 不存在的元素
}

TEST(HashTableTest, StringRemove)
{
    HashTable<std::string> table(10, hashFunctionString);
    table.insert("hello");
    table.insert("world");
    EXPECT_TRUE(table.remove("hello"));
    EXPECT_FALSE(table.find("hello"));   // 删除后查找
    EXPECT_FALSE(table.remove("test"));  // 删除不存在的元素
}

// 测试浮点数哈希表
TEST(HashTableTest, FloatInsert)
{
    HashTable<float> table(10, hashFunctionFloat);
    EXPECT_TRUE(table.insert(1.23f));
    EXPECT_TRUE(table.insert(4.56f));
    EXPECT_FALSE(table.insert(1.23f));  // 重复插入
}

TEST(HashTableTest, FloatFind)
{
    HashTable<float> table(10, hashFunctionFloat);
    table.insert(1.23f);
    table.insert(4.56f);
    EXPECT_TRUE(table.find(1.23f));
    EXPECT_TRUE(table.find(4.56f));
    EXPECT_FALSE(table.find(7.89f));  // 不存在的元素
}

TEST(HashTableTest, FloatRemove)
{
    HashTable<float> table(10, hashFunctionFloat);
    table.insert(1.23f);
    table.insert(4.56f);
    EXPECT_TRUE(table.remove(1.23f));
    EXPECT_FALSE(table.find(1.23f));    // 删除后查找
    EXPECT_FALSE(table.remove(7.89f));  // 删除不存在的元素
}
