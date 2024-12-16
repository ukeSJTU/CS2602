#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

/**
 * @file PriorityQueue.h
 * @brief 优先级队列（小顶堆）的实现
 */

#include "Exceptions.h"

namespace datastructures
{

/**
 * @class PriorityQueue
 * @brief 优先级队列（小顶堆）的模板类
 *
 * @tparam elemType 队列中存储元素的类型
 */
template <class elemType>
class PriorityQueue
{
   private:
    elemType* array;  ///< 动态数组，用于存储堆的元素
    int maxSize;      ///< 队列的最大容量
    int currentLen;   ///< 当前存储的元素个数

    void doubleSpace();          ///< 扩展队列的存储空间
    void adjust(int hole);       ///< 调整指定位置的元素以保持小顶堆的性质
    void buildRecursive(int r);  ///< 递归方式建立堆（效率较低，已注释）
    void buildIterative();       ///< 非递归方式建立堆

   public:
    PriorityQueue(int size = 10);                              ///< 构造空队列
    PriorityQueue(elemType a[], int n);                        ///< 从数组初始化队列
    bool isEmpty() const { return currentLen == 0; }           ///< 检查队列是否为空
    bool isFull() const { return currentLen == maxSize - 1; }  ///< 检查队列是否已满
    elemType front() const;                                    ///< 获取队首元素，不删除
    void enQueue(const elemType& x);                           ///< 入队操作
    void deQueue();                                            ///< 出队操作
    ~PriorityQueue() { delete[] array; }                       ///< 析构函数，释放动态数组
};

/**
 * @brief 构造一个空的优先级队列
 * @param size 队列的初始大小
 */
template <class elemType>
PriorityQueue<elemType>::PriorityQueue(int size)
{
    if (size < 1) throw IllegalSize();
    array = new elemType[size];
    maxSize = size;
    currentLen = 0;
}

/**
 * @brief 从数组初始化一个优先级队列
 * @param a 输入数组
 * @param n 数组长度
 */
template <class elemType>
PriorityQueue<elemType>::PriorityQueue(elemType a[], int n)
{
    if (n < 1) {
        throw IllegalSize();
    }
    array = new elemType[n + 10];  // 申请额外空间以支持后续入队
    maxSize = n + 10;
    currentLen = n;

    // 初始化堆
    for (int i = 0; i < n; i++) {
        array[i + 1] = a[i];
    }

    // 调用非递归方式建堆
    buildIterative();

    // 递归方式建堆（效率较低，已注释）
    // buildRecursive(1);
}

/**
 * @brief 非递归方式调整数组为小顶堆
 */
template <class elemType>
void PriorityQueue<elemType>::buildIterative()
{
    for (int i = currentLen / 2; i >= 1; i--) {
        adjust(i);
    }
}

// /**
//  * @brief 递归方式调整数组为小顶堆（效率较低）
//  * @param r 当前调整的根节点下标
//  */
// template <class elemType>
// void PriorityQueue<elemType>::buildRecursive(int r) {
//     if (r > currentLen / 2) return;
//     buildRecursive(2 * r);        // 递归调整左子树
//     buildRecursive(2 * r + 1);    // 递归调整右子树
//     adjust(r);
// }

/**
 * @brief 调整指定位置的元素以保持堆的性质
 * @param hole 元素的位置
 */
template <class elemType>
void PriorityQueue<elemType>::adjust(int hole)
{
    int minChild;
    elemType x = array[hole];

    while (2 * hole <= currentLen) {  // 如果存在左子节点
        minChild = 2 * hole;
        if (minChild + 1 <= currentLen && array[minChild + 1] < array[minChild]) {
            minChild++;  // 找到左右子节点中较小的
        }
        if (x <= array[minChild]) break;
        array[hole] = array[minChild];
        hole = minChild;  // 向下调整
    }
    array[hole] = x;
}

/**
 * @brief 获取队首元素
 * @return 队首元素的值
 */
template <class elemType>
elemType PriorityQueue<elemType>::front() const
{
    if (isEmpty()) {
        throw OutOfBound();
    }
    return array[1];
}

/**
 * @brief 入队操作，将新元素插入队列
 * @param x 新元素的值
 */
template <class elemType>
void PriorityQueue<elemType>::enQueue(const elemType& x)
{
    if (isFull()) {
        doubleSpace();
    }
    int hole = ++currentLen;

    // 向上调整以保持堆性质
    for (; hole > 1 && x < array[hole / 2]; hole /= 2) {
        array[hole] = array[hole / 2];
    }
    array[hole] = x;
}

/**
 * @brief 出队操作，删除队首元素
 */
template <class elemType>
void PriorityQueue<elemType>::deQueue()
{
    if (isEmpty()) throw OutOfBound();
    array[1] = array[currentLen--];
    adjust(1);
}

/**
 * @brief 扩展队列存储空间
 */
template <class elemType>
void PriorityQueue<elemType>::doubleSpace()
{
    elemType* temp = new elemType[2 * maxSize];
    for (int i = 1; i <= currentLen; i++) temp[i] = array[i];
    delete[] array;
    array = temp;
    maxSize *= 2;
}

}  // namespace datastructures

#endif  // PRIORITYQUEUE_H