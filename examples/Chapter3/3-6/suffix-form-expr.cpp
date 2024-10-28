#include <iostream>
#include "linkStack.h"

void inToSufForm(char *inStr, char *sufStr)
{
    LinkStack<char> s;
    int i = 0, j = 0;
    char topCh;

    s.push('#');

    while (inStr[i] != '\0')
    {
        if (inStr[i] >= '0' && inStr[i] <= '9')
        {
            sufStr[j++] = inStr[i];
        }
        else if (inStr[i] == ' ')
        {
            i++;
            continue;
        }
        else
        {
            switch (inStr[i])
            {
            case '(':
                s.push(inStr[i]);
                break;
            case ')':
                topCh = s.top();
                s.pop();
                while (topCh != '(')
                {
                    sufStr[j++] = topCh;
                    topCh = s.top();
                    s.pop();
                }
                break;
            case '+':
            case '-':
                topCh = s.top();
                while (topCh != '#' && topCh != '(')
                {
                    sufStr[j++] = topCh;
                    s.pop();
                    topCh = s.top();
                }
                s.push(inStr[i]);
                break;
            case '*':
            case '/':
                topCh = s.top();
                while (topCh == '*' || topCh == '/')
                {
                    sufStr[j++] = topCh;
                    s.pop();
                    topCh = s.top();
                }
                s.push(inStr[i]);
                break;
            }
        }
        i++;
    }

    topCh = s.top();
    while (topCh != '#')
    {
        sufStr[j++] = topCh;
        s.pop();
        topCh = s.top();
    }

    sufStr[j] = '\0';

    return;
}

int main()
{
    char inStr[20], sufStr[20];

    std::cout << "Input the infix expression: ";
    std::cin.getline(inStr, 20, '\n');

    inToSufForm(inStr, sufStr);

    std::cout << "The suffix expression is: " << sufStr << std::endl;

    return 0;
}