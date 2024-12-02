#ifndef LINKSTACK_H
#define LINKSTACK_H

#include <cstddef>

#include "Exceptions.h"

namespace datastructures {
// 链栈的节点类定义
template <class elemType> class LinkStack; // 前向声明 LinkStack 模板类

// 链栈的节点类定义
template <class elemType> class Node {
    friend class LinkStack<elemType>;

  private:
    elemType data;        // 存储数据
    Node<elemType> *next; // 指向下一个节点

  public:
    // 默认构造函数
    Node() { next = nullptr; }

    // 带参数构造函数
    Node(const elemType &x, Node<elemType> *p = nullptr) {
        data = x;
        next = p;
    }
};

// 链栈类定义
template <class elemType> class LinkStack {
  private:
    Node<elemType> *top_p; // 栈顶指针

  public:
    // 默认构造函数，初始化栈为空
    LinkStack() { top_p = nullptr; }

    // 判断栈是否为空
    bool isEmpty() { return top_p == nullptr; }

    // 判断栈是否已满（对于链栈永远不会满）
    bool isFull() { return false; }

    // 返回栈顶元素
    elemType top();

    // 入栈操作
    void push(const elemType &e);

    // 出栈操作
    void pop();

    // 析构函数，清理栈内所有节点
    ~LinkStack();
};

// 返回栈顶元素
template <class elemType> elemType LinkStack<elemType>::top() {
    if (isEmpty()) // 栈为空时抛出异常
    {
        throw OutOfBound();
    }
    return top_p->data;
}

// 出栈操作
template <class elemType> void LinkStack<elemType>::pop() {
    if (isEmpty()) // 栈为空时抛出异常
    {
        throw OutOfBound();
    }
    Node<elemType> *tmp = top_p;
    top_p = top_p->next; // 更新栈顶指针
    delete tmp;          // 删除原栈顶节点
}

// 入栈操作
template <class elemType> void LinkStack<elemType>::push(const elemType &e) {
    top_p = new Node<elemType>(e, top_p); // 新节点插入栈顶
}

// 析构函数，清理栈内的所有节点
template <class elemType> LinkStack<elemType>::~LinkStack() {
    Node<elemType> *tmp;
    while (top_p) // 遍历栈，删除所有节点
    {
        tmp = top_p;
        top_p = top_p->next;
        delete tmp;
    }
}
} // namespace datastructures

#endif
