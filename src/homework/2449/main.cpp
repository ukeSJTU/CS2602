#include <iostream>

#include "SeqQueue.h"

using namespace std;

struct Credit {
    int cnt;
    int expiresAt;
};

int main()
{
    int n, m;
    cin >> n >> m;

    datastructures::SeqQueue<Credit> q;
    int totalUsed = 0;  // 累计用掉的积分

    for (int day = 1; day <= n; ++day) {
        int p, c;  // p: 今日获得积分, c: 今日需要消费的积分
        cin >> p >> c;

        // 将今天获得的积分入队，设置有效期截止天数
        if (p > 0) {
            q.enQueue({p, day + m});
        }

        // 清理过期积分（队头的积分是否过期）
        while (!q.isEmpty() && q.front().expiresAt < day) {
            q.deQueue();
        }

        // 消费积分，优先用最早的积分
        while (c > 0 && !q.isEmpty()) {
            Credit &credit = q.front();
            if (credit.cnt <= c) {  // 积分不足以满足需求
                c -= credit.cnt;    // 用掉队头积分
                totalUsed += credit.cnt;
                q.deQueue();      // 积分用完，出队
            } else {              // 积分足够满足需求
                credit.cnt -= c;  // 扣掉消费的积分
                totalUsed += c;
                c = 0;
            }
        }
    }

    cout << totalUsed << endl;
    return 0;
}