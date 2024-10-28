#ifndef LINK_QUEUE_H
#define LINK_QUEUE_H

class IllegalSize
{
};
class OutOfBound
{
};

template <class elemType>
class LinkQueue;

template <class elemType>
class Node
{
    friend class LinkQueue<elemType>;

private:
    elemType data;
    Node<elemType> *next;

public:
    Node() { next = nullptr; }
    Node(const elemType &x, Node<elemType> *n = nullptr)
    {
        data = x;
        next = n;
    }
};

template <class elemType>
class LinkQueue
{
private:
    Node<elemType> *front, *rear;

public:
    LinkQueue() { front = rear = nullptr; };
    ~LinkQueue();
    bool isEmpty() { return front == nullptr; }
    bool isFull() { return false; }
    elemType front();
    void enQueue(const elemType &x);
    void deQueue();
};

template <class elemType>
elemType LinkQueue<elemType>::front()
{
    if (isEmpty())
        throw OutOfBound();
    return front->data;
}

template <class elemType>
void LinkQueue<elemType>::enQueue(const elemType &x)
{
    if (rear == nullptr)
        front = rear = new Node<elemType>(x);
    else
    {
        rear->next = new Node<elemType>(x);
        rear = rear->next;
    }
}

template <class elemType>
void LinkQueue<elemType>::deQueue()
{
    if (isEmpty())
        throw OutOfBound();
    Node<elemType> *tmp = front;
    front = front->next;
    if (front == nullptr)
        rear = nullptr;
    delete tmp;
}

template <class elemType>
LinkQueue<elemType>::~LinkQueue()
{
    Node<elemType> *tmp;
    while (front != nullptr)
    {
        tmp = front;
        front = front->next;
        delete tmp;
    }
}

#endif // LINK_QUEUE_H