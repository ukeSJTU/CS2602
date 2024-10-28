#include <iostream>
#include "linkStack.h"

int main()
{
    LinkStack<char> s;
    char str[20];
    char ctemp;
    int i = 0;

    std::cout << "Input the string: ";
    std::cin.getline(str, 20, '\n');
    std::cout << "The string you input is: " << str << std::endl;

    ctemp = str[i];
    while (ctemp != '\0')
    {
        switch (ctemp)
        {
        case '(':
            s.push(ctemp);
            break;
        case ')':
            if (s.isEmpty())
            {
                std::cout << "An opening bracket '(' is expected!" << std::endl;
                return 1;
            }
            else
            {
                s.pop();
            }
            break;
        }
        i++;
        ctemp = str[i];
    }

    if (!s.isEmpty())
    {
        std::cout << "A closing bracket ')' is expected!" << std::endl;
        return 1;
    }
    return 0;
}