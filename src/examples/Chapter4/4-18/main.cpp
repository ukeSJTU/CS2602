#include <iostream>

#include "HuffmanTree.h"

int main()
{
    // Example data
    const int n = 6;
    char data[n] = {'A', 'B', 'C', 'D', 'E', 'F'};
    double weights[n] = {3, 8, 10, 12, 50, 4};

    // Create Huffman tree
    datastructures::HuffmanTree<char> huffmanTree;
    huffmanTree.buildTree(data, weights, n);

    // Display the tree structure
    std::cout << "Huffman Tree Structure:" << std::endl;
    huffmanTree.disp();
    std::cout << std::endl;

    // Generate Huffman codes
    // Method 1: Let the function allocate memory
    char** codes1 = huffmanTree.HuffmanCode(nullptr, n);

    std::cout << "Method 1 - Huffman Codes:" << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << "Character " << data[i] << " (weight: " << weights[i]
                  << ") code: " << codes1[i] << std::endl;
    }

    // Clean up memory for method 1
    for (int i = 0; i < n; i++) {
        delete[] codes1[i];
    }
    delete[] codes1;

    // Method 2: Provide pre-allocated array
    char** codes2 = new char*[n];
    for (int i = 0; i < n; i++) {
        codes2[i] = new char[n + 1];
    }

    huffmanTree.HuffmanCode(codes2, n);

    std::cout << "\nMethod 2 - Huffman Codes:" << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << "Character " << data[i] << " (weight: " << weights[i]
                  << ") code: " << codes2[i] << std::endl;
    }

    // Clean up memory for method 2
    for (int i = 0; i < n; i++) {
        delete[] codes2[i];
    }
    delete[] codes2;

    return 0;
}
