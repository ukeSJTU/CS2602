#include <algorithm>
#include <iostream>
using namespace std;

const int MAX_SIZE = 100 * 100;  // 网格最多 100 * 100
int parent[MAX_SIZE];            // 并查集的根节点数组
int rankArr[MAX_SIZE];           // 并查集的秩数组
int fishSum[MAX_SIZE];           // 每个连通分量的鱼的数量
int grid[100][100];              // 网格数组
int m, n;                        // 湖的高和宽

// 并查集初始化
void initUnionFind()
{
    for (int i = 0; i < MAX_SIZE; ++i) {
        parent[i] = i;  // 每个节点初始指向自己
        rankArr[i] = 0;
        fishSum[i] = 0;
    }
}

// 查找操作（带路径压缩）
int find(int x)
{
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

// 合并操作（按秩合并）
void unionSet(int x, int y)
{
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY) {
        if (rankArr[rootX] > rankArr[rootY]) {
            parent[rootY] = rootX;
            fishSum[rootX] += fishSum[rootY];  // 合并鱼的数量
        } else if (rankArr[rootX] < rankArr[rootY]) {
            parent[rootX] = rootY;
            fishSum[rootY] += fishSum[rootX];
        } else {
            parent[rootY] = rootX;
            fishSum[rootX] += fishSum[rootY];
            rankArr[rootX]++;
        }
    }
}

int main()
{
    cin >> m >> n;

    initUnionFind();

    // 输入网格并初始化鱼的数量
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> grid[i][j];
            if (grid[i][j] > 0) {
                int index = i * n + j;  // 二维坐标转一维索引
                fishSum[index] = grid[i][j];
            }
        }
    }

    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};  // 四个方向

    // 遍历网格，合并相邻的水域格子
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] > 0) {
                int currentIndex = i * n + j;
                for (int k = 0; k < 4; ++k) {
                    int ni = i + directions[k][0];
                    int nj = j + directions[k][1];
                    if (ni >= 0 && ni < m && nj >= 0 && nj < n && grid[ni][nj] > 0) {
                        int neighborIndex = ni * n + nj;
                        unionSet(currentIndex, neighborIndex);
                    }
                }
            }
        }
    }

    // 计算最大鱼的数量
    int maxFish = 0;
    for (int i = 0; i < m * n; ++i) {
        if (find(i) == i) {  // 只统计根节点
            maxFish = max(maxFish, fishSum[i]);
        }
    }

    cout << maxFish << endl;
    return 0;
}