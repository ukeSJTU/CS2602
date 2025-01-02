#include <iostream>

template <class elemType>
void adjust(elemType a[], int n, int i)
{
    // 对尺寸为n的数组a，假设根为0下标元素，
    // 调整下标为i的元素，使得以i为根的二叉树为一个大顶堆
    int maxChild;
    elemType tmp;

    while (true) {
        maxChild = 2 * i + 1;  // i的左子下标

        if (maxChild > n - 1) {
            return;
        }

        // i还有右子
        if (maxChild + 1 <= n - 1) {
            // 右子大于等于左子
            if (a[maxChild + 1] >= a[maxChild]) {
                maxChild++;
            }
        }

        // 最大孩子小于父结点
        if (a[i] > a[maxChild]) {
            return;
        }

        // 最大孩子大于等于父结点，父结点向下调整
        tmp = a[i];
        a[i] = a[maxChild];
        a[maxChild] = tmp;

        i = maxChild;  // 继续向下调整
    }
}

template <class elemType>
void heapSort(elemType a[], int n)
{
    int i, j;
    elemType tmp;

    // 从倒数第一个非叶子结点开始调整，首次建立大顶堆
    for (i = (n - 2) / 2; i >= 0; i--) {
        adjust(a, n, i);
    }

    // 换大顶，主次减少参与的元素，重新调整为大顶堆
    for (j = n - 1; j >= 1; j--) {
        // 大顶和第i个位置元素交换
        tmp = a[0];
        a[0] = a[j];
        a[j] = tmp;

        // 调整第0个元素
        adjust(a, n, 0);
    }
}

int main()
{
    int n;
    std::cout << "Please input number of items to sort: ";

    std::cin >> n;

    int *arr = new int[n];

    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    heapSort(arr, n);

    std::cout << "After heap sort: " << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }

    std::cout << std::endl;

    return 0;
}