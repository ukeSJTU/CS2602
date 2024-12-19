#include <iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;

    // 动态分配内存存储优先级
    int* priorities = new int[n];
    for (int i = 0; i < n; ++i) {
        cin >> priorities[i];
    }

    // 步骤1：统计每种优先级的数量
    int c0 = 0, c1 = 0, c2 = 0;
    for (int i = 0; i < n; ++i) {
        if (priorities[i] == 0)
            c0++;
        else if (priorities[i] == 1)
            c1++;
        else if (priorities[i] == 2)
            c2++;
    }

    // 步骤2：划分区域
    // 定义三个区域的起始和结束索引
    // 区域0: [0, c0-1]
    // 区域1: [c0, c0+c1-1]
    // 区域2: [c0+c1, n-1]

    // 步骤3：统计各区域内的实际优先级分布
    // m[i][j] 表示实际优先级为 i 的包裹在期望优先级为 j 的区域中的数量
    int** m = new int*[3];
    for (int i = 0; i < 3; ++i) {
        m[i] = new int[3];
        for (int j = 0; j < 3; ++j) {
            m[i][j] = 0;
        }
    }

    // 统计区域0
    for (int i = 0; i < c0; ++i) {
        if (priorities[i] >= 0 && priorities[i] <= 2) {
            m[priorities[i]][0]++;
        }
    }

    // 统计区域1
    for (int i = c0; i < c0 + c1; ++i) {
        if (priorities[i] >= 0 && priorities[i] <= 2) {
            m[priorities[i]][1]++;
        }
    }

    // 统计区域2
    for (int i = c0 + c1; i < n; ++i) {
        if (priorities[i] >= 0 && priorities[i] <= 2) {
            m[priorities[i]][2]++;
        }
    }

    // 步骤4：计算直接交换次数
    int swap_01 = min(m[0][1], m[1][0]);
    int swap_02 = min(m[0][2], m[2][0]);
    int swap_12 = min(m[1][2], m[2][1]);

    long long total_swaps = 0;
    total_swaps += swap_01;
    total_swaps += swap_02;
    total_swaps += swap_12;

    // 更新矩阵 m
    m[0][1] -= swap_01;
    m[1][0] -= swap_01;

    m[0][2] -= swap_02;
    m[2][0] -= swap_02;

    m[1][2] -= swap_12;
    m[2][1] -= swap_12;

    // 步骤5：计算剩余错位包裹数量
    int remaining = 0;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (i != j) {
                remaining += m[i][j];
            }
        }
    }

    // 处理循环交换，每个循环需要两次交换
    // 每个循环涉及三个包裹，因此循环次数为 remaining / 3
    long long cycles = remaining / 3;
    total_swaps += 2 * cycles;

    // 输出结果
    cout << total_swaps << endl;

    // 释放动态分配的内存
    delete[] priorities;
    for (int i = 0; i < 3; ++i) {
        delete[] m[i];
    }
    delete[] m;

    return 0;
}