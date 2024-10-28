#include <iostream>
#include "linkStack.h"

int calcSuf(char *sufStr)
{
    int op1, op2, op;
    int i = 0;
    LinkStack<int> s;

    while (sufStr[i] != '\0')
    {
        if (sufStr[i] >= '0' && sufStr[i] <= '9')
        {
            s.push(sufStr[i] - '0');
        }
        else
        {
            op2 = s.top();
            s.pop();
            op1 = s.top();
            s.pop();
            switch (sufStr[i])
            {
            case '+':
                op = op1 + op2;
                break;
            case '-':
                op = op1 - op2;
                break;
            case '*':
                op = op1 * op2;
                break;
            case '/':
                op = op1 / op2;
                break;
            }
            s.push(op);
        }
        i++;
    }

    return s.top();
}

int main()
{
    char sufStr[20];
    char ctemp;
    int i = 0;

    std::cout << "Input the suffix form expression: ";
    std::cin.getline(sufStr, 20, '\n');
    std::cout << "The suffix form expression you input is: " << sufStr << std::endl;

    std::cout << "The result of the expression is: " << calcSuf(sufStr) << std::endl;
    return 0;
}