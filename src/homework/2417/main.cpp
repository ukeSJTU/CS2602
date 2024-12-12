#include <iostream>

#include "LinkList.h"

using namespace datastructures;

// 定义一个结构体，用于存储数字及其频率
struct NumberFreq {
    long long number;  // 存储数字，范围 [0, 10^9]
    int frequency;     // 存储该数字的频率

    NumberFreq(long long n = 0, int f = 0) : number(n), frequency(f) {}

    // 用于 LinkList 的查找操作，比较数字是否相等
    bool operator==(const NumberFreq& other) const { return number == other.number; }
};

int main()
{
    int n;  // 数组的大小
    std::cin >> n;

    LinkList<NumberFreq> freqList;  // 使用 LinkList 存储数字及其频率
    int maxFreq = 0;                // 存储最大频率

    for (int i = 0; i < n; i++) {
        long long num;  // 读取当前数字
        std::cin >> num;

        // 尝试在链表中查找该数字
        NumberFreq searchNum(num);
        int pos = freqList.find(searchNum);

        if (pos == -1) {
            // 如果未找到该数字，将其加入链表，初始频率为 1
            freqList.insert(0, NumberFreq(num, 1));
            if (maxFreq < 1) maxFreq = 1;
        } else {
            // 如果找到该数字，增加其频率
            NumberFreq& curr = freqList.get(pos);
            curr.frequency++;
            if (curr.frequency > maxFreq) {
                maxFreq = curr.frequency;
            }
        }
    }

    // 输出最大频率
    std::cout << maxFreq << std::endl;
    return 0;
}