#include <cctype>
#include <cstddef>
#include <iostream>
#include <string>

#include "LinkStack.h"

int precedence(char op)
{
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

std::string infixToPostfix(const std::string &infix)
{
    datastructures::LinkStack<char> stack;
    std::string postfix;
    std::string number;  // 用于存储多位数字

    for (size_t i = 0; i < infix.length() && infix[i] != '@'; ++i) {
        char ch = infix[i];
        if (std::isspace(ch)) continue;

        if (std::isdigit(ch)) {
            number += ch;
        } else if (ch == '.') {
            // 遇到小数点，表示数字结束
            postfix += number + ".";
            number = "";
        } else if (ch == '(') {
            stack.push(ch);
        } else if (ch == ')') {
            while (!stack.isEmpty() && stack.top() != '(') {
                postfix += stack.top();
                stack.pop();
            }
            if (!stack.isEmpty()) stack.pop();  // 弹出 '('
        } else {
            while (!stack.isEmpty() && precedence(stack.top()) >= precedence(ch)) {
                postfix += stack.top();
                stack.pop();
            }
            stack.push(ch);
        }
    }

    while (!stack.isEmpty()) {
        postfix += stack.top();
        stack.pop();
    }

    return postfix + "@";
}

int main()
{
    std::string infix;
    std::getline(std::cin, infix);

    std::string postfix = infixToPostfix(infix);
    std::cout << postfix << std::endl;

    return 0;
}