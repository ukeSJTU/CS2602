#ifndef LINKLIST_H
#define LINKLIST_H

#include <iostream>
#include <stdexcept>
#include "Exceptions.h"

// 定义命名空间 datastructures
namespace datastructures
{

    // LinkList 的前向声明
    template <class elemType>
    class LinkList;

    // 节点类定义
    template <class elemType>
    class Node
    {
        friend class LinkList<elemType>; // LinkList 类可以访问 Node 的私有成员

    private:
        elemType data; // 节点存储的数据
        Node *next;    // 指向下一个节点的指针

    public:
        Node() : next(nullptr) {}                                        // 默认构造函数
        Node(const elemType &e, Node *n = nullptr) : data(e), next(n) {} // 带数据和指针的构造函数
    };

    // LinkList 类定义
    template <class elemType>
    class LinkList
    {
    private:
        Node<elemType> *head; // 指向头节点的指针（哑节点）

    public:
        LinkList();                            // 构造函数
        bool isEmpty() const;                  // 检查链表是否为空
        bool isFull() const { return false; }  // 检查链表是否已满（对于链表来说，默认是永远不满的）
        int length() const;                    // 获取链表的长度
        elemType get(int i) const;             // 获取链表中第 i 个元素
        int find(const elemType &e) const;     // 查找元素的索引
        void insert(int i, const elemType &e); // 插入元素
        void remove(int i, elemType &e);       // 删除元素
        void reverse();                        // 反转链表
        void clear();                          // 清空链表
        ~LinkList();                           // 析构函数，释放内存
    };

    /**
     * 构造函数
     * 初始化一个空的链表，并创建一个哑头节点。
     */
    template <class elemType>
    LinkList<elemType>::LinkList()
    {
        head = new Node<elemType>(); // 创建一个哑头节点
    }

    /**
     * 析构函数
     * 清空链表并删除头节点，释放内存。
     */
    template <class elemType>
    LinkList<elemType>::~LinkList()
    {
        clear();
        delete head;
    }

    /**
     * 检查链表是否为空。
     * @return 如果链表为空，则返回 true，否则返回 false。
     */
    template <class elemType>
    bool LinkList<elemType>::isEmpty() const
    {
        return head->next == nullptr;
    }

    /**
     * 获取链表的长度。
     * @return 链表的元素个数。
     */
    template <class elemType>
    int LinkList<elemType>::length() const
    {
        int len = 0;
        Node<elemType> *p = head->next;
        while (p != nullptr)
        {
            len++;
            p = p->next;
        }
        return len;
    }

    /**
     * 获取链表中第 i 个元素。
     * 如果索引无效，抛出 OutOfBound 异常。
     * @param i 索引值。
     * @return 第 i 个元素。
     */
    template <class elemType>
    elemType LinkList<elemType>::get(int i) const
    {
        if (i < 0)
            throw OutOfBound();

        Node<elemType> *p = head->next;
        int idx = 0;
        while (p != nullptr && idx < i)
        {
            p = p->next;
            idx++;
        }
        if (p == nullptr)
            throw OutOfBound();
        return p->data;
    }

    /**
     * 查找链表中第一个元素 e 的位置。
     * @param e 要查找的元素。
     * @return 元素的索引，如果找不到，返回 -1。
     */
    template <class elemType>
    int LinkList<elemType>::find(const elemType &e) const
    {
        Node<elemType> *p = head->next;
        int idx = 0;
        while (p != nullptr)
        {
            if (p->data == e)
                return idx;
            p = p->next;
            idx++;
        }
        return -1;
    }

    /**
     * 在索引 i 处插入元素 e。
     * 如果索引无效，抛出 OutOfBound 异常。
     * @param i 索引值。
     * @param e 要插入的元素。
     */
    template <class elemType>
    void LinkList<elemType>::insert(int i, const elemType &e)
    {
        if (i < 0)
            throw OutOfBound();

        Node<elemType> *p = head;
        int idx = 0;
        while (p != nullptr && idx < i)
        {
            p = p->next;
            idx++;
        }
        if (p == nullptr)
            throw OutOfBound();

        Node<elemType> *newNode = new Node<elemType>(e, p->next);
        p->next = newNode;
    }

    /**
     * 删除索引 i 处的元素，并将其存入 e 中。
     * 如果索引无效，抛出 OutOfBound 异常。
     * @param i 索引值。
     * @param e 用于存储删除的元素。
     */
    template <class elemType>
    void LinkList<elemType>::remove(int i, elemType &e)
    {
        if (i < 0)
            throw OutOfBound();

        Node<elemType> *p = head;
        int idx = 0;
        while (p->next != nullptr && idx < i)
        {
            p = p->next;
            idx++;
        }
        if (p->next == nullptr)
            throw OutOfBound();

        Node<elemType> *q = p->next;
        p->next = q->next;
        e = q->data;
        delete q;
    }

    /**
     * 反转链表中的元素顺序。
     */
    template <class elemType>
    void LinkList<elemType>::reverse()
    {
        Node<elemType> *prev = nullptr;
        Node<elemType> *current = head->next;
        while (current != nullptr)
        {
            Node<elemType> *nextNode = current->next;
            current->next = prev;
            prev = current;
            current = nextNode;
        }
        head->next = prev;
    }

    /**
     * 清空链表，删除所有节点，保留头节点。
     */
    template <class elemType>
    void LinkList<elemType>::clear()
    {
        Node<elemType> *p = head->next;
        Node<elemType> *q;
        while (p != nullptr)
        {
            q = p->next;
            delete p;
            p = q;
        }
        head->next = nullptr;
    }

} // namespace datastructures

#endif // LINKLIST_H
