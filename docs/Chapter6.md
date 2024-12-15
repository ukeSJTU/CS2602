# 第 6 章 查找

## 6.1 静态查找技术

### 6.1.1 顺序查找

### 6.1.2 折半查找

### 6.1.3 插值查找

### 6.1.4 分块查找

## 6.2 二叉查找树

### 6.2.1 二叉查找树的定义

### 6.2.2 基本操作实现

### 6.2.3 顺序统计

## 6.3 平衡二叉查找树

### 6.3.1 插入操作

### 6.3.2 删除操作

### 6.3.3 最大高度

## 6.4 红黑树

### 6.4.1 插入操作

### 6.4.2 删除操作

## 6.5 B 树和 B+树

### 6.5.1 B 树

### 6.5.2 B 树的查找

### 6.5.3 B 树的插入

### 6.5.4 B 树的删除

### 6.5.5 B+树

## 6.6 哈希方法

### 6.6.1 常用的哈希函数

### 6.6.2 线性探测法

### 6.6.3 二次探测法

### 6.6.4 链地址法

## 6.7 小结

## 6.8 习题

### 书本

### PPT

### ACM-OJ

#### 11051

TLE 方法：

```cpp
#include <iostream>

#include "LinkList.h"

int main()
{
    int n, m, t;
    std::cin >> n;
    datastructures::LinkList<int> list;
    for (int i = 0; i < n; i++) {
        std::cin >> t;
        list.insert(i, t);
    }

    int step_cnt = 0;
    std::cin >> m;
    for (int i = 0; i < m; i++) {
        std::cin >> t;
        for (int j = 0; j < list.length(); j++) {
            step_cnt++;
            int elem = list.get(j);
            if (elem == t) {
                // 把找到的指定节点移动到链表的第一个位置
                // 删除，然后在最一开始添加
                int tmp;
                list.remove(j, tmp);
                list.insert(0, tmp);
                break;
            }
        }
        // std::cout << "Finding " << t << " costs " << step_cnt << " steps." << std::endl;
    }

    std::cout << step_cnt << std::endl;
    return 0;
}
```
