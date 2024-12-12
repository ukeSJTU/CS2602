#include <iostream>
#include <string>

#include "ExprTree.h"

using namespace datastructures;

int main()
{
    ExprTree<char> expression_tree;
    std::string expr;  // 用于存储用户输入的表达式

    std::cout << "欢迎使用表达式树计算器！" << std::endl;

    // 示例表达式
    std::string example_expr = "7*(5-2)-8/2";
    std::cout << "\n示例表达式: " << example_expr << std::endl;

    // 输出计算示例表达式的结果
    expression_tree.buildExpTree(example_expr.c_str());
    std::cout << "示例表达式树的中序遍历结果: ";
    expression_tree.inOrder();  // 这里假设你已经实现了中序遍历
    std::cout << std::endl;

    int result = expression_tree.calcExprTree();
    std::cout << "计算结果: " << result << std::endl;

    // 循环让用户不断输入表达式
    while (true) {
        // 提示用户输入表达式
        std::cout << "\n请输入一个中缀表达式（或输入 'exit' 退出程序）：";
        std::getline(std::cin, expr);  // 获取用户输入的表达式

        // 如果用户输入 "exit"，则退出程序
        if (expr == "exit") {
            std::cout << "程序已退出，感谢使用！" << std::endl;
            break;
        }

        // 校验表达式是否合法（这里只做简单判断，实际可以更严格）
        if (expr.empty()) {
            std::cout << "错误：表达式不能为空，请输入有效的表达式。" << std::endl;
            continue;
        }

        // 输出用户输入的表达式
        std::cout << "你输入的表达式: " << expr << std::endl;

        // 构建表达式树
        try {
            expression_tree.buildExpTree(expr.c_str());  // 将字符串转换为 C 风格字符串
        } catch (const std::exception &e) {
            std::cout << "错误：" << e.what() << std::endl;
            continue;
        }

        // 输出表达式树的中序遍历结果
        std::cout << "表达式树的中序遍历结果: ";
        expression_tree.inOrder();  // 这里假设你已经实现了中序遍历
        std::cout << std::endl;

        // 计算并输出结果
        try {
            int result = expression_tree.calcExprTree();
            std::cout << "计算结果: " << result << std::endl;
        } catch (const std::exception &e) {
            std::cout << "计算错误: " << e.what() << std::endl;
        }
    }

    return 0;
}
