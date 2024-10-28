#include <iostream>
#include "seqQueue.h"

int main()
{
    int n;
    std::cout << "Input the number of elements(greater than 10): ";
    std::cin >> n;
    SeqQueue<int> q;

    for (int i = 0; i < n; i++)
    {
        q.enQueue(i);
    }

    int x;
    while (!q.isEmpty())
    {
        x = q.front();
        q.deQueue();
        std::cout << x << " ";
    }
    std::cout << std::endl;
    return 0;
}