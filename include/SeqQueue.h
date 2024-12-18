#ifndef SEQQUEUE_H
#define SEQQUEUE_H

#include "Exceptions.h"

namespace datastructures
{

/**
 * @brief 顺序队列类模板
 * @tparam elemType 队列中存储的元素类型
 */
template <class elemType>
class SeqQueue
{
   private:
    elemType *array;  ///< 存储队列数据的数组
    int maxSize;      ///< 队列的最大容量
    int front_p;      ///< 队列头部指针
    int rear_p;       ///< 队列尾部指针
    /**
     * @brief 扩大队列容量为原来的两倍
     */
    void doubleSpace();

   public:
    /**
     * @brief 构造函数
     * @param initSize 初始队列容量（默认为 10）
     * @throw IllegalSize 如果无法分配内存，抛出异常
     */
    SeqQueue(int initSize = 10);

    /**
     * @brief 判断队列是否为空
     * @return 如果队列为空返回 true，否则返回 false
     */
    bool isEmpty();

    /**
     * @brief 判断队列是否已满
     * @return 如果队列已满返回 true，否则返回 false
     */
    bool isFull();

    /**
     * @brief 获取队列头部的元素
     * @return 队列头部元素的引用
     * @throw OutOfBound 如果队列为空，抛出异常
     */
    elemType &front();

    /**
     * @brief 获取队列头部的元素（const版本）
     * @return 队列头部元素的常量引用
     * @throw OutOfBound 如果队列为空，抛出异常
     */
    const elemType &front() const;

    /**
     * @brief 向队列尾部插入新元素
     * @param e 要插入的元素
     * @throw IllegalSize 如果内存分配失败，抛出异常
     */
    void enQueue(const elemType &e);

    /**
     * @brief 移除队列头部的元素
     * @throw OutOfBound 如果队列为空，抛出异常
     */
    void deQueue();

    /**
     * @brief 析构函数，释放队列内存
     */
    ~SeqQueue();
};

/**
 * @brief 构造函数
 * @tparam elemType 队列中存储的元素类型
 * @param initSize 初始队列容量（默认为 10）
 * @throw IllegalSize 如果无法分配内存，抛出异常
 */
template <class elemType>
SeqQueue<elemType>::SeqQueue(int initSize)
{
    array = new elemType[initSize];
    if (!array) {
        throw IllegalSize();
    }

    maxSize = initSize;
    front_p = 0;
    rear_p = 0;
}

/**
 * @brief 判断队列是否为空
 * @tparam elemType 队列中存储的元素类型
 * @return 如果队列为空返回 true，否则返回 false
 */
template <class elemType>
bool SeqQueue<elemType>::isEmpty()
{
    return front_p == rear_p;
}

/**
 * @brief 判断队列是否已满
 * @tparam elemType 队列中存储的元素类型
 * @return 如果队列已满返回 true，否则返回 false
 */
template <class elemType>
bool SeqQueue<elemType>::isFull()
{
    return (rear_p + 1) % maxSize == front_p;
}

/**
 * @brief 获取队列头部的元素
 * @tparam elemType 队列中存储的元素类型
 * @return 队列头部元素
 * @throw OutOfBound 如果队列为空，抛出异常
 */
template <class elemType>
elemType &SeqQueue<elemType>::front()
{
    if (isEmpty()) {
        throw OutOfBound();
    }
    return array[front_p];
}

template <class elemType>
const elemType &SeqQueue<elemType>::front() const
{
    if (isEmpty()) {
        throw OutOfBound();  // 如果队列为空，抛出异常
    }
    return array[front_p];  // 返回队头元素的常量引用
}

/**
 * @brief 向队列尾部插入新元素
 * @tparam elemType 队列中存储的元素类型
 * @param e 要插入的元素
 * @throw IllegalSize 如果内存分配失败，抛出异常
 */
template <class elemType>
void SeqQueue<elemType>::enQueue(const elemType &e)
{
    if (isFull()) {
        doubleSpace();
    }
    array[rear_p] = e;
    rear_p = (rear_p + 1) % maxSize;
}

/**
 * @brief 移除队列头部的元素
 * @tparam elemType 队列中存储的元素类型
 * @throw OutOfBound 如果队列为空，抛出异常
 */
template <class elemType>
void SeqQueue<elemType>::deQueue()
{
    if (isEmpty()) {
        throw OutOfBound();
    }
    front_p = (front_p + 1) % maxSize;
}

/**
 * @brief 析构函数，释放队列内存
 * @tparam elemType 队列中存储的元素类型
 */
template <class elemType>
SeqQueue<elemType>::~SeqQueue()
{
    delete[] array;
}

/**
 * @brief 扩大队列容量为原来的两倍
 * @tparam elemType 队列中存储的元素类型
 * @throw IllegalSize 如果内存分配失败，抛出异常
 */
template <class elemType>
void SeqQueue<elemType>::doubleSpace()
{
    elemType *newArray;

    newArray = new elemType[2 * maxSize];
    if (!newArray) {
        throw IllegalSize();
    }

    int i, j;
    for (i = 0, j = front_p; j != rear_p; j = (j + 1) % maxSize, i++) {
        newArray[i] = array[j];
    }

    delete[] array;

    array = newArray;
    front_p = 0;
    rear_p = i;
    maxSize *= 2;
}
}  // namespace datastructures

#endif  // SEQQUEUE_H