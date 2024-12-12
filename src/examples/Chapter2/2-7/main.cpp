#include <iostream>

#include "LinkList.h"

struct Item {
    int coef;
    int exp;
};

void parseExpression(datastructures::LinkList<Item> &expr)
{
    int coef, exp;
    std::cin >> coef >> exp;
    while (coef != 0 && exp != 0) {
        Item item = {coef, exp};
        expr.insert(expr.length(), item);
        std::cin >> coef >> exp;
    }
}

void printExpression(const datastructures::LinkList<Item> &expr)
{
    for (int i = 0; i < expr.length(); i++) {
        Item item = expr.get(i);
        std::cout << item.coef << "x^" << item.exp;
        if (i != expr.length() - 1) {
            std::cout << "+";
        }
    }
    std::cout << std::endl;
}

datastructures::LinkList<Item> addExpression(const datastructures::LinkList<Item> &expr1,
                                             const datastructures::LinkList<Item> &expr2)
{
    datastructures::LinkList<Item> result;
    int i = 0, j = 0;
    while (i < expr1.length() && j < expr2.length()) {
        Item item1 = expr1.get(i);
        Item item2 = expr2.get(j);
        // 指数小的项先插入
        if (item1.exp < item2.exp) {
            result.insert(result.length(), item1);
            i++;
        } else if (item1.exp > item2.exp) {
            result.insert(result.length(), item2);
            j++;
        } else {
            // 系数和为 0，不插入
            if (item1.coef + item2.coef == 0) {
                i++;
                j++;
                continue;
            } else {
                Item item = {item1.coef + item2.coef, item1.exp};
                result.insert(result.length(), item);
                i++;
                j++;
            }
        }
    }
    while (i < expr1.length()) {
        Item item = expr1.get(i);
        result.insert(result.length(), item);
        i++;
    }
    while (j < expr2.length()) {
        Item item = expr2.get(j);
        result.insert(result.length(), item);
        j++;
    }
    return result;
}

int main()
{
    datastructures::LinkList<Item> expr1, expr2;

    std::cout << "请输入第一个多项式" << std::endl;
    std::cout << "请按照指数从小到大输入系数、指数对，最后输入 0 0 来结束多项式" << std::endl;
    parseExpression(expr1);

    std::cout << "多项式 1 为：" << std::endl;
    printExpression(expr1);

    std::cout << "请输入第二个多项式" << std::endl;
    std::cout << "请按照指数从小到大输入系数、指数对，最后输入 0 0 来结束多项式" << std::endl;
    parseExpression(expr2);

    std::cout << "多项式 2 为：" << std::endl;
    printExpression(expr2);

    std::cout << "两个多项式相加的结果为：" << std::endl;
    datastructures::LinkList<Item> add_result = addExpression(expr1, expr2);
    printExpression(add_result);

    return 0;
}