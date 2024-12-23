#ifndef DISJOINT_SET_H
#define DISJOINT_SET_H

namespace datastructures
{

/**
 * @brief 并查集类 (Disjoint Set)
 *
 * 并查集是一种数据结构，用于处理不相交集合的合并和查询操作。
 */
class DisjointSet
{
   public:
    int size;     ///< 集合的大小
    int* parent;  ///< 存储每个节点的父节点，负数表示根节点的大小或高度

    /**
     * @brief 构造函数：初始化并查集
     * @param s 集合大小
     */
    explicit DisjointSet(int s);

    /**
     * @brief 析构函数：释放动态分配的内存
     */
    ~DisjointSet();

    /**
     * @brief 查找操作：找到元素 x 所在集合的根节点（带路径压缩）
     * @param x 要查找的元素
     * @return int 根节点的索引
     */
    int find(int x);

    /**
     * @brief 合并操作：将两个集合合并为一个集合
     * @param root1 第一个集合的根节点
     * @param root2 第二个集合的根节点
     */
    void union_sets(int root1, int root2);
};

// ------------------------------------
// 构造函数
// ------------------------------------
inline DisjointSet::DisjointSet(int s) : size(s)
{
    parent = new int[size + 1];
    for (int i = 1; i <= size; ++i) {
        parent[i] = -1;  // 开始时，每个元素都是一个独立的集合
    }
}

// ------------------------------------
// 析构函数
// ------------------------------------
inline DisjointSet::~DisjointSet() { delete[] parent; }

// ------------------------------------
// 查找操作 (带路径压缩)
// ------------------------------------
inline int DisjointSet::find(int x)
{
    if (parent[x] < 0) {
        return x;  // 如果当前节点是根节点，直接返回
    }
    return parent[x] = find(parent[x]);  // 路径压缩：将路径上所有节点直接连接到根节点
}

// ------------------------------------
// 合并操作 (按树的大小合并)
// ------------------------------------
inline void DisjointSet::union_sets(int x, int y)
{
    int root1 = find(x);
    int root2 = find(y);

    if (root1 == root2) {
        return;  // 如果两个根节点相同，则已在同一集合中
    }

    // 将节点数较少的树合并到节点数较多的树中
    if (parent[root1] > parent[root2]) {
        parent[root2] += parent[root1];  // 更新根节点的大小
        parent[root1] = root2;           // 将 root1 的父节点设为 root2
    } else {
        parent[root1] += parent[root2];  // 更新根节点的大小
        parent[root2] = root1;           // 将 root2 的父节点设为 root1
    }
}

}  // namespace datastructures

#endif  // DISJOINT_SET_H