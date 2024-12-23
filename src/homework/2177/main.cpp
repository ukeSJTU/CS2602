#include <algorithm>
#include <iostream>

#include "DisjointSet.h"

using namespace std;

int get_max_tree_size(datastructures::DisjointSet& ds)
{
    int max_size = 0;
    for (int i = 1; i <= ds.size; ++i) {
        if (ds.parent[i] < 0) {
            max_size = std::max(max_size, -ds.parent[i]);
        }
    }
    return max_size;
}

int main()
{
    int n, m;
    cin >> n >> m;  // 读取节点数和边数

    datastructures::DisjointSet ds(n);

    // 读取所有边
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        ds.union_sets(u, v);  // 合并两个节点
    }

    // 输出最大树的节点数
    cout << get_max_tree_size(ds) << endl;

    return 0;
}