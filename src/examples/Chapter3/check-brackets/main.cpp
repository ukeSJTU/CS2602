// 本代码是书本上示例程序3-5的拓展

#include <functional>
#include <iostream>
#include <string>
#include <vector>

#include "LinkStack.h"

// 检查括号匹配的逻辑
bool checkBrackets(const std::string &expression, std::string &errorMsg, std::string &errorTrace)
{
    datastructures::LinkStack<std::pair<char, int>> s;
    char ctemp;
    for (int i = 0; i < expression.length(); ++i) {
        ctemp = expression[i];
        if (ctemp == '(' || ctemp == '[' || ctemp == '{') {
            s.push({ctemp, i});
        } else if (ctemp == ')' || ctemp == ']' || ctemp == '}') {
            if (s.isEmpty()) {
                errorMsg = "Unexpected closing bracket '" + std::string(1, ctemp) +
                           "' at position " + std::to_string(i);
                errorTrace = std::string(i, ' ') + "^";  // 标记位置
                return false;
            }
            auto [topChar, topPos] = s.top();
            s.pop();

            // 检查匹配
            if ((topChar == '(' && ctemp != ')') || (topChar == '[' && ctemp != ']') ||
                (topChar == '{' && ctemp != '}')) {
                errorMsg = "Mismatched brackets: '" + std::string(1, topChar) + "' at position " +
                           std::to_string(topPos) + " and '" + std::string(1, ctemp) +
                           "' at position " + std::to_string(i);
                errorTrace =
                    std::string(topPos, ' ') + "^" + std::string(i - topPos - 1, ' ') + "^";
                return false;
            }
        }
    }

    // 检查未匹配的左括号
    if (!s.isEmpty()) {
        auto [topChar, topPos] = s.top();
        errorMsg = "Unclosed opening bracket '" + std::string(1, topChar) + "' at position " +
                   std::to_string(topPos);
        errorTrace = std::string(topPos, ' ') + "^";  // 标记位置
        return false;
    }

    return true;
}

// 运行测试数据
void runTests(
    const std::function<bool(const std::string &, std::string &, std::string &)> &matchLogic)
{
    std::vector<std::string> testExpressions = {
        "()", "([]{})", "({[)]}", "((()", "())", "({[})]",
    };

    for (const auto &expression : testExpressions) {
        std::string errorMsg, errorTrace;
        bool result = matchLogic(expression, errorMsg, errorTrace);
        std::cout << "Expression: " << expression << "\n";
        if (result) {
            std::cout << "Result: Brackets match\n";
        } else {
            std::cout << "Result: " << errorMsg << "\n";
            std::cout << "         " << expression << "\n";
            std::cout << "         " << errorTrace << "\n";
        }
        std::cout << "--------------------------\n";
    }
}

// 主函数
int main()
{
    // 运行测试数据
    std::cout << "Running fixed test cases:\n";
    runTests(checkBrackets);

    // 进入交互模式
    std::cout << "Entering interactive mode. Type 'exit' to quit.\n";
    std::string input;
    while (true) {
        std::cout << "Input an expression: ";
        std::getline(std::cin, input);

        if (input == "exit") {
            break;
        }

        std::string errorMsg, errorTrace;
        if (checkBrackets(input, errorMsg, errorTrace)) {
            std::cout << "The brackets match in this expression\n";
        } else {
            std::cout << "Error: " << errorMsg << "\n";
            std::cout << "       " << input << "\n";
            std::cout << "       " << errorTrace << "\n";
        }
    }

    return 0;
}