class IllegalSize
{
};
class OutOfBound
{
};

template <class elemType>
class seqStack
{
private:
    elemType *elem;
    int top_p; // index of the top element
    int maxSize;
    void doubleSpace();

public:
    seqStack(int initSize = 100);
    bool isEmpty() { return (top_p == -1); };
    bool isFull() { return (top_p == maxSize - 1); };
    elemType top();
    void push(const elemType &e);
    void pop();
    ~seqStack() { delete[] array };
};

template <class elemType>
seqStack<elemType>::seqStack(int initSize)
{
    elem = new elemType[initSize];
    if (!elem)
    {
        throw IllegalSize();
    }

    maxSize = initSize;
    top_p = -1;
}

template <class elemType>
void seqStack<elemType>::doubleSpace()
{
    elemType *tmp = elem;
    elem = new elemType[2 * maxSize];
    if (!elem)
    {
        throw IllegalSize();
    }

    for (int i = 0; i <= top_p; i++)
    {
        elem[i] = tmp[i];
    }

    maxSize *= 2;
    delete[] tmp;
}

template <class elemType>
elemType seqStack<elemType>::top()
{
    if (isEmpty())
    {
        throw OutOfBound();
    }

    return elem[top_p];
}

template <class elemType>
void seqStack<elemType>::push(const elemType &e)
{
    if (isFull())
    {
        doubleSpace();
    }

    elem[++top_p] = e;
}

template <class elemType>
void seqStack<elemType>::pop()
{
    if (isEmpty())
    {
        throw OutOfBound();
    }

    top_p--;
}