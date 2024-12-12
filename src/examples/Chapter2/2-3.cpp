// 书本P24：程序2-3，求两个正整数集合的交集
#include <iostream>

#include "SeqList.h"

using namespace datastructures;

int main()
{
    SeqList<int> list1, list2;

    int value;

    std::cout << "请输入第一个列表的元素（以0结束）：\n";
    // 输入第一个列表，0作为结束标志
    while (true) {
        std::cin >> value;
        if (value == 0) break;
        list1.insert(list1.length() + 1, value);  // 插入到列表末尾
    }

    std::cout << "请输入第二个列表的元素（以0结束）：\n";
    // 输入第二个列表，0作为结束标志
    while (true) {
        std::cin >> value;
        if (value == 0) break;
        list2.insert(list2.length() + 1, value);  // 插入到列表末尾
    }

    // 输出两个列表的交集
    std::cout << "交集为：\n";
    SeqList<int> intersectionList;

    for (int i = 1; i <= list1.length(); ++i) {
        int element = list1.get(i);
        // 检查list2中是否包含该元素
        for (int j = 1; j <= list2.length(); ++j) {
            if (list2.get(j) == element) {
                intersectionList.insert(intersectionList.length() + 1, element);
                break;  // 找到一个交集元素，跳出内层循环
            }
        }
    }

    // 输出交集
    for (int i = 1; i <= intersectionList.length(); ++i) {
        std::cout << intersectionList.get(i) << " ";
    }

    std::cout << std::endl;

    return 0;
}
