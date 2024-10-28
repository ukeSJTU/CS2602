template <class elemType>
struct HuffmanNode
{
    elemType data;
    double weight;
    int parent, left, right;
};

template <class elemType>
int minIndex(HuffmanNode<elemType> Bt[], int k, int m)
{
    int i, min, minWeight = 9999;

    for (i = m - 1; i > k; i--)
    {
        if (Bt[i].parent == 0 && Bt[i].weight < minWeight)
        {
            minWeight = Bt[i].weight;
            min = i;
        }
    }

    return min;
}

template <class elemType>
HuffmanNode<elemType> *BestBinaryTree(elemType a[], double w[], int n)
{
    int i, j, m = 2 * n;
    HuffmanNode<elemType> *BBTree = new HuffmanNode<elemType>[m];

    for (j = 0; j < n; j++)
    {
        i = m - 1 - j;
        BBTree[i].data = a[j];
        BBTree[i].weight = w[j];
        BBTree[i].parent = BBTree[i].left = BBTree[i].right = 0;
    }

    i = n - 1; // i is the position which is ready for the first new node

    while (i != 0)
    {
        first_min = minIndex(BBTree, i, m);
        BBTree[first_min].parent = i;
        second_min = minIndex(BBTree, i, m);
        BBTree[second_min].parent = i;

        BBTree[i].weight = BBTree[first_min].weight + BBTree[second_min].weight;
        BBTree[i].left = first_min;
        BBTree[i].right = second_min;
        BBTree[i].parent = 0;
        i--;
    }

    for (i = 1; i < n; i++)
    {
        std::cout << i << " data: " << "--" << " weight: " << BBTree[i].weight << " parent: " << BBTree[i].parent << " left: " << BBTree[i].left << " right: " << BBTree[i].right << std::endl;
    }

    for (; i < m; i++)
    {
        std::cout << i << " data: " << BBTree[i].data << " weight: " << BBTree[i].weight << " parent: " << BBTree[i].parent << " left: " << BBTree[i].left << " right: " << BBTree[i].right << std::endl;
    }

    return BBTree;
}