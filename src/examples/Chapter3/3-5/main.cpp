#include <iostream>

#include "LinkStack.h"

int main()
{
    int STR_LEN = 50;
    char str[STR_LEN];
    datastructures::LinkStack<char> s;
    char ctemp;
    int i;

    std::cout << "Input the string: ";
    std::cin.getline(str, STR_LEN, '\n');
    std::cout << "str:" << str << std::endl;

    i = 0;
    ctemp = str[i++];
    while (ctemp != '\0') {
        if (ctemp == '(' || ctemp == '[' || ctemp == '{') {
            s.push(ctemp);
        } else {
            if (s.isEmpty()) {
                std::cout << "An opening bracket '(' is expected!\n" << std::endl;
                return 1;
            }

            else {
                s.pop();
            }
        }

        ctemp = str[i++];
    }

    if (!s.isEmpty()) {
        std::cout << "A closing bracket ')' is expected!\n" << std::endl;
    } else {
        std::cout << "The brackets match in this expression" << std::endl;
    }

    return 0;
}