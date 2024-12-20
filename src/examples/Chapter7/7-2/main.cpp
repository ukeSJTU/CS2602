#include <iostream>

template <class elemType>
void insert(elemType a[], int n, const elemType &x)
// n 为有序表a中当前元素的个数，x为待插入的新元素（也就是待排序的元素）
{
    int i;

    for (i = n - 1; i >= 0; i--) {
        if (a[i] <= x) {
            break;
        } else {
            a[i + 1] = a[i];
        }
    }

    a[i + 1] = x;
}

template <class elemType>
void insertSort(elemType a[], int n)
{
    int i, j;
    elemType tmp;

    // 将第i个元素插入到前i-1个元素的有序序列中
    for (i = 1; i < n; i++) {
        tmp = a[i];
        insert(a, i, tmp);
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

    insertSort(arr, n);

    std::cout << "After insert sort: " << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }

    std::cout << std::endl;

    return 0;
}