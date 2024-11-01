#ifndef SEQQUEUE_H
#define SEQQUEUE_H

class IllegalSize
{
};
class OutOFBound
{
};

template <class elemType>
class SeqQueue
{
private:
    elemType *array;
    int maxSize;
    int front_p, rear_p;
    void doubleSpace();

public:
    SeqQueue(int initSize = 10);
    bool isEmpty();
    bool isFull();
    elemType front();
    void enQueue(const elemType &e);
    void deQueue();
    ~SeqQueue();
};

template <class elemType>
SeqQueue<elemType>::SeqQueue(int initSize)
{
    array = new elemType[initSize];
    if (!array)
    {
        throw IllegalSize();
    }

    maxSize = initSize;
    front_p = 0;
    rear_p = 0;
}

template <class elemType>
bool SeqQueue<elemType>::isEmpty()
{
    return front_p == rear_p;
}

template <class elemType>
bool SeqQueue<elemType>::isFull()
{
    return (rear_p + 1) % maxSize == front_p;
}

template <class elemType>
elemType SeqQueue<elemType>::front()
{
    if (isEmpty())
    {
        throw OutOFBound();
    }
    return array[front_p];
}

template <class elemType>
void SeqQueue<elemType>::enQueue(const elemType &e)
{
    if (isFull())
    {
        doubleSpace();
    }
    array[rear_p] = e;
    rear_p = (rear_p + 1) % maxSize;
}

template <class elemType>
void SeqQueue<elemType>::deQueue()
{
    if (isEmpty())
    {
        throw OutOFBound();
    }
    front_p = (front_p + 1) % maxSize;
}

template <class elemType>
SeqQueue<elemType>::~SeqQueue()
{
    delete[] array;
}

template <class elemType>
void SeqQueue<elemType>::doubleSpace()
{
    elemType *tmp = array;
    array = new elemType[2 * maxSize];
    if (!array)
    {
        throw IllegalSize();
    }

    for (int i = 0, j = front_p; j != rear_p;; i++, j = (j + 1) % maxSize)
    {
        array[i] = tmp[j];
    }

    front_p = 0;
    rear_p = i;
    maxSize *= 2;
    delete[] tmp;
}

#endif // SEQQUEUE_H