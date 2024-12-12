#ifndef LINKSTACK_H
#define LINKSTACK_H

#include <cstddef>

#include "Exceptions.h"

namespace datastructures
{
/**
 * @brief 链栈的节点类定义
 * @tparam elemType 链栈中存储的数据类型
 */
template <class elemType>
class LinkStack;  // 前向声明 LinkStack 模板类

/**
 * @brief 链栈的节点类
 * @tparam elemType 链栈中存储的数据类型
 */
template <class elemType>
class Node
{
    friend class LinkStack<elemType>;

   private:
    elemType data;         ///< 存储节点数据
    Node<elemType> *next;  ///< 指向下一个节点的指针

   public:
    /**
     * @brief 默认构造函数
     */
    Node() { next = nullptr; }

    /**
     * @brief 带参数构造函数
     * @param x 节点存储的数据
     * @param p 指向下一个节点的指针（默认为 nullptr）
     */
    Node(const elemType &x, Node<elemType> *p = nullptr)
    {
        data = x;
        next = p;
    }
};

/**
 * @brief 链栈类
 * @tparam elemType 链栈中存储的数据类型
 */
template <class elemType>
class LinkStack
{
   private:
    Node<elemType> *top_p;  ///< 栈顶指针

   public:
    /**
     * @brief 默认构造函数，初始化栈为空
     */
    LinkStack() { top_p = nullptr; }

    /**
     * @brief 判断栈是否为空
     * @return 如果栈为空返回 true，否则返回 false
     */
    bool isEmpty() { return top_p == nullptr; }

    /**
     * @brief 判断栈是否已满（对于链栈，永远不会满）
     * @return 返回 false
     */
    bool isFull() { return false; }

    /**
     * @brief 返回栈顶元素
     * @return 栈顶元素的值
     * @throw OutOfBound 如果栈为空，抛出 OutOfBound 异常
     */
    elemType top();

    /**
     * @brief 入栈操作
     * @param e 要入栈的元素
     */
    void push(const elemType &e);

    /**
     * @brief 出栈操作
     * @throw OutOfBound 如果栈为空，抛出 OutOfBound 异常
     */
    void pop();

    /**
     * @brief 析构函数，清理栈内所有节点
     */
    ~LinkStack();
};

/**
 * @brief 返回栈顶元素
 * @tparam elemType 链栈中存储的数据类型
 * @return 栈顶元素的值
 * @throw OutOfBound 如果栈为空，抛出 OutOfBound 异常
 */
template <class elemType>
elemType LinkStack<elemType>::top()
{
    if (isEmpty())  // 栈为空时抛出异常
    {
        throw OutOfBound();
    }
    return top_p->data;
}

/**
 * @brief 出栈操作
 * @tparam elemType 链栈中存储的数据类型
 * @throw OutOfBound 如果栈为空，抛出 OutOfBound 异常
 */
template <class elemType>
void LinkStack<elemType>::pop()
{
    if (isEmpty())  // 栈为空时抛出异常
    {
        throw OutOfBound();
    }
    Node<elemType> *tmp = top_p;
    top_p = top_p->next;  // 更新栈顶指针
    delete tmp;           // 删除原栈顶节点
}

/**
 * @brief 入栈操作
 * @tparam elemType 链栈中存储的数据类型
 * @param e 要入栈的元素
 */
template <class elemType>
void LinkStack<elemType>::push(const elemType &e)
{
    top_p = new Node<elemType>(e, top_p);  // 新节点插入栈顶
}

/**
 * @brief 析构函数，清理栈内的所有节点
 * @tparam elemType 链栈中存储的数据类型
 */
template <class elemType>
LinkStack<elemType>::~LinkStack()
{
    Node<elemType> *tmp;
    while (top_p)  // 遍历栈，删除所有节点
    {
        tmp = top_p;
        top_p = top_p->next;
        delete tmp;
    }
}
}  // namespace datastructures

#endif