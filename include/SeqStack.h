#ifndef SEQSTACK_H
#define SEQSTACK_H

#include "Exceptions.h"

namespace datastructures {

template <class elemType> class SeqStack {
  private:
    elemType *elem;
    int top_p; // index of the top element
    int maxSize;
    void doubleSpace();

  public:
    SeqStack(int initSize = 100);
    bool isEmpty() { return (top_p == -1); };
    bool isFull() { return (top_p == maxSize - 1); };
    elemType top();
    void push(const elemType &e);
    void pop();
    ~SeqStack() { delete[] elem; };
};

template <class elemType> SeqStack<elemType>::SeqStack(int initSize) {
    elem = new elemType[initSize];
    if (!elem) {
        throw IllegalSize();
    }

    maxSize = initSize;
    top_p = -1;
}

template <class elemType> void SeqStack<elemType>::doubleSpace() {
    elemType *tmp = elem;
    elem = new elemType[2 * maxSize];
    if (!elem) {
        throw IllegalSize();
    }

    for (int i = 0; i <= top_p; i++) {
        elem[i] = tmp[i];
    }

    maxSize *= 2;
    delete[] tmp;
}

template <class elemType> elemType SeqStack<elemType>::top() {
    if (isEmpty()) {
        throw OutOfBound();
    }

    return elem[top_p];
}

template <class elemType> void SeqStack<elemType>::push(const elemType &e) {
    if (isFull()) {
        doubleSpace();
    }

    elem[++top_p] = e;
}

template <class elemType> void SeqStack<elemType>::pop() {
    if (isEmpty()) {
        throw OutOfBound();
    }

    top_p--;
}

} // namespace datastructures

#endif // SEQSTACK_H