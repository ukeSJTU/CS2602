#include <cstring>
#include <iostream>

#include "LinkStack.h"

/**
 * @brief 将中缀表达式转换为后缀表达式
 * @param infixStr 输入的中缀表达式
 * @param postfixStr 输出的后缀表达式
 */
void convertInfixToPostfix(const char *infixStr, char *postfixStr)
{
    datastructures::LinkStack<char> stack;  // 操作符栈
    int i = 0, j = 0;
    char topChar;

    stack.push('#');  // 初始化栈，使用 '#' 作为栈底标志

    while (infixStr[i] != '\0') {
        if ((infixStr[i] >= '0') && (infixStr[i] <= '9')) {
            postfixStr[j++] = infixStr[i++];  // 操作数直接加入后缀表达式
        } else {
            switch (infixStr[i]) {
                case '(':  // 左括号直接入栈
                    stack.push('(');
                    break;
                case ')':  // 遇到右括号，将栈顶元素弹出并加入后缀表达式，直到遇到左括号
                    while (stack.top() != '(') {
                        postfixStr[j++] = stack.top();
                        stack.pop();
                    }
                    stack.pop();  // 弹出 '('
                    break;
                case '*':
                case '/':  // 处理乘除运算符
                    while (stack.top() == '*' || stack.top() == '/') {
                        postfixStr[j++] = stack.top();
                        stack.pop();
                    }
                    stack.push(infixStr[i]);
                    break;
                case '+':
                case '-':  // 处理加减运算符
                    while (stack.top() != '(' && stack.top() != '#') {
                        postfixStr[j++] = stack.top();
                        stack.pop();
                    }
                    stack.push(infixStr[i]);
                    break;
                default:
                    break;
            }
            i++;
        }
    }

    // 处理栈中剩余的操作符
    while (stack.top() != '#') {
        postfixStr[j++] = stack.top();
        stack.pop();
    }

    postfixStr[j] = '\0';  // 结束符
}

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
    char infixStr[100];    // 中缀表达式输入
    char postfixStr[100];  // 转换后的后缀表达式

    std::cout << "请输入中缀表达式（例如 '9+(3-1)*3+6/2'，输入 'exit' 结束）：" << std::endl;
    while (true) {
        std::cin.getline(infixStr, 100);
        if (strcmp(infixStr, "exit") == 0) break;

        try {
            convertInfixToPostfix(infixStr, postfixStr);  // 转换为后缀表达式
            std::cout << "后缀表达式: " << postfixStr << std::endl;

            int result = calculatePostfix(postfixStr);  // 计算后缀表达式结果
            std::cout << "计算结果: " << result << std::endl;
        } catch (const std::exception &e) {
            std::cerr << "错误: " << e.what() << std::endl;
        }
    }

    return 0;
}