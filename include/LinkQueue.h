#ifndef LINK_QUEUE_H
#define LINK_QUEUE_H

#include <cstddef>

#include "Exceptions.h"

template <class elemType> class LinkQueue;

template <class elemType> class Node {
    friend class LinkQueue<elemType>;

  private:
    elemType data;
    Node<elemType> *next;

  public:
    Node() { next = nullptr; }
    Node(const elemType &x, Node<elemType> *n = nullptr) {
        data = x;
        next = n;
    }
};

template <class elemType> class LinkQueue {
  private:
    Node<elemType> *front_p, *rear_p;

  public:
    LinkQueue() { front_p = rear_p = nullptr; };
    ~LinkQueue();
    bool isEmpty() { return front_p == nullptr; }
    bool isFull() { return false; }
    elemType front();
    void enQueue(const elemType &x);
    void deQueue();
};

template <class elemType> elemType LinkQueue<elemType>::front() {
    if (isEmpty())
        throw OutOfBound();
    return front_p->data;
}

template <class elemType> void LinkQueue<elemType>::enQueue(const elemType &x) {
    if (rear_p == nullptr)
        front_p = rear_p = new Node<elemType>(x);
    else {
        rear_p->next = new Node<elemType>(x);
        rear_p = rear_p->next;
    }
}

template <class elemType> void LinkQueue<elemType>::deQueue() {
    if (isEmpty())
        throw OutOfBound();
    Node<elemType> *tmp = front_p;
    front_p = front_p->next;
    if (front_p == nullptr)
        rear_p = nullptr;
    delete tmp;
}

template <class elemType> LinkQueue<elemType>::~LinkQueue() {
    Node<elemType> *tmp;
    while (front_p != nullptr) {
        tmp = front_p;
        front_p = front_p->next;
        delete tmp;
    }
}

#endif // LINK_QUEUE_H