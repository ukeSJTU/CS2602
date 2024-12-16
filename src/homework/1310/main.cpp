#include <algorithm>
#include <iostream>

#include "PriorityQueue.h"

using namespace datastructures;

struct Meeting {
    int start_time, end_time;
};

bool compare(Meeting a, Meeting b) { return a.start_time < b.start_time; }

int main()
{
    int n;
    std::cin >> n;

    Meeting meetings[2001];

    // 读入会议的开始和结束时间
    for (int i = 0; i < n; ++i) {
        Meeting meeting;
        std::cin >> meeting.start_time >> meeting.end_time;
        meetings[i] = meeting;
    }

    std::sort(meetings, meetings + n, compare);

    // 优先队列，存储会议的结束时间
    PriorityQueue<int> pq;

    // 遍历每个会议
    for (int i = 0; i < n; ++i) {
        // 如果当前会议的开始时间大于或等于堆顶的结束时间
        // 说明可以复用一个会议室
        if (!pq.isEmpty() && meetings[i].start_time >= pq.front()) {
            pq.deQueue();  // 释放一个会议室
        }

        // 将当前会议的结束时间加入堆中
        pq.enQueue(meetings[i].end_time);
    }

    // 最终堆中的元素个数就是所需要的会议室数量
    std::cout << pq.getSize() << std::endl;

    return 0;
}