#ifndef EXP_TREE_H
#define EXP_TREE_H

#include "BinaryTree.h"
#include <cstddef>
#include <iostream>

namespace datastructures {

// 表达式树类，继承自二叉树
template <class elemType> class ExprTree : public BTree<elemType> {
  public:
    ExprTree() : BTree<elemType>() {}

    // 构建表达式树
    void buildExpTree(const char *expr);

    // 比较运算符优先级
    int comparePriority(const char op1, const char op2);

    // 计算表达式树的值
    int calcExprTree();
};

// 比较运算符优先级，返回值意义：
// 1: op1优先级比op2高，
// -1: op1优先级比op2低，
// 0: op1优先级与op2相同
template <class elemType> int ExprTree<elemType>::comparePriority(const char op1, const char op2) {
    switch (op1) {
    case '(':
        return 1;
    case ')':
        return (op2 != '(') ? -1 : 0;
    case '*':
    case '/':
        return (op2 == '*' || op2 == '/') ? -1 : 1;
    case '+':
    case '-':
        return (op2 == '(' || op2 == '#') ? 1 : -1;
    }
    return 0; // 未知操作符返回0
}

// 根据传入的表达式构建表达式树
template <class elemType> void ExprTree<elemType>::buildExpTree(const char *expr) {
    SeqStack<char> opStack;                  // 操作符栈
    SeqStack<Node<elemType> *> subTreeStack; // 子树栈
    Node<elemType> *node, *left, *right;
    char hash = '#', currentChar;

    opStack.push(hash); // 初始符号栈，填入#符号

    while (*expr) {
        if ((*expr >= '0') && (*expr <= '9')) { // 如果当前字符是数字
            node = new Node<elemType>(*expr);   // 创建一个新节点
            subTreeStack.push(node);            // 将该节点压入子树栈
        } else {                                // 如果是运算符
            currentChar = opStack.top();        // 获取栈顶的运算符

            // 如果当前操作符优先级低于栈顶运算符，进行合并操作
            while (comparePriority(*expr, currentChar) == -1) {
                opStack.pop();
                right = subTreeStack.top();
                subTreeStack.pop();
                left = subTreeStack.top();
                subTreeStack.pop();
                node = new Node<elemType>(currentChar, left, right);
                subTreeStack.push(node);
                currentChar = opStack.top(); // 继续检查栈顶符号
            }

            if (comparePriority(*expr, currentChar) == 0) { // 优先级相同
                opStack.pop();                              // 弹出栈顶运算符
            } else {                                        // 优先级较高，直接压入符号栈
                opStack.push(*expr);
            }
        }
        expr++; // 继续处理下一个字符
    }

    // 处理完所有字符后，将栈中剩余的操作符与子树合并
    currentChar = opStack.top();
    while (currentChar != '#') {
        opStack.pop();
        right = subTreeStack.top();
        subTreeStack.pop();
        left = subTreeStack.top();
        subTreeStack.pop();
        node = new Node<elemType>(currentChar, left, right);
        subTreeStack.push(node);
        currentChar = opStack.top(); // 继续检查栈顶符号
    }

    this->root = subTreeStack.top(); // 设置树的根节点
    subTreeStack.pop();              // 弹出栈顶元素
}

// 计算表达式树的值
template <class elemType> int ExprTree<elemType>::calcExprTree() {
    if (this->getRoot() == nullptr) { // 空树直接返回0
        return 0;
    }

    Node<elemType> *node;
    SeqStack<Node<elemType> *> nodeStack; // 存储节点的栈
    SeqStack<int> operationStack;         // 存储操作符的栈
    SeqStack<int> numStack;               // 存储数值的栈

    int zero = 0, one = 1, two = 2;
    int flag, num, num1, num2;

    nodeStack.push(this->getRoot()); // 初始节点入栈
    operationStack.push(zero);       // 初始状态为0（左子树）

    while (!nodeStack.isEmpty()) { // 遍历树
        flag = operationStack.top();
        operationStack.pop();
        node = nodeStack.top(); // 获取栈顶节点

        switch (flag) {
        case 2: // 处理当前节点的操作
            nodeStack.pop();
            if ((this->getData(node) >= '0') && (this->getData(node) <= '9')) { // 当前节点是数字
                num = this->getData(node) - '0';                                // 获取数字
                numStack.push(num);                                             // 将数字压入栈
            } else {                                                            // 当前节点是操作符
                num2 = numStack.top();
                numStack.pop();
                num1 = numStack.top();
                numStack.pop();
                switch (this->getData(node)) { // 根据操作符进行计算
                case '+':
                    num = num1 + num2;
                    break;
                case '-':
                    num = num1 - num2;
                    break;
                case '*':
                    num = num1 * num2;
                    break;
                case '/':
                    num = num1 / num2;
                    break;
                }
                numStack.push(num); // 将结果压入栈
            }
            break;
        case 1: // 处理右子树
            operationStack.push(two);
            if (this->getRight(node) != nullptr) {
                nodeStack.push(this->getRight(node)); // 右子树入栈
                operationStack.push(zero);            // 设置状态为0（左子树）
            }
            break;
        case 0: // 处理左子树
            operationStack.push(one);
            if (this->getLeft(node) != nullptr) {
                nodeStack.push(this->getLeft(node)); // 左子树入栈
                operationStack.push(zero);           // 设置状态为0（左子树）
            }
            break;
        } // switch
    } // while

    num = numStack.top(); // 结果栈的顶部即为计算结果
    numStack.pop();
    return num; // 返回最终计算结果
}

} // namespace datastructures

#endif
