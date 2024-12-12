#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<pair<int, int>> meetings(n);  // 存储会议的开始时间和结束时间

    // 读入会议的开始和结束时间
    for (int i = 0; i < n; ++i) {
        cin >> meetings[i].first >> meetings[i].second;
    }

    // 按照开始时间排序
    sort(meetings.begin(), meetings.end());

    // 小根堆（优先队列），用于存储会议的结束时间
    priority_queue<int, vector<int>, greater<int>> pq;

    // 遍历每个会议
    for (int i = 0; i < n; ++i) {
        // 如果当前会议的开始时间大于或等于堆顶的结束时间
        // 说明可以复用一个会议室
        if (!pq.empty() && meetings[i].first >= pq.top()) {
            pq.pop();  // 释放一个会议室
        }

        // 将当前会议的结束时间加入堆中
        pq.push(meetings[i].second);
    }

    // 最终堆中的元素个数就是所需要的会议室数量
    cout << pq.size() << endl;

    return 0;
}
