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

int main()
{
    char infixStr[100] = "9+(3-1)*3+6/2";  // 示例中缀表达式
    char postfixStr[100];

    std::cout << "示例中缀表达式: " << infixStr << std::endl;
    convertInfixToPostfix(infixStr, postfixStr);
    std::cout << "转换后的后缀表达式: " << postfixStr << std::endl;

    std::cout << "请输入中缀表达式（输入 'exit' 结束）：" << std::endl;
    while (true) {
        std::cin.getline(infixStr, 100);
        if (strcmp(infixStr, "exit") == 0) break;
        convertInfixToPostfix(infixStr, postfixStr);
        std::cout << "后缀表达式: " << postfixStr << std::endl;
    }

    return 0;
}