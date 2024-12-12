#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "Exceptions.h"

namespace datastructures
{
// 优先队列类
template <class elemType>
class PriorityQueue
{
   private:
    struct Node {
        elemType data;  // 存储数据
        int priority;   // 优先级
        Node *next;     // 指向下一个节点

        Node(const elemType &d, int p) : data(d), priority(p), next(nullptr) {}
    };

    Node *front_p;  // 队列的前端指针

   public:
    PriorityQueue();                                // 构造函数，初始化队列
    ~PriorityQueue();                               // 析构函数，释放队列内存
    bool isEmpty() const;                           // 判断队列是否为空
    void enQueue(const elemType &x, int priority);  // 插入元素并设置优先级
    void deQueue();                                 // 删除优先级最高的元素
    elemType front();                               // 返回优先级最高的元素
};

/**
 * 构造函数
 * 初始化一个空的优先队列
 */
template <class elemType>
PriorityQueue<elemType>::PriorityQueue() : front_p(nullptr)
{
}

/**
 * 析构函数
 * 释放队列占用的内存
 */
template <class elemType>
PriorityQueue<elemType>::~PriorityQueue()
{
    while (!isEmpty()) {
        deQueue();
    }
}

/**
 * 判断队列是否为空
 * 如果队列为空，返回true；否则返回false
 * @return 是否为空
 */
template <class elemType>
bool PriorityQueue<elemType>::isEmpty() const
{
    return front_p == nullptr;
}

/**
 * 插入元素并设置优先级
 * 按照优先级将元素插入队列中
 * @param x 插入的元素
 * @param priority 元素的优先级，越大优先级越高
 */
template <class elemType>
void PriorityQueue<elemType>::enQueue(const elemType &x, int priority)
{
    Node *newNode = new Node(x, priority);
    if (isEmpty() || front_p->priority < priority) {
        newNode->next = front_p;
        front_p = newNode;
    } else {
        Node *current = front_p;
        while (current->next != nullptr && current->next->priority >= priority) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

/**
 * 删除优先级最高的元素
 * 删除队列头部的元素
 */
template <class elemType>
void PriorityQueue<elemType>::deQueue()
{
    if (isEmpty()) {
        throw OutOfBound();  // 如果队列为空，抛出异常
    }

    Node *tmp = front_p;
    front_p = front_p->next;
    delete tmp;
}

/**
 * 返回优先级最高的元素
 * 如果队列为空，抛出异常
 * @return 优先级最高的元素
 */
template <class elemType>
elemType PriorityQueue<elemType>::front()
{
    if (isEmpty()) {
        throw OutOfBound();  // 如果队列为空，抛出异常
    }
    return front_p->data;
}
}  // namespace datastructures

#endif  // PRIORITY_QUEUE_H
