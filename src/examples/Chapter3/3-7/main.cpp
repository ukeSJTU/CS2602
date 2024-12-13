#include <cstring>
#include <iostream>

#include "LinkStack.h"

/**
 * @brief 计算后缀表达式的结果
 * @param postfixStr 输入的后缀表达式
 * @return 计算结果
 */
int calculatePostfix(const char *postfixStr)
{
    datastructures::LinkStack<int> stack;  // 操作数栈
    int i = 0;

    while (postfixStr[i] != '\0') {
        if (postfixStr[i] >= '0' && postfixStr[i] <= '9') {
            stack.push(postfixStr[i] - '0');  // 将字符数字转换为整数
        } else {
            int op2 = stack.top();
            stack.pop();
            int op1 = stack.top();
            stack.pop();

            int result;
            switch (postfixStr[i]) {
                case '*':
                    result = op1 * op2;
                    break;
                case '/':
                    result = op1 / op2;
                    break;
                case '+':
                    result = op1 + op2;
                    break;
                case '-':
                    result = op1 - op2;
                    break;
                default:
                    throw std::runtime_error("无效的运算符");
            }
            stack.push(result);
        }
        i++;
    }

    return stack.top();
}

int main()
{
    char postfixStr[100] = "931-3*+62/+";  // 示例后缀表达式
    std::cout << "示例后缀表达式: " << postfixStr << std::endl;
    std::cout << "计算结果: " << calculatePostfix(postfixStr) << std::endl;

    std::cout << "请输入后缀表达式（输入 'exit' 结束）：" << std::endl;
    while (true) {
        std::cin.getline(postfixStr, 100);
        if (strcmp(postfixStr, "exit") == 0) break;
        try {
            int result = calculatePostfix(postfixStr);
            std::cout << "计算结果: " << result << std::endl;
        } catch (const std::runtime_error &e) {
            std::cerr << "错误: " << e.what() << std::endl;
        }
    }

    return 0;
}