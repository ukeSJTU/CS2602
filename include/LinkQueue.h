#ifndef LINK_QUEUE_H
#define LINK_QUEUE_H

#include "Exceptions.h"

namespace datastructures
{

// LinkQueue 前向声明
template <class elemType>
class LinkQueue;

/**
 * @brief 链式队列节点类
 * @tparam elemType 队列中存储的元素类型
 */
template <class elemType>
class Node
{
    friend class LinkQueue<elemType>;

   private:
    elemType data;         ///< 节点存储的数据
    Node<elemType> *next;  ///< 指向下一个节点的指针

   public:
    /**
     * @brief 默认构造函数
     */
    Node() { next = nullptr; }

    /**
     * @brief 带参数构造函数
     * @param x 节点的数据
     * @param n 指向下一个节点的指针（默认为 nullptr）
     */
    Node(const elemType &x, Node<elemType> *n = nullptr)
    {
        data = x;
        next = n;
    }
};

/**
 * @brief 链式队列类
 * @tparam elemType 队列中存储的元素类型
 */
template <class elemType>
class LinkQueue
{
   private:
    Node<elemType> *front_p;  ///< 指向队列头部节点的指针
    Node<elemType> *rear_p;   ///< 指向队列尾部节点的指针

   public:
    /**
     * @brief 默认构造函数，初始化队列为空
     */
    LinkQueue() { front_p = rear_p = nullptr; }

    /**
     * @brief 析构函数，释放队列内存
     */
    ~LinkQueue();

    /**
     * @brief 判断队列是否为空
     * @return 如果队列为空返回 true，否则返回 false
     */
    bool isEmpty() { return front_p == nullptr; }

    /**
     * @brief 判断队列是否已满（链式队列永远不会满）
     * @return 始终返回 false
     */
    bool isFull() { return false; }

    /**
     * @brief 获取队列头部元素
     * @return 队列头部元素
     * @throw OutOfBound 如果队列为空，抛出异常
     */
    elemType front();

    /**
     * @brief 向队列尾部插入新元素
     * @param x 要插入的元素
     */
    void enQueue(const elemType &x);

    /**
     * @brief 从队列头部移除元素
     * @throw OutOfBound 如果队列为空，抛出异常
     */
    void deQueue();
};

/**
 * @brief 获取队列头部元素
 * @tparam elemType 队列中存储的元素类型
 * @return 队列头部元素
 * @throw OutOfBound 如果队列为空，抛出异常
 */
template <class elemType>
elemType LinkQueue<elemType>::front()
{
    if (isEmpty()) throw OutOfBound();
    return front_p->data;
}

/**
 * @brief 向队列尾部插入新元素
 * @tparam elemType 队列中存储的元素类型
 * @param x 要插入的元素
 */
template <class elemType>
void LinkQueue<elemType>::enQueue(const elemType &x)
{
    if (rear_p == nullptr)
        front_p = rear_p = new Node<elemType>(x);
    else {
        rear_p->next = new Node<elemType>(x);
        rear_p = rear_p->next;
    }
}

/**
 * @brief 从队列头部移除元素
 * @tparam elemType 队列中存储的元素类型
 * @throw OutOfBound 如果队列为空，抛出异常
 */
template <class elemType>
void LinkQueue<elemType>::deQueue()
{
    if (isEmpty()) throw OutOfBound();
    Node<elemType> *tmp = front_p;
    front_p = front_p->next;
    if (front_p == nullptr) rear_p = nullptr;
    delete tmp;
}

/**
 * @brief 析构函数，释放队列内存
 * @tparam elemType 队列中存储的元素类型
 */
template <class elemType>
LinkQueue<elemType>::~LinkQueue()
{
    Node<elemType> *tmp;
    while (front_p != nullptr) {
        tmp = front_p;
        front_p = front_p->next;
        delete tmp;
    }
}
}  // namespace datastructures

#endif  // LINK_QUEUE_H