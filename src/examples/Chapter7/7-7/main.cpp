#include <iostream>

template <class elemType>
void quickSort(elemType a[], int start, int end)
{
    int i, j, hole;
    elemType tmp;

    // 序列中没有元素或只有一个元素，递归结束
    if (end <= start) {
        return;
    }

    tmp = a[start];
    hole = start;
    i = start;  // 从左到右搜索的指针
    j = end;    // 从右到左搜索的指针

    while (i < j) {
        // 从j位置开始从后往前找第一个小于tmp的值
        while ((j > i) && (a[j] >= tmp)) {
            j--;
        }

        // 从上面while循环退出只有两种可能：
        // 1. j和i聚头，退出外层while循环并将本轮待排序元素tmp放到hole位置处
        // 2, 找到了第一个小于tmp的值
        if (j == i) {
            break;
        }

        a[hole] = a[j];
        hole = j;

        // 从j位置开始从后往前找第一个小于tmp的值
        while ((i < j) && (a[i] < tmp)) {
            i++;
        }

        // 从上面while循环退出只有两种可能：
        // 1. j和i聚头，退出外层while循环并将本轮待排序元素tmp放到hole位置处
        // 2. 找到了第一个大于tmp的值
        if (j == i) {
            break;
        }

        a[hole] = a[i];
        hole = i;
    }
    a[hole] = tmp;

    quickSort(a, start, hole - 1);
    quickSort(a, hole + 1, end);
}

template <class elemType>
void quickSort(elemType a[], int n)
{
    quickSort(a, 0, n - 1);
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

    quickSort(arr, n);

    std::cout << "After quick sort: " << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }

    std::cout << std::endl;

    return 0;
}