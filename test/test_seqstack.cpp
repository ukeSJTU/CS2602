#include <gtest/gtest.h>

#include "Exceptions.h"
#include "SeqStack.h"

// 测试 SeqStack 类
namespace datastructures
{

// 测试 SeqStack 是否能够正常初始化
TEST(SeqStackTest, Initialization)
{
    SeqStack<int> stack(5);
    EXPECT_TRUE(stack.isEmpty());
    EXPECT_FALSE(stack.isFull());
}

// 测试 SeqStack push 和 top 方法
TEST(SeqStackTest, PushAndTop)
{
    SeqStack<int> stack(5);

    stack.push(1);
    EXPECT_EQ(stack.top(), 1);

    stack.push(2);
    EXPECT_EQ(stack.top(), 2);

    stack.push(3);
    EXPECT_EQ(stack.top(), 3);
}

// 测试 SeqStack pop 方法
TEST(SeqStackTest, Pop)
{
    SeqStack<int> stack(5);

    stack.push(1);
    stack.push(2);
    stack.push(3);

    stack.pop();
    EXPECT_EQ(stack.top(), 2);

    stack.pop();
    EXPECT_EQ(stack.top(), 1);

    stack.pop();
    EXPECT_TRUE(stack.isEmpty());
}

// 测试栈满时的行为
TEST(SeqStackTest, FullStack)
{
    SeqStack<int> stack(3);

    stack.push(1);
    stack.push(2);
    stack.push(3);

    EXPECT_TRUE(stack.isFull());
    EXPECT_NO_THROW(stack.push(4));  // 不应抛出异常，因为栈应在满时扩展
}

// 测试栈为空时的行为
TEST(SeqStackTest, EmptyStack)
{
    SeqStack<int> stack(5);

    EXPECT_TRUE(stack.isEmpty());
    EXPECT_THROW(stack.pop(), OutOfBound);  // 空栈 pop 应抛出异常
    EXPECT_THROW(stack.top(), OutOfBound);  // 空栈 top 应抛出异常
}

// 测试栈动态扩展
TEST(SeqStackTest, DynamicExpansion)
{
    SeqStack<int> stack(2);

    stack.push(1);
    stack.push(2);

    // 在这里栈应该扩展
    stack.push(3);

    EXPECT_EQ(stack.top(), 3);  // 栈顶应该是 3
}

}  // namespace datastructures

// 主函数执行所有测试
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
