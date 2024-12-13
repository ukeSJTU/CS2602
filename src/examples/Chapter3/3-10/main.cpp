#include <iostream>

#include "SeqQueue.h"

int main()
{
    datastructures::SeqQueue<int> q;
    int i, x;

    for (int i = 0; i < 15; i++) {
        q.enQueue(i);
        // std::cout << "i = " << i << " Queue is full? " << q.isFull() << std::endl;
    }

    while (!q.isEmpty()) {
        std::cout << q.front() << " ";
        q.deQueue();
    }

    std::cout << std::endl;
    return 0;
}