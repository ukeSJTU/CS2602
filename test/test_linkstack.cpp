#include <gtest/gtest.h>

#include "LinkStack.h"

using namespace datastructures;

// 测试 LinkStack 的各个功能
TEST(LinkStackTest, PushTest)
{
    LinkStack<int> stack;

    // 测试入栈
    stack.push(10);
    stack.push(20);
    stack.push(30);

    // 测试栈顶元素
    EXPECT_EQ(stack.top(), 30);
}

TEST(LinkStackTest, PopTest)
{
    LinkStack<int> stack;
    stack.push(10);
    stack.push(20);
    stack.push(30);

    // 测试出栈
    stack.pop();
    EXPECT_EQ(stack.top(), 20);

    stack.pop();
    EXPECT_EQ(stack.top(), 10);

    // 测试栈为空时的出栈操作
    stack.pop();
    EXPECT_THROW(stack.pop(), OutOfBound);  // 空栈抛出异常
}

TEST(LinkStackTest, TopTest)
{
    LinkStack<int> stack;

    // 测试栈顶元素
    stack.push(10);
    stack.push(20);
    stack.push(30);
    EXPECT_EQ(stack.top(), 30);

    // 测试空栈时的 top 操作
    stack.pop();
    stack.pop();
    stack.pop();
    EXPECT_THROW(stack.top(), OutOfBound);  // 空栈抛出异常
}

TEST(LinkStackTest, IsEmptyTest)
{
    LinkStack<int> stack;

    // 测试栈为空时的情况
    EXPECT_TRUE(stack.isEmpty());

    // 测试栈非空时的情况
    stack.push(10);
    EXPECT_FALSE(stack.isEmpty());

    stack.pop();
    EXPECT_TRUE(stack.isEmpty());
}
