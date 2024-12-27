# 第 2 章 线性表

- [第 2 章 线性表](#第-2-章-线性表)
  - [2.1 线性表的定义及 ADT](#21-线性表的定义及-adt)
  - [2.2 线性表的顺序存储结构](#22-线性表的顺序存储结构)
    - [2.2.1 顺序表](#221-顺序表)
    - [2.2.2 顺序表基本操作的实现](#222-顺序表基本操作的实现)
  - [2.3 线性表的链式存储结构](#23-线性表的链式存储结构)
    - [2.3.1 单链表](#231-单链表)
    - [2.3.2 单链表基本操作的实现](#232-单链表基本操作的实现)
      - [插入操作：](#插入操作)
      - [删除操作：](#删除操作)
      - [逆置操作：](#逆置操作)
    - [2.3.3 单向循环链表](#233-单向循环链表)
    - [2.3.4 双链表、双向循环链表](#234-双链表双向循环链表)
  - [2.4 线性表的应用](#24-线性表的应用)
    - [2.4.1 一元多项式的加法](#241-一元多项式的加法)
    - [2.4.2 字符串的存储和实现](#242-字符串的存储和实现)
    - [2.4.3 稀疏矩阵](#243-稀疏矩阵)
  - [2.5 小结](#25-小结)
  - [2.6 习题](#26-习题)
    - [书本习题](#书本习题)
      - [问题 1](#问题-1)
      - [问题 2](#问题-2)
      - [问题 3](#问题-3)
      - [问题 4](#问题-4)
      - [问题 5](#问题-5)
      - [问题 6](#问题-6)
      - [问题 7](#问题-7)
      - [问题 8](#问题-8)
      - [问题 9](#问题-9)
      - [问题 10](#问题-10)
      - [问题 11](#问题-11)
      - [问题 12](#问题-12)
      - [问题 13](#问题-13)
      - [问题 14](#问题-14)
      - [问题 15](#问题-15)
      - [问题 16](#问题-16)
      - [问题 17 `*`](#问题-17-)
      - [问题 18](#问题-18)
      - [问题 19](#问题-19)
      - [问题 20 `*`](#问题-20-)
      - [问题 21 `**`](#问题-21-)
    - [PPT](#ppt)
    - [ACM-OJ](#acm-oj)
      - [2416 - 空闲链表](#2416---空闲链表)
      - [2417 - 数字统计](#2417---数字统计)
      - [11005](#11005)

## 2.1 线性表的定义及 ADT

线性表是具有相同数据类型的 n 个数据元素的有限序列。其中：

- 线性表的规模或长度是指表中元素的个数
- 空表是指长度为 0 的线性表
- 线性表中的位置是从 1 开始计数的

抽象数据类型（ADT）是一个数学模型，它包含了数据对象、数据对象之间的关系以及对数据的基本操作。线性表的 ADT 定义了一组基本操作，这些操作与具体的存储结构实现无关（无论是顺序存储还是链式存储）。

基本操作可以分为 5 类：

1. 构造类：initialize - 初始化线性表
2. 属性类：isEmpty, length, isFull, get, find - 获取线性表的基本信息
3. 数据操纵类：insert, remove, clear - 修改线性表的内容
4. 遍历类：遍历线性表中的所有元素
5. 典型应用类：针对特定应用场景的操作

## 2.2 线性表的顺序存储结构

数据结构在内存中的存储通常有两种方式：顺序存储和链式存储。顺序存储是指数据元素存储在地址连续的存储单元中，使得逻辑上相邻的元素在物理位置上也相邻。

### 2.2.1 顺序表

顺序表是线性表的顺序存储实现，基于数组实现。在我们的实现中：

- 数组下标 0（`elem[0]`）用作特殊用途，不存放顺序表的元素
- 从下标 1 开始连续存储元素，即`elem[n]`存储顺序表的第 n 个元素
- maxSize 表示存储空间的大小（最多能存储的元素数）
- len 表示当前实际存储的元素个数
- initSize 表示初始分配的存储空间大小

### 2.2.2 顺序表基本操作的实现

1. 查找操作

- `elem[0]`用作哨兵单元，从尾向头反向查找
- 时间复杂度：$O(n)$
- 使用哨兵可以简化边界条件的判断

```cpp
template <class elemType>
int SeqList<elemType>::count(const elemType &e) const {
    int count = 0;
    for (int i = 1; i <= len; i++) {
        if (elem[i] == e) count++;
    }
    return count;
}
```

2. 插入操作 insert

- 时间复杂度：平均 $O(n)$
- 当空间不足时，需要调用 doubleSpace()扩展空间
- doubleSpace()的实现：
  1. 分配一个大小为原来两倍的新数组
  2. 将原数组的元素复制到新数组
  3. 释放原数组空间
  4. 更新 maxSize
- 插入时需要注意移动元素的顺序：从后向前移动，避免覆盖

3. 删除操作 remove

- 时间复杂度：平均 $O(n)$
- 删除时需要注意移动元素的顺序：从前向后移动
- 删除最后一个元素后直接 len--，无需其他操作

## 2.3 线性表的链式存储结构

分析顺序表的主要弊端：

- 插入/删除需要移动大量元素
- 需要预先分配存储空间
- 空间可能浪费或不足

链表通过链式存储解决这些问题：

- 每个元素放在独立的存储单元（结点）中
- 结点间通过指针连接，表示逻辑关系
- 动态分配内存，按需扩展

结点的组成：

- 数据域：存储元素值
- 指针域：存储下一个结点的地址

链表的特点：

- 首结点：第一个存放数据的结点
- 头结点：在首结点之前的特殊结点，不存储数据
- 头指针（head）：指向头结点

头结点的作用：

- 统一操作：使得在首结点位置的插入/删除操作与其他位置保持一致
- 简化边界处理：避免对空表的特殊处理

示例：头结点的好处

1. 没有头结点的情况：

```cpp
// 在链表头部插入结点
Node* newNode = new Node('Z');
newNode->next = head;
head = newNode;  // 需要更新头指针

// 在其他位置插入结点
Node* p = head;
while (p != NULL && p->data != 'B') {
    p = p->next;
}
Node* newNode = new Node('X');
newNode->next = p->next;
p->next = newNode;
```

2. 有头结点的情况：

```cpp
// 在链表头部插入结点
Node* newNode = new Node('Z');
newNode->next = head->next;
head->next = newNode;  // 操作统一

// 在其他位置插入结点
Node* p = head;
while (p->next != NULL && p->next->data != 'B') {
    p = p->next;
}
Node* newNode = new Node('X');
newNode->next = p->next;
p->next = newNode;
```

链表的分类：

1. 单链表：每个结点一个 next 指针
2. 循环链表：最后一个结点的 next 指向头结点
3. 双链表：每个结点有 prior 和 next 两个指针
4. 双向循环链表：结合了循环链表和双链表的特点

### 2.3.1 单链表

单链表的基本结构：

```cpp
template <class elemType>
class Node {
    friend class LinkList<elemType>;
private:
    elemType data;
    Node* next;
public:
    Node() : next(nullptr) {}
    Node(const elemType& e, Node* n = nullptr) : data(e), next(n) {}
};
```

### 2.3.2 单链表基本操作的实现

#### 插入操作：

- 基本原则：先设置新结点的 next，再修改前驱结点的 next
- 时间复杂度：$O(n)$，但在表头插入为 $O(1)$

#### 删除操作：

- 基本原则：先保存待删除结点的 next，再释放结点
- 注意内存管理：使用 delete 释放结点

顺序表 vs 单链表 操作时间复杂度对比：

| 操作       | 顺序表（平均） | 单链表（平均） |
| ---------- | -------------- | -------------- |
| 按索引查找 | $O(1)$         | $O(n)$         |
| 按值查找   | $O(n)$         | $O(n)$         |
| 插入       | $O(n)$         | $O(n)$         |
| 删除       | $O(n)$         | $O(n)$         |
| 头部插入   | $O(n)$         | $O(1)$         |
| 头部删除   | $O(n)$         | $O(1)$         |

#### 逆置操作：

代码中的实现是“就地逆置”操作，也就是说过程中不会消耗额外的空间。

其核心思想是从第二个数据结点开始，依次插入到`head`结点后面，完成逆置的操作。

代码如下：

```cpp
template <class elemType>
void LinkList<elemType>::reverse()
{
    Node<elemType> *prev = nullptr;
    Node<elemType> *current = head->next;
    while (current != nullptr) {
        Node<elemType> *nextNode = current->next;
        current->next = prev;
        prev = current;
        current = nextNode;
    }
    head->next = prev;
}
```

在单链表逆置的过程中，我们使用了三个指针：`prev`、`current` 和 `nextNode`。

**初始状态**

在开始反转之前，链表和指针的状态如下：

```mermaid
block-beta

   space:2 head space:2  curr space:4 prev space:2
   columns 13
   block:n1:2
     columns 2
     H
     a1["*"]
   end
   space
   block:n2:2
     columns 2
     1
     a2["*"]
   end
   space
   block:n3:2
     columns 2
     2
     a3["*"]
   end
   space
   block:n4:2
     columns 2
     3
     a4["*"]
   end
   space
   End(("NULL"))

   a1 --> n2
   a2 --> n3
   a3 --> n4
   a4 --> End
   head --> n1
   prev --> End
   curr --> n2
```

- head：指向链表头结点。
- prev：初始化为`nullptr`。
- curr：指向链表的第一个有效结点（1）。

**第一步：反转第一个结点**

1. 记录下一个结点

`Node<elemType> *nextNode = current->next;`

`nextNode` 记录 `curr` 的下一个结点 `2`。

2. 反转当前结点的指针

current->next = prev;

将 1 的 next 指向 prev（nullptr）。

3. 移动指针

prev = current;
current = nextNode;

- prev 移动到 1。
- curr 移动到 2。

```mermaid
block-beta

   space:2 head space:2 prev space:2 curr space:4
   columns 13
   block:n1:2
     columns 2
     H
     a1["*"]
   end
   space
   block:n2:2
     columns 2
     1
     a2["*"]
   end
   space
   block:n3:2
     columns 2
     2
     a3["*"]
   end
   space
   block:n4:2
     columns 2
     3
     a4["*"]
   end
   space
   End(("nul"))

   a1 --> n2
   a2 -- "X" --> End
   a3 --> n4
   a4 --> End
   head --> n1
   prev --> n2
   curr --> n3
```

- 1 的指针已经指向 nullptr。
- prev 移动到 1，curr 移动到 2。

第二步：反转第二个结点

重复以上步骤：

1. 记录下一个结点： nextNode = 3
2. 反转当前结点的指针： 2->next = 1
3. 移动指针：
   - prev 移动到 2
   - curr 移动到 3

```mermaid
block-beta

   space:2 head space:2 prev space:2 curr space:4
   columns 13
   block:n1:2
     columns 2
     H
     a1["*"]
   end
   space
   block:n2:2
     columns 2
     1
     a2["*"]
   end
   space
   block:n3:2
     columns 2
     2
     a3["*"]
   end
   space
   block:n4:2
     columns 2
     3
     a4["*"]
   end
   space
   End(("nul"))

   a1 --> n2
   a2 -- "X" --> End
   a3 --> n2
   a4 --> End
   head --> n1
   prev --> n3
   curr --> n4
```

- 2 的 next 指向 1。

第三步：反转第三个结点

1. 记录下一个结点： nextNode = nullptr
2. 反转当前结点的指针： 3->next = 2
3. 移动指针：
   - prev 移动到 3
   - curr 移动到 nullptr（循环结束）

```mermaid
block-beta

   space:2 head space:2 prev space:2 curr space:4
   columns 13
   block:n1:2
     columns 2
     H
     a1["*"]
   end
   space
   block:n2:2
     columns 2
     1
     a2["*"]
   end
   space
   block:n3:2
     columns 2
     2
     a3["*"]
   end
   space
   block:n4:2
     columns 2
     3
     a4["*"]
   end
   space
   End(("nul"))

   a1 --> n2
   a2 -- "X" --> End
   a3 --> n2
   a4 --> n3
   head --> n1
   prev --> n4
   curr --> End
```

- 3 的 next 指向 2。

更新头指针

最后将 head->next 指向 prev（即新链表的头结点 3）：

head->next = prev;

```mermaid
block-beta

   space:2 head space:2 prev space:2 curr space:4
   columns 13
   block:n1:2
     columns 2
     H
     a1["*"]
   end
   space
   block:n4:2
     columns 2
     3
     a4["*"]
   end
   space
   block:n3:2
     columns 2
     2
     a3["*"]
   end
   space
   block:n2:2
     columns 2
     1
     a2["*"]
   end
   space
   End(("nul"))

   a1 --> n4
   a4 --> n3
   a3 --> n2
   a2 --> End
   head --> n1
```

总结

1. 每次迭代将当前结点的 next 指向前一个结点。
2. 使用 prev 保存已反转的部分链表。
3. 使用 current 遍历链表。
4. 空间复杂度为 ￼，没有使用额外存储。

核心逻辑：

- 依次将 curr->next 指向 prev。
- 移动 prev 和 curr 到下一个结点。

最终，链表被就地逆置，无需额外的空间开销。

### 2.3.3 单向循环链表

单向循环链表的特点：

- 最后一个结点的 next 指向头结点
- 适用于需要循环处理的场景，如约瑟夫环问题

约瑟夫环问题实现：

```cpp
void josephus(int n, int m) {
    if (n <= 0 || m <= 0) return;

    // 建立循环链表
    Node* head = new Node(1);
    Node* tail = head;
    for (int i = 2; i <= n; i++) {
        tail->next = new Node(i);
        tail = tail->next;
    }
    tail->next = head;  // 形成环

    // 模拟报数过程
    Node* current = tail;  // 指向当前结点的前一个结点
    while (current->next != current) {
        // 找到第m个结点的前一个结点
        for (int i = 1; i < m; i++) {
            current = current->next;
        }
        // 删除第m个结点
        Node* temp = current->next;
        current->next = temp->next;
        cout << temp->data << " ";
        delete temp;
    }
    cout << current->data << endl;
    delete current;
}
```

### 2.3.4 双链表、双向循环链表

双链表结点结构：

```cpp
template <class elemType>
class DNode {
    elemType data;
    DNode* prior;
    DNode* next;
public:
    DNode() : prior(nullptr), next(nullptr) {}
    DNode(const elemType& e, DNode* p = nullptr, DNode* n = nullptr)
        : data(e), prior(p), next(n) {}
};
```

双向循环链表特点：

- 头结点的 prior 指向尾结点
- 尾结点的 next 指向头结点
- 便于双向遍历和删除操作

## 2.4 线性表的应用

### 2.4.1 一元多项式的加法

多项式可以用线性表存储，每一项包含系数和指数。实现多项式加法的关键是按指数大小有序存储，便于对应项相加。

### 2.4.2 字符串的存储和实现

字符串的基本概念：

- 空串：长度为 0 的字符串
- 空格串：只包含空格的字符串
- 子串：字符串中任意连续的字符序列
- 主串：包含子串的字符串
- 串的长度：字符个数（不计入结束符）

存储结构选择：

- 顺序存储更适合字符串：单个字符 1 字节，指针 4 字节
- 支持静态存储和动态存储

C++ 字符串处理方式对比：

| 特性     | \<cstring\>    | \<string\>     |
| -------- | -------------- | -------------- |
| 数据类型 | C 风格字符数组 | std::string    |
| 内存管理 | 手动           | 自动           |
| 安全性   | 低             | 高             |
| 功能性   | 基础函数       | 丰富的成员函数 |
| 使用场景 | 底层操作       | 现代 C++开发   |

模式匹配算法：

1. BF（Brute-Force）算法：

   - 简单直观但效率较低
   - 时间复杂度：O(mn)，m 为主串长度，n 为模式串长度

2. KMP 算法：
   - 避免不必要的比较
   - 时间复杂度：O(m+n)
   - 核心是 next 数组的构建

### 2.4.3 稀疏矩阵

稀疏矩阵的特点：

- 非零元素远少于总元素
- 使用三元组存储可以节省空间：

```cpp
struct Triple {
    int row, col;  // 行号、列号
    int value;     // 元素值
};
```

压缩存储的优势：

- 节省存储空间
- 只对非零元素进行运算
- 适合大规模稀疏矩阵运算

## 2.5 小结

线性表是最基本的数据结构之一，主要有两种实现方式：

1. 顺序表：

   - 随机访问快
   - 插入删除需要移动元素
   - 需要预分配空间

2. 链表：
   - 动态分配空间
   - 插入删除只需修改指针
   - 不支持随机访问

选择合适的实现方式需要考虑：

- 数据规模
- 访问模式
- 插入删除频率
- 空间限制

## 2.6 习题

### 书本习题

#### 问题 1

描述一个顺序存储结构需要哪些元素？为什么需要当前元素个数这一要素？

<details>
  <summary>答案</summary>

一个顺序存储结构需要以下元素：

1. 存储空间：用于存放数据元素的连续存储单元（如数组）。
2. 存储容量：表示存储空间的最大容纳元素个数。
3. 当前元素个数：表示当前实际存储的元素个数。

为什么需要当前元素个数？

- 访问与遍历：知道当前元素个数，可以避免访问未初始化或无效的存储单元。
- 插入与删除：在进行插入或删除操作时，需要知道有效数据的范围。
- 边界检查：防止在存储空间已满时进行插入，或在空结构上进行删除操作。

</details>

#### 问题 2

描述一个链式存储结构需要哪些元素？为什么通常不需要当前元素个数这一要素？

<details>
  <summary>答案</summary>

一个链式存储结构需要以下元素：

- 头指针：指向链表的第一个结点，作为链表的入口。
- 数据域：存储结点的数据元素。
- 指针域：存储指向下一个结点的地址（单链表）或前后结点的地址（双链表）。

为什么通常不需要当前元素个数？

- 动态分配：链表结点是动态分配的，结点的个数随时可以变化，不需要提前定义大小。
- 遍历计算：如果需要知道元素个数，可以通过遍历链表进行统计。
- 节省空间：在结点中已经包含了足够的结构信息，存储当前元素个数会显得冗余。

</details>

#### 问题 3

顺序结构已经能很好地存储和处理线性关系，为什么还要用更复杂及费空间的链式结构？

<details>
  <summary>答案</summary>

顺序结构虽然能高效地存储和处理线性关系，但在某些场景下存在局限性，链式结构则能弥补这些不足：

1. 动态内存分配
   - 顺序存储需要预先分配固定大小的连续内存，可能导致内存浪费或空间不足。
   - 链式存储可以根据需求动态分配内存，更加灵活。
2. 高效的插入与删除
   - 顺序结构在中间位置插入或删除元素时，需要大量数据移动。
   - 链式结构只需修改指针即可，插入和删除效率更高。
3. 避免内存碎片
   - 顺序存储需要连续的内存空间，可能导致内存碎片无法利用。
   - 链式存储可以使用零散的内存空间，减少浪费。
4. 灵活扩展
   - 顺序存储一旦分配，大小固定，难以扩展。
   - 链式存储可以随着元素的增加而动态扩展。

因此，在频繁插入、删除操作或内存分布不连续的场景下，链式结构具有显著优势。

</details>

#### 问题 4

试描述链式结构中的头指针、头结点、首结点、末结点、尾结点、尾指针，它们各自的类型是什么？在内存中的存储结构是怎样的？

<details>
  <summary>答案</summary>

链式结构中的关键概念及其类型

1. 头指针（Head Pointer）
   - 类型：指针，指向链表的头结点或首结点。
   - 作用：标记链表的起始位置，用于访问链表。
   - 存储结构：存储头结点或首结点的内存地址。
2. 头结点（Head Node）
   - 类型：结点（结构体），通常不存储有效数据，只包含指针域。
   - 作用：便于链表的统一管理，简化链表的边界操作（例如空链表的处理）。
   - 存储结构：包含一个或多个指针域，指向首结点。
3. 首结点（First Node）
   - 类型：结点（结构体），存储有效数据和指向下一个结点的指针。
   - 作用：链表中第一个存储有效数据的结点。
   - 存储结构：包含数据域和指针域。
4. 末结点（Last Node）
   - 类型：结点（结构体），存储有效数据和指针域。
   - 作用：链表中存储有效数据的最后一个结点。
   - 存储结构：数据域有效，指针域为空（NULL）。
5. 尾结点（Tail Node）
   - 类型：结点（结构体）。
   - 作用：在某些链表中（如循环链表），尾结点指向首结点，形成闭合结构。
   - 存储结构：指针域指向首结点，形成循环。
6. 尾指针（Tail Pointer）
   - 类型：指针，指向末结点或尾结点。
   - 作用：方便在链表末尾进行插入操作。
   - 存储结构：存储末结点或尾结点的地址。

```plaintext


+---------+       +-------------+       +-------------+       +-------------+
|  头结点  | ----> |  数据 | 指针 | ----> |  数据 | 指针  | ----> |  数据 | NULL |
+---------+       +-------------+       +-------------+       +-------------+
     ↑                   ↑                                            ↑
     |                   |                                            |
   头指针               首结点                                        末结点
                                                                      ↑
                                                                    尾指针
```

- 头指针：存储头结点的地址。
- 头结点：指向首结点的指针（若有）。
- 首结点到末结点：每个结点包含数据域和指针域。
- 末结点：指针域为空 (NULL)，或在循环链表中指向首结点。
- 尾指针：指向末结点。

这些元素在不同类型的链表（单链表、双向链表、循环链表）中可能存在细微差异，但其核心功能和内存布局大致相同。

</details>

#### 问题 5

己知表头元素为 c 的单链表在内存中的存储状态如下表所示。

| 内存地址 | 元素数据 | 链接地址 |
| -------- | -------- | -------- |
| 1000H    | a        | 1010H    |
| 1004H    | b        | 10CH     |
| 1008H    | c        | 1000H    |
| 100CH    | d        | NULL     |
| 1010H    | e        | 1004H    |
| 1014H    |          |          |

现将 f 存放于 1014H 处并插入到单链表中，若 f 在逻辑上位于 a 和 e 之间，则 a, e, f 的“链接地址“依次是什么？

<details>
  <summary>答案</summary>

要将元素 f 插入到 a 和 e 之间，需调整相关结点的“链接地址”。

初始状态

- a 的链接地址：1010H（指向 e）
- e 的链接地址：1004H（指向 b）

插入操作

1. 将 a 的链接地址改为指向 f（1014H）。
2. 将 f 的链接地址设为原先 a 指向的地址，即 e（1010H）。

调整后的链接地址

- a：1014H（指向 f）
- f：1010H（指向 e）
- e：1004H（指向 b）

结果

- a → f → e → b → …

因此，a、f、e 的链接地址依次为：

- a → 1014H
- f → 1010H
- e → 1004H

</details>

#### 问题 6

顺序表中如果每个结点除了存储元素的值，还要存储下一个元素的地址。那么这个地址可以是怎样的？是否有必要存在？

<details>
  <summary>答案</summary>

顺序表中存储下一个元素地址

在顺序表中，每个元素在内存中是连续存储的，没有必要存储下一个元素地址。

</details>

#### 问题 7

建立一个工程文件。创建 `seqList.h` 文件，在其中定义 `seqList` 类，并实现各个基本操作成员函数；创建一个 `main.cpp` 文件，定义一个 `main` 函数，设计使用 `seqList` 对象并测试 `segList.h` 中声明的所有基本操作，验证其正确性。

<details>
  <summary>答案</summary>

头文件请参考[SeqList.h](../include/SeqList.h)。示例程序请参考[main.cpp](../src/examples/Chapter2/2-3/main.cpp)。测试程序请参考[test_seqlist.cpp](../test/test_seqlist.cpp)。

</details>

#### 问题 8

改造习题 7 中的 `find` 函数，使函数返回待查数据 `x` 在线性表中出现的次数。

<details>
  <summary>答案</summary>

改造后的 find 函数

```cpp
/**
 * 查找元素 e 在顺序表中出现的次数
 * @param e 要查找的元素
 * @return 元素出现的次数
 */
template <class elemType>
int SeqList<elemType>::find(const elemType &e) const {
    int count = 0;
    for (int i = 1; i <= len; ++i) {
        if (elem[i] == e) {
            ++count;
        }
    }
    return count;
}
```

说明

1. 遍历整个顺序表。
2. 每次遇到`e`，计数器`count`加一。
3. 返回`count`，即元素`e`出现的次数。

</details>

#### 问题 9

如习题 7，设计、测试 `linkList` 类及基本操作函数。

<details>
  <summary>答案</summary>

头文件请参考[LinkList.h](../include/LinkList.h)。测试程序请参考[test_linklist.cpp](../test/test_linklist.cpp)。

</details>

#### 问题 10

分别分析顺序结构和链式结构下所有基本操作的时间复杂度。

<details>
  <summary>答案</summary>

| 操作       | 顺序结构                     | 链式结构                   |
| ---------- | ---------------------------- | -------------------------- |
| 访问       | $O(1)$                       | $O(n)$                     |
| 查找       | $O(n)$                       | $O(n)$                     |
| 插入       | $O(n)$（中间插入需移动元素） | $O(1)$（在指定结点后插入） |
| 删除       | $O(n)$（中间删除需移动元素） | $O(1)$（在指定结点后删除） |
| 按序号插入 | $O(n)$                       | $O(n)$                     |
| 按序号删除 | $O(n)$                       | $O(n)$                     |

</details>

#### 问题 11

设计一个不带头结点的单链表，分析其插入、删除操作和在带头结点的单链表中进行插入、删除操作有什么不同？

<details>
  <summary>答案</summary>

有头结点与无头结点的单链表插入、删除对比

有头结点的插入操作

```cpp
template <class elemType>
void LinkList<elemType>::insert(int i, const elemType &e) {
    if (i < 0) throw OutOfBound();

    Node<elemType> *p = head; // 从头结点开始
    int idx = 0;
    while (p != nullptr && idx < i) {
        p = p->next;
        idx++;
    }
    if (p == nullptr) throw OutOfBound();

    Node<elemType> *newNode = new Node<elemType>(e, p->next);
    p->next = newNode;
}
```

无头结点的插入操作

```cpp
template <class elemType>
void LinkList<elemType>::insert(int i, const elemType &e) {
    if (i < 0) throw OutOfBound();

    if (i == 0) { // 特殊处理头结点插入
        Node<elemType> *newNode = new Node<elemType>(e, head);
        head = newNode;
        return;
    }

    Node<elemType> *p = head;
    int idx = 0;
    while (p != nullptr && idx < i - 1) {
        p = p->next;
        idx++;
    }
    if (p == nullptr) throw OutOfBound();

    Node<elemType> *newNode = new Node<elemType>(e, p->next);
    p->next = newNode;
}
```

有头结点的删除操作

```cpp
template <class elemType>
void LinkList<elemType>::remove(int i, elemType &e) {
    if (i < 0) throw OutOfBound();

    Node<elemType> *p = head; // 从头结点开始
    int idx = 0;
    while (p->next != nullptr && idx < i) {
        p = p->next;
        idx++;
    }
    if (p->next == nullptr) throw OutOfBound();

    Node<elemType> *q = p->next;
    p->next = q->next;
    e = q->data;
    delete q;
}
```

无头结点的删除操作

```cpp
template <class elemType>
void LinkList<elemType>::remove(int i, elemType &e) {
    if (i < 0 || head == nullptr) throw OutOfBound();

    if (i == 0) { // 特殊处理头结点删除
        Node<elemType> *q = head;
        e = q->data;
        head = head->next;
        delete q;
        return;
    }

    Node<elemType> *p = head;
    int idx = 0;
    while (p->next != nullptr && idx < i - 1) {
        p = p->next;
        idx++;
    }
    if (p->next == nullptr) throw OutOfBound();

    Node<elemType> *q = p->next;
    p->next = q->next;
    e = q->data;
    delete q;
}
```

区别总结

TODO: 调整格式 markdown 表格

操作 有头结点 无头结点
插入 头结点统一入口，逻辑简洁 需特殊处理表头插入
删除 头结点统一入口，逻辑简洁 需特殊处理表头删除

- 有头结点：统一处理逻辑，避免头结点的特殊情况。
- 无头结点：插入、删除头结点时需单独处理，逻辑稍复杂。

</details>

#### 问题 12

完整地写出双链表相关定义及实现。

<details>
  <summary>答案</summary>

```cpp

template <class elemType>
struct DNode {
    elemType data;          // 数据域
    DNode<elemType>* prev;  // 指向前驱结点的指针
    DNode<elemType>* next;  // 指向后继结点的指针

    DNode(const elemType& e, DNode* p = nullptr, DNode* n = nullptr) : data(e), prev(p), next(n) {}
};

template <class elemType>
class DLinkedList
{
   private:
    DNode<elemType>* head;  // 头指针
    DNode<elemType>* tail;  // 尾指针
    int length;             // 链表长度

   public:
    DLinkedList();   // 构造函数
    ~DLinkedList();  // 析构函数

    void insert(int i, const elemType& e);  // 插入元素
    void remove(int i, elemType& e);        // 删除元素
    int find(const elemType& e) const;      // 查找元素
    void display() const;                   // 显示链表
    int size() const;                       // 获取链表长度
};

template <class elemType>
DLinkedList<elemType>::DLinkedList()
{
    head = new DNode<elemType>(elemType());  // 哑头结点
    tail = head;
    length = 0;
}

template <class elemType>
DLinkedList<elemType>::~DLinkedList()
{
    while (head != nullptr) {
        DNode<elemType>* tmp = head;
        head = head->next;
        delete tmp;
    }
}

template <class elemType>
void DLinkedList<elemType>::insert(int i, const elemType& e)
{
    if (i < 0 || i > length) throw OutOfBound();

    DNode<elemType>* p = head;
    for (int idx = 0; idx < i; ++idx) {
        p = p->next;
    }

    DNode<elemType>* newNode = new DNode<elemType>(e, p, p->next);
    if (p->next != nullptr) {
        p->next->prev = newNode;
    }
    p->next = newNode;

    if (newNode->next == nullptr) {
        tail = newNode;
    }

    ++length;
}

template <class elemType>
void DLinkedList<elemType>::remove(int i, elemType& e)
{
    if (i < 0 || i >= length) throw OutOfBound();

    DNode<elemType>* p = head->next;
    for (int idx = 0; idx < i; ++idx) {
        p = p->next;
    }

    e = p->data;
    if (p->prev != nullptr) {
        p->prev->next = p->next;
    }
    if (p->next != nullptr) {
        p->next->prev = p->prev;
    }
    if (p == tail) {
        tail = p->prev;
    }

    delete p;
    --length;
}

template <class elemType>
int DLinkedList<elemType>::find(const elemType& e) const
{
    DNode<elemType>* p = head->next;
    int idx = 0;

    while (p != nullptr) {
        if (p->data == e) {
            return idx;
        }
        p = p->next;
        ++idx;
    }

    return -1;  // 未找到
}

template <class elemType>
void DLinkedList<elemType>::display() const
{
    DNode<elemType>* p = head->next;

    while (p != nullptr) {
        std::cout << p->data << " ";
        p = p->next;
    }
    std::cout << std::endl;
}

template <class elemType>
int DLinkedList<elemType>::size() const
{
    return length;
}

int main()
{
    DLinkedList<int> list;

    // 插入元素
    list.insert(0, 10);
    list.insert(1, 20);
    list.insert(2, 30);

    // 显示链表
    list.display();  // 输出: 10 20 30

    // 删除元素
    int removed;
    list.remove(1, removed);
    std::cout << "Removed: " << removed << std::endl;  // 输出: Removed: 20

    // 显示链表
    list.display();  // 输出: 10 30

    // 查找元素
    std::cout << "Index of 30: " << list.find(30) << std::endl;  // 输出: Index of 30: 1

    return 0;
}
```

总结

- 双链表结点：包含前驱指针 prev 和后继指针 next。
- 插入：双向指针调整，处理前后结点关系。
- 删除：确保断开被删除结点的前后连接。
- 优点：支持双向遍历，插入和删除更加灵活。

</details>

#### 问题 13

n 个人围成一个圈，从 1、2、3 开始报数。当报到 m 时，第 m 个人出列，并从原来的第 m+1 人重新开始 1、2、3 报数。如此循环，直到圈中只剩下一个人。这个圈称作约瑟夫环。试用单向循环链表实现该游戏，并输出最后剩下的那人的姓名。

<details>
  <summary>答案</summary>

```cpp
#include <iostream>
#include <string>

/**
 * 单向循环链表的结点定义
 */
struct Node {
    std::string name;
    Node* next;

    Node(const std::string& n) : name(n), next(nullptr) {}
};

/**
 * 构建约瑟夫环
 * @param n 人数
 * @return 返回头指针
 */
Node* createJosephusCircle(int n) {
    if (n <= 0) return nullptr;

    Node* head = new Node("Person 1");
    Node* prev = head;

    for (int i = 2; i <= n; ++i) {
        Node* newNode = new Node("Person " + std::to_string(i));
        prev->next = newNode;
        prev = newNode;
    }

    prev->next = head; // 尾结点指向头结点，形成循环链表

    return head;
}

/**
 * 约瑟夫环算法
 * @param head 链表头指针
 * @param m 每次报数到 m 出列
 * @return 返回最后剩下的人的姓名
 */
std::string josephusGame(Node* head, int m) {
    if (!head || m <= 0) return "";

    Node* p = head;
    while (p->next != p) { // 当链表中只剩一个结点时结束
        // 找到第 m-1 个结点
        for (int i = 1; i < m - 1; ++i) {
            p = p->next;
        }

        // 删除第 m 个结点
        Node* toDelete = p->next;
        p->next = toDelete->next;
        std::cout << toDelete->name << " 出列\n";
        delete toDelete;

        // 移动到下一个结点
        p = p->next;
    }

    std::string winner = p->name;
    delete p; // 清理最后一个结点
    return winner;
}

/**
 * 主函数
 */
int main() {
    int n, m;
    std::cout << "请输入参与游戏的人数 n: ";
    std::cin >> n;
    std::cout << "请输入每次报数的数字 m: ";
    std::cin >> m;

    Node* head = createJosephusCircle(n);
    std::string winner = josephusGame(head, m);

    std::cout << "最后剩下的人是: " << winner << std::endl;
    return 0;
}
```

程序说明：

1. 创建循环链表
   - 使用 createJosephusCircle 函数创建一个包含 n 个人的单向循环链表。
2. 约瑟夫环算法
   - 每次从当前结点开始，报数到第 m 个结点，将其移除。
   - 重复此过程，直到只剩下一个结点。
3. 主函数
   - 用户输入人数 n 和报数 m。
   - 输出被淘汰的顺序以及最后剩下的人的姓名。

示例输入/输出

输入：

```plaintext
请输入参与游戏的人数 n: 5
请输入每次报数的数字 m: 3
```

输出：

```plaintext
Person 3 出列
Person 1 出列
Person 5 出列
Person 2 出列
最后剩下的人是: Person 4
```

</details>

#### 问题 14

n 个元素存储在一个顺序表中，试用最小的空间代价实现就地逆置。如原来的顺序是`agrtuy`，逆置后的顺序为`yutrga`。

<details>
  <summary>答案</summary>

```cpp
template <class elemType>
void SeqList<elemType>::reverse()
{
    int left = 1;       // 从第一个元素开始
    int right = len;    // 从最后一个元素开始

    while (left < right) {
        // 交换 elem[left] 和 elem[right]
        elemType temp = elem[left];
        elem[left] = elem[right];
        elem[right] = temp;

        ++left;
        --right;
    }
}
```

</details>

#### 问题 15

已知两个长度分别为 `m` 和 `n` 的升序链表，将它们合并一个长度为 `m+n` 的降序链表。

<details>
  <summary>答案</summary>

TODO

</details>

#### 问题 16

利用链式结构分别实现集合运算$C=A\cup B$, $C=A-B$并分析其时间复杂度。要求运算结束后在内存中的 A、B 两个集合中元素不变。

<details>
  <summary>答案</summary>

TODO

</details>

#### 问题 17 `*`

受数据类型限制，计算机存储整数的范围是有限的。在实际应用中，如果需要用到很大或很小的整数，可以采用以下方法解决：建立一个单链表，每个结点存储一个 0~9 的数字字符，头结点中存储 0、1 分别表示正数和负数。由于单链表中结点是逐个动态申消的，因此原则上该单链表可以存储任意大小的醛数。如+357 可在单链表中作如下表示：

```mermaid
block-beta

   space:2 head space:2
   block:n1:2
     columns 2
     0
     a1["*"]
   end
   space
   block:n2:2
     columns 2
     7
     a2["*"]
   end
   space
   block:n3:2
     columns 2
     5
     a3["*"]
   end
   space
   block:n4:2
     columns 2
     3
     a4["^"]
   end
   space

   a1 --> n2
   a2 --> n3
   a3 --> n4
   head --> n1
```

试编写完成两个大整数加法的程序。

<details>
  <summary>答案</summary>

TODO

</details>

#### 问题 18

完成两个一元多项式的乘法并在`main`函数中加以测试。

<details>
  <summary>答案</summary>

我们已经在[2-7 示例程序](../src/examples/Chapter2/2-7/main.cpp)中实现了一元多项式的加法，下面是给予该代码实现的一元多项式乘法。

```cpp
datastructures::LinkList<Item> multiplyExpression(const datastructures::LinkList<Item> &expr1,
                                                  const datastructures::LinkList<Item> &expr2) {
    datastructures::LinkList<Item> result;

    for (int i = 0; i < expr1.length(); i++) {
        Item item1 = expr1.get(i);
        for (int j = 0; j < expr2.length(); j++) {
            Item item2 = expr2.get(j);

            // 计算乘积
            Item product = {item1.coef * item2.coef, item1.exp + item2.exp};

            if (product.coef == 0) {
                continue; // 系数为0，跳过
            }

            // 有序插入到结果链表中
            bool inserted = false;
            for (int k = 0; k < result.length(); k++) {
                Item current = result.get(k);

                if (current.exp == product.exp) {
                    // 指数相同，合并系数
                    result.get(k).coef += product.coef;
                    if (result.get(k).coef == 0) {
                        result.remove(k, current); // 系数为0，删除该项
                    }
                    inserted = true;
                    break;
                } else if (current.exp < product.exp) {
                    // 按指数降序插入
                    result.insert(k, product);
                    inserted = true;
                    break;
                }
            }

            if (!inserted) {
                // 如果没有插入，说明指数最小，插入末尾
                result.insert(result.length(), product);
            }
        }
    }

    return result;
}
```

</details>

#### 问题 19

利用[`2.4.3`节](#243-稀疏矩阵)方法在内存中存储稀疏矩阵，试编写算法实现稀疏矩阵的逆置运算。

<details>
  <summary>答案</summary>

具体代码实现请参考[稀疏矩阵源代码](../src/examples/Chapter2/sparse-matrix/main.cpp)中的`transpose`函数。

</details>

#### 问题 20 `*`

利用与 19 题同样的方法存储稀疏矩阵，试编写算法实现两个稀疏矩阵的乘法运算。

<details>
  <summary>答案</summary>

具体代码实现请参考[稀疏矩阵源代码](../src/examples/Chapter2/sparse-matrix/main.cpp)中的`multiply`函数。

</details>

#### 问题 21 `**`

讨论如何改进 KMP 算法中求失配函数 next 的算法，对该方法进行编程实现并讨论其
时间复杂度。

<details>
  <summary>答案</summary>

TODO

</details>

### PPT

1. 线性表若采用链式存储结构保存，则要求内存中可用存储单元的地址（D）

   - A. 必须是连续的
   - B. 部分地址必须是连续的
   - C. 一定是不连续的
   - D. 连续或不连续都可以

2. 顺序表和链表特性对比：
   顺序表特性：

   - 逻辑相邻元素物理位置相邻
   - 支持随机存取
   - 支持顺序存取

   链表特性：

   - 不必事先估计存储空间
   - 空间与元素个数成正比
   - 插入删除不需要移动元素
   - 支持顺序存取

3. 查找单链表中间结点的方法：

   - 已知长度 len：返回第⌈len/2⌉个结点
   - 未知长度：
     1. 遍历得到长度后计算
     2. 快慢指针法：快指针每次走两步，慢指针每次走一步

4. 有序单链表操作：

   ```cpp
   // 统计大于x的不同数的个数
   int countGreater(const LinkList<int>& list, int x) {
       int count = 0;
       int last = x;  // 记录上一个计数的数
       Node* p = list.head->next;
       while (p != nullptr) {
           if (p->data > x && p->data != last) {
               count++;
               last = p->data;
           }
           p = p->next;
       }
       return count;
   }

   // 将小于x的数按递减序重排
   void rearrangeLesser(LinkList<int>& list, int x) {
       Node* p = list.head->next;
       Node* smaller = nullptr;  // 小于x的结点链表
       Node* rest = nullptr;     // 大于等于x的结点链表

       while (p != nullptr) {
           Node* next = p->next;
           if (p->data < x) {
               p->next = smaller;
               smaller = p;
           } else {
               p->next = rest;
               rest = p;
           }
           p = next;
       }

       // 重新连接链表
       p = smaller;
       while (p != nullptr && p->next != nullptr) {
           Node* max = p;
           Node* q = p->next;
           while (q != nullptr) {
               if (q->data > max->data) max = q;
               q = q->next;
           }
           // 交换数据
           int temp = p->data;
           p->data = max->data;
           max->data = temp;
           p = p->next;
       }

       // 连接两部分
       list.head->next = smaller;
       while (smaller != nullptr && smaller->next != nullptr)
           smaller = smaller->next;
       if (smaller != nullptr)
           smaller->next = rest;
       else
           list.head->next = rest;
   }
   ```

5. 删除重复元素的实现：

   ```cpp
   // 顺序表实现
   template <class elemType>
   void SeqList<elemType>::removeDuplicates() {
       if (len <= 1) return;
       int newLen = 1;
       for (int i = 2; i <= len; i++) {
           bool isDuplicate = false;
           for (int j = 1; j <= newLen; j++) {
               if (elem[i] == elem[j]) {
                   isDuplicate = true;
                   break;
               }
           }
           if (!isDuplicate) {
               newLen++;
               elem[newLen] = elem[i];
           }
       }
       len = newLen;
   }

   // 链表实现
   template <class elemType>
   void LinkList<elemType>::removeDuplicates() {
       if (head->next == nullptr) return;
       Node<elemType>* p = head->next;
       while (p != nullptr) {
           Node<elemType>* q = p;
           while (q->next != nullptr) {
               if (q->next->data == p->data) {
                   Node<elemType>* temp = q->next;
                   q->next = q->next->next;
                   delete temp;
               } else {
                   q = q->next;
               }
           }
           p = p->next;
       }
   }
   ```

### ACM-OJ

#### 2416 - 空闲链表

请参考[2416 题解](../src/homework/2416/main.cpp)文件。

#### 2417 - 数字统计

使用本章所学的`LinkList`类的做题思路也很清晰，请参考[2417 题解](../src/homework/2417/main.cpp)文件。

当然也可以使用哈希表统计数字出现的最大频率：

```cpp
#include <iostream>
#include <unordered_map>

int main() {
    int n;
    std::cin >> n;

    std::unordered_map<long long, int> freqMap;
    int maxFreq = 0;

    for (int i = 0; i < n; i++) {
        long long num;
        std::cin >> num;
        freqMap[num]++;
        maxFreq = std::max(maxFreq, freqMap[num]);
    }

    std::cout << maxFreq << std::endl;
    return 0;
}
```

#### 11005

二维数组，分别按照数独的规则对行、列、`3*3`九宫格进行检查，[11005 题解](../src/homework/11005/main.cpp)
