#include <iostream>

#include "LinkList.h"
#include "PriorityQueue.h"

using namespace datastructures;

class UglyNumberQueue
{
   private:
    PriorityQueue<long long> pq = PriorityQueue<long long>(1001);  // 使用小顶堆优先队列
    LinkList<long long> seen;                                      // 使用链表存储已经出现的丑数
    const int primes[3] = {2, 3, 5};                               // 丑数的质因子

    /**
     * @brief 判断一个值是否已存在于链表
     * @param value 要查找的值
     * @return true 如果值已存在；否则 false
     */
    bool isSeen(long long value)
    {
        for (int i = 0; i < seen.length(); ++i) {
            if (seen.get(i) == value) return true;
        }
        return false;
    }

   public:
    UglyNumberQueue()
    {
        pq.enQueue(1);      // 初始化优先队列，插入第一个丑数 1
        seen.insert(0, 1);  // 插入到链表中记录已出现的丑数
    }

    int getNthUglyNumber(int n)
    {
        long long ugly = 1;
        for (int i = 0; i < n; ++i) {
            ugly = pq.front();  // 获取堆顶最小值
            pq.deQueue();       // 删除堆顶元素

            // 生成新的丑数
            for (int prime : primes) {
                long long newUgly = ugly * prime;

                // 检查是否重复
                if (seen.find(newUgly) == -1) {
                    seen.insert(0, newUgly);  // 插入到链表
                    pq.enQueue(newUgly);      // 插入到优先队列
                }
            }
        }
        return static_cast<int>(ugly);
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