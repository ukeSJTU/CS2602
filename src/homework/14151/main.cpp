#include <iostream>

#include "LinkStack.h"
#include "SeqQueue.h"

using namespace datastructures;

int main()
{
    int T;
    std::cin >> T;
    while (T--) {
        int n;
        std::cin >> n;
        int value;
        bool flag = true;
        LinkStack<int> s;
        SeqQueue<int> q = SeqQueue<int>(n + 1);
        for (int j = 0; j < n; j++) {
            std::cin >> value;

            q.enQueue(value);
        }

        // 判断出栈序列是否合法
        int nextPush = 1;  // 下一个要入栈的数字
        int index = 0;     // 出栈序列的当前索引

        while (nextPush <= n || !s.isEmpty()) {
            // 当栈不为空，且栈顶等于出栈序列的当前数字
            if (!s.isEmpty() && s.top() == q.front()) {
                s.pop();      // 符合出栈条件，弹出栈顶元素
                q.deQueue();  // 移动到下一个出栈序列的数字
                index++;
            } else if (nextPush <= n) {
                // 否则继续将数字入栈
                s.push(nextPush);
                nextPush++;
            } else {
                // 如果既无法匹配栈顶元素，又没有新的数字入栈，序列不合法
                flag = false;
                break;
            }
        }

        // 最终出栈序列的索引应等于 n，表示所有元素成功匹配
        flag = (index == n);

        if (!flag) {
            std::cout << "No" << std::endl;
        } else {
            std::cout << "Yes" << std::endl;
        }
    }
    return 0;
}