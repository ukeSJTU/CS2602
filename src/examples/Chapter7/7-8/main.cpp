#include <iostream>

template <class elemType>
void selectSort(elemType a[], int n)
{
    int i, j, minIndex;
    elemType tmp;

    // 为每个位置找合适的数据
    for (i = 0; i < n; i++) {
        // 为第i个位置找合适的数据
        minIndex = i;
        for (j = i + 1; j < n; j++) {
            if (a[j] < a[minIndex]) {
                minIndex = j;
            }
        }

        // 将minIndex位置上的数据和位置i上数据交换
        if (minIndex == i) {
            continue;

        } else {
            tmp = a[i];
            a[i] = a[minIndex];
            a[minIndex] = tmp;
        }
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

    selectSort(arr, n);

    std::cout << "After select sort: " << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }

    std::cout << std::endl;

    return 0;
}