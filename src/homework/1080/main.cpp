#include <iostream>

#include "LinkStack.h"

int calculatePostfix(const char *postfixStr)
{
    datastructures::LinkStack<int> stack;
    int i = 0;

    int num = 0;

    while (postfixStr[i] != '@') {
        if (postfixStr[i] == '.') {
            stack.push(num);

            num = 0;
        } else if (postfixStr[i] >= '0' && postfixStr[i] <= '9') {
            num = num * 10 + (postfixStr[i] - '0');
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
            }
            stack.push(result);
        }

        i++;
    }

    return stack.top();
}

int main()
{
    char postfixStr[10000];
    std::cin.getline(postfixStr, 10000);

    std::cout << calculatePostfix(postfixStr) << std::endl;

    return 0;
}