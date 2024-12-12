#ifndef SEQLIST_H
#define SEQLIST_H

#define INITSIZE 100
#include "Exceptions.h"

// 定义数据结构命名空间
namespace datastructures
{

// 顺序表类
template <class elemType>
class SeqList
{
   private:
    elemType *elem;      // 顺序表存储数组，存放实际的数据元素
    int len;             // 顺序表中的元素个数，亦称表的长度
    int maxSize;         // 顺序表最大可能的长度
    void doubleSpace();  // 扩展容量

   public:
    SeqList(int size = INITSIZE);                     // 构造函数，初始化顺序表
    bool isEmpty() const { return (len == 0); }       // 表为空返回true，否则返回false
    bool isFull() const { return (len == maxSize); }  // 表满返回true，否则返回false
    int length() const { return len; }                // 表的长度，即表中实际存储的元素个数
    elemType get(int i) const;                        // 返回第i个元素的值
    int find(const elemType &e) const;  // 查找元素e，返回值是e的元素的序号，没有则返回0

    void insert(
        int i,
        const elemType &e);  // 在第i个位置插入新的元素（值为e），使原来的第i个元素成为第i+1个元素
    void remove(
        int i,
        elemType
            &e);  // 若第i个元素存在，删除并将其存入e指向的空间，使原来的第i+1个元素成为第i个元素

    void clear() { len = 0; }  // 清空顺序表
    ~SeqList();                // 析构函数，释放表占用的动态数组
};

/**
 * 构造函数
 * 用于初始化一个顺序表，设置最大容量为size，默认为INITSIZE。
 * 如果size小于等于0，抛出IllegalSize异常。
 * @param size 初始化的最大容量
 */
template <class elemType>
SeqList<elemType>::SeqList(int size)
{
    elem = new elemType[size];
    if (!elem) {
        throw IllegalSize();
    }
    maxSize = size - 1;  // 0下标位置不放元素，用于查找时做哨兵位
    len = 0;
}

/**
 * 析构函数
 * 用于释放动态分配的内存
 */
template <class elemType>
SeqList<elemType>::~SeqList()
{
    delete[] elem;
}

/**
 * 扩展顺序表容量
 * 将当前容量扩展为原来的两倍
 */
template <class elemType>
void SeqList<elemType>::doubleSpace()
{
    elemType *tmp = new elemType[2 * maxSize + 1];
    if (!tmp) {
        throw IllegalSize();
    }

    // 拷贝现有数据到新空间
    for (int i = 1; i <= len; i++) {
        tmp[i] = elem[i];
    }

    delete[] elem;          // 释放原内存
    elem = tmp;             // 更新指针
    maxSize = 2 * maxSize;  // 更新容量
}

/**
 * 获取指定位置的元素
 * 如果位置无效，抛出OutOfBound异常
 * @param i 元素的位置
 * @return 返回该位置的元素
 */
template <class elemType>
elemType SeqList<elemType>::get(int i) const
{
    if (i < 1 || i > len) throw OutOfBound();
    return elem[i];
}

/**
 * 查找元素e的第一次出现位置
 * @param e 要查找的元素
 * @return 元素位置，如果不存在返回0
 */
template <class elemType>
int SeqList<elemType>::find(const elemType &e) const
{
    elem[0] = e;  // 设置哨兵位
    int i = len;
    while (elem[i] != e) {
        --i;
    }
    return i;
}

/**
 * 插入元素e到位置i
 * 如果顺序表已满，自动扩展容量
 * @param i 插入位置
 * @param e 插入的元素
 */
template <class elemType>
void SeqList<elemType>::insert(int i, const elemType &e)
{
    if (i < 1 || i > len + 1) throw OutOfBound();  // 插入位置越界
    if (len == maxSize)                            // 容量已满时扩展
        doubleSpace();

    for (int j = len + 1; j > i; --j) {
        elem[j] = elem[j - 1];
    }
    elem[i] = e;
    ++len;
}

/**
 * 删除位置i的元素，并将其存入e中
 * @param i 要删除的元素位置
 * @param e 存储被删除的元素
 */
template <class elemType>
void SeqList<elemType>::remove(int i, elemType &e)
{
    if (i < 1 || i > len) throw OutOfBound();
    e = elem[i];
    for (int j = i; j < len; ++j) {
        elem[j] = elem[j + 1];
    }
    --len;
}

}  // namespace datastructures

#endif  // SEQLIST_H
