#include <iostream>
#include <queue>
using namespace std;

int lastStoneWeight(vector<int>& stones)
{
    priority_queue<int> pq;  // 最大堆

    // 将所有宝石加入堆中
    for (int stone : stones) {
        pq.push(stone);
    }

    // 反复取出两颗最重的宝石
    while (pq.size() > 1) {
        int stone1 = pq.top();
        pq.pop();  // 最大
        int stone2 = pq.top();
        pq.pop();  // 第二大

        if (stone1 != stone2) {
            pq.push(stone1 - stone2);  // 差值重新加入堆
        }
    }

    // 如果堆中还有宝石，返回它的重量；否则返回0
    return pq.empty() ? 0 : pq.top();
}

int main()
{
    int n;
    cin >> n;  // 输入宝石个数

    vector<int> stones(n);
    for (int i = 0; i < n; i++) {
        cin >> stones[i];  // 输入每个宝石的重量
    }

    cout << lastStoneWeight(stones) << endl;

    return 0;
}