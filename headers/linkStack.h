class OutOfBound
{
};

template <class elemType>
class linkStack;

template <class elemType>
class Node
{
    friend class linkStack<elemType>;

private:
    elemType data;
    Node<elemType> *next;

public:
    Node() { next = nullptr; }
    Node(const elemType &x, Node<elemType> *p = nullptr)
    {
        data = x;
        next = p;
    }
};

template <class elemType>
class LinkStack
{
private:
    Node<elemType> *top_p;

public:
    LinkStack() { top_p = nullptr; }
    bool isEmpty() { return top_p == nullptr; }
    bool isFull() { return false; }
    elemType top();
    void push(const elemType &e);
    void pop();
    ~LinkStack();
};

template <class elemType>
elemType LinkStack<elemType>::top()
{
    if (isEmpty())
    {
        throw OutOfBound();
    }
    return top_p->data;
}

template <class elemType>
void LinkStack<elemType>::pop()
{
    if (isEmpty())
    {
        throw OutOfBound();
    }
    Node<elemType> *tmp = top_p;
    top_p = top_p->next;
    delete tmp;
}

template <class elemType>
void LinkStack<elemType>::push(const elemType &e)
{
    top_p = new Node<elemType>(e, top_p);
}

template <class elemType>
LinkStack<elemType>::~LinkStack()
{
    Node<elemType> *tmp;
    while (top_p)
    {
        tmp = top_p;
        top_p = top_p->next;
        delete tmp;
    }
}