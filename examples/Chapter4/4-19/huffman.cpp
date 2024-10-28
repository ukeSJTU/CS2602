#include <iostream>
#include "huffman.h"

int main()
{
    char a[6] = {'A', 'B', 'C', 'D', 'E', 'F'};
    double w[6] = {3, 8, 10, 12, 50, 4};
    HuffmanNode<char> *BBTree = BestBinaryTree(a, w, 6);
    char **HFCode = HuffmanCode(BBTree, 6);

    for (int i = 0; i < 6; i++)
    {
        std::cout << a[i] << ": " << HFCode[i] << std::endl;
    }
    return 0;
}