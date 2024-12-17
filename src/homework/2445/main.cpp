#include <iostream>
#include <string>

#include "LinkStack.h"
using namespace std;

bool isBalanced(const string& s)
{
    datastructures::LinkStack<char> stack;
    for (char ch : s) {
        if (ch == '(' || ch == '[') {
            // 遇到左括号，压入栈中
            stack.push(ch);
        } else if (ch == ')') {
            // 遇到右括号 ')'，检查栈顶
            if (stack.isEmpty() || stack.top() != '(') {
                return false;  // 不匹配
            }
            stack.pop();  // 匹配成功，弹出栈顶
        } else if (ch == ']') {
            // 遇到右括号 ']'，检查栈顶
            if (stack.isEmpty() || stack.top() != '[') {
                return false;  // 不匹配
            }
            stack.pop();  // 匹配成功，弹出栈顶
        }
    }

    // 最后检查栈是否为空
    return stack.isEmpty();
}

int main()
{
    string input;
    cin >> input;
    if (isBalanced(input)) {
        cout << "Balanced" << endl;
    } else {
        cout << "Unbalanced" << endl;
    }

    return 0;
}