// !!! 如果你最后4个测试案例错误，请检查自己是不是用的 int 存储数据，请用 long long
#include <iostream>

#include "LinkQueue.h"

int main()
{
    int n;

    std::cin >> n;

    if (n <= 9) {
        std::cout << n << std::endl;
        return 0;
    }

    datastructures::LinkQueue<long long> q;
    for (int i = 1; i <= 9; i++) {
        q.enQueue(i);
    }

    while (n != 1) {
        long long value = q.front();
        q.deQueue();
        switch (value % 10) {
            case 0:
                q.enQueue(value * 10 + 0);
                q.enQueue(value * 10 + 1);
                break;

            case 1:
                q.enQueue(value * 10 + 0);
                q.enQueue(value * 10 + 1);
                q.enQueue(value * 10 + 2);
                break;

            case 2:
                q.enQueue(value * 10 + 1);
                q.enQueue(value * 10 + 2);
                q.enQueue(value * 10 + 3);
                break;

            case 3:
                q.enQueue(value * 10 + 2);
                q.enQueue(value * 10 + 3);
                q.enQueue(value * 10 + 4);
                break;

            case 4:
                q.enQueue(value * 10 + 3);
                q.enQueue(value * 10 + 4);
                q.enQueue(value * 10 + 5);
                break;

            case 5:
                q.enQueue(value * 10 + 4);
                q.enQueue(value * 10 + 5);
                q.enQueue(value * 10 + 6);
                break;

            case 6:
                q.enQueue(value * 10 + 5);
                q.enQueue(value * 10 + 6);
                q.enQueue(value * 10 + 7);
                break;

            case 7:
                q.enQueue(value * 10 + 6);
                q.enQueue(value * 10 + 7);
                q.enQueue(value * 10 + 8);
                break;

            case 8:
                q.enQueue(value * 10 + 7);
                q.enQueue(value * 10 + 8);
                q.enQueue(value * 10 + 9);
                break;

            case 9:
                q.enQueue(value * 10 + 8);
                q.enQueue(value * 10 + 9);
                break;
        }

        n -= 1;
    }

    std::cout << q.front() << std::endl;

    return 0;
}