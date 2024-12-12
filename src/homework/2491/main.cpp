#include <climits>
#include <iostream>

#include "LinkList.h"
#include "PriorityQueue.h"

using namespace datastructures;

class UglyNumberQueue
{
   private:
    PriorityQueue<long long> pq;
    LinkList<long long> seen;         // 使用链表存储已经出现的丑数
    const int primes[3] = {2, 3, 5};  // 丑数的质因子

   public:
    UglyNumberQueue()
    {
        pq.enQueue(1, -1);  // 使用负优先级，这样较小的数字会有更高的优先级
        seen.insert(0, 1);  // 将1标记为已出现
    }

    int getNthUglyNumber(int n)
    {
        long long ugly = 1;
        for (int i = 0; i < n; ++i) {
            ugly = pq.front();
            pq.deQueue();

            // 生成新的丑数
            for (int prime : primes) {
                // 检查乘法是否会溢出
                if (ugly <= INT_MAX / prime) {
                    long long newUgly = ugly * prime;
                    // 检查新丑数是否已出现
                    if (newUgly <= INT_MAX && seen.find(newUgly) == -1) {
                        seen.insert(0, newUgly);        // 插入新丑数到链表
                        pq.enQueue(newUgly, -newUgly);  // 负优先级使较小的数优先级更高
                    }
                }
            }
        }
        return ugly;
    }
};

int main()
{
    int n;
    std::cin >> n;

    UglyNumberQueue uglyQueue;
    std::cout << uglyQueue.getNthUglyNumber(n) << std::endl;

    return 0;
}
