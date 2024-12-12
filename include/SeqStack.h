#ifndef SEQSTACK_H
#define SEQSTACK_H

#include "Exceptions.h"

namespace datastructures
{

/**
 * @brief 顺序栈类模板
 *
 * 使用动态数组实现的顺序栈，支持自动扩容。
 *
 * @tparam elemType 栈中元素类型
 */
template <class elemType>
class SeqStack
{
   private:
    elemType *elem;      ///< 栈存储数组，存放实际的数据元素
    int top_p;           ///< 栈顶下标
    int maxSize;         ///< 当前数组的最大容量
    void doubleSpace();  ///< 将存储空间扩容为原来的两倍

   public:
    /**
     * @brief 构造函数
     *
     * 初始化一个给定容量的顺序栈。
     *
     * @param initSize 栈的初始容量，默认为100
     * @exception IllegalSize 如果分配内存失败则抛出该异常
     */
    SeqStack(int initSize = 100);

    /**
     * @brief 判断栈是否为空
     *
     * @return 若栈为空返回true，否则返回false
     */
    bool isEmpty() { return (top_p == -1); }

    /**
     * @brief 判断栈是否已满
     *
     * @return 若栈已满返回true，否则返回false
     */
    bool isFull() { return (top_p == maxSize - 1); }

    /**
     * @brief 获取栈顶元素
     *
     * @return 返回栈顶元素的拷贝
     * @exception OutOfBound 如果栈为空则抛出该异常
     */
    elemType top();

    /**
     * @brief 向栈顶压入新元素
     *
     * 如果栈已满则自动扩容。
     *
     * @param e 要入栈的元素
     */
    void push(const elemType &e);

    /**
     * @brief 弹出栈顶元素
     *
     * 从栈中移除并丢弃栈顶元素。
     *
     * @exception OutOfBound 如果栈为空则抛出该异常
     */
    void pop();

    /**
     * @brief 析构函数
     *
     * 释放栈内存。
     */
    ~SeqStack() { delete[] elem; }
};

template <class elemType>
SeqStack<elemType>::SeqStack(int initSize)
{
    elem = new elemType[initSize];
    if (!elem) {
        throw IllegalSize();
    }

    maxSize = initSize;
    top_p = -1;
}

/**
 * @brief 将栈的存储空间扩容一倍
 *
 * 分配两倍容量的新数组，将原有数据拷贝到新数组中，然后释放旧数组。
 *
 * @exception IllegalSize 如果内存分配失败则抛出该异常
 */
template <class elemType>
void SeqStack<elemType>::doubleSpace()
{
    elemType *tmp = elem;
    elem = new elemType[2 * maxSize];
    if (!elem) {
        throw IllegalSize();
    }

    for (int i = 0; i <= top_p; i++) {
        elem[i] = tmp[i];
    }

    maxSize *= 2;
    delete[] tmp;
}

template <class elemType>
elemType SeqStack<elemType>::top()
{
    if (isEmpty()) {
        throw OutOfBound();
    }

    return elem[top_p];
}

template <class elemType>
void SeqStack<elemType>::push(const elemType &e)
{
    if (isFull()) {
        doubleSpace();
    }

    elem[++top_p] = e;
}

template <class elemType>
void SeqStack<elemType>::pop()
{
    if (isEmpty()) {
        throw OutOfBound();
    }

    top_p--;
}

}  // namespace datastructures

#endif  // SEQSTACK_H