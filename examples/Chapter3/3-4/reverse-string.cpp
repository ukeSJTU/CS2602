#include <iostream>
#include "linkStack.h"

int main()
{
    LinkStack<char> s;
    char ctemp;

    std::cout << "Input the elements, press enter to an end: ";
    ctemp = std::cin.get();
    while (ctemp != '\n')
    {
        s.push(ctemp);
        ctemp = std::cin.get();
    }

    std::cout << "Output the elements in the stack one by one: ";
    while (!s.isEmpty())
    {
        std::cout << s.top() << " ";
        s.pop();
    }
    std::cout << std::endl;
    return 0;
}