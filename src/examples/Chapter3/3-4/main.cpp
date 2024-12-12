#include <iostream>

#include "LinkStack.h"

int main()
{
    datastructures::LinkStack<char> s;
    char ctemp;

    std::cout << "Input the elements, press enter to an end: ";
    ctemp = std::cin.get();

    while (ctemp != '\n') {
        s.push(ctemp);
        ctemp = std::cin.get();
    }

    std::cout << "Output the elemetns in the stack one by one: ";
    while (!s.isEmpty()) {
        ctemp = s.top();
        s.pop();
        std::cout << ctemp;
    }
    std::cout << std::endl;
    return 0;
}