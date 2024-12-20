#include <iostream>

template <class elemType>
void merge(elemType a[], int low, int mid, int high)
{
    int i = low, j = mid + 1, k = 0;
    elemType *c = new elemType[high - low + 1];  // 创建实际空间存储合并后的结果

    // 两个有序序列中元素的比较合并
    while ((i <= mid) && (j <= high)) {
        if (a[i] <= a[j]) {
            c[k] = a[i];
            i++;
        } else {
            c[k] = a[j];
            j++;
        }
        k++;
    }

    // copy剩余的元素
    while (i <= mid) {
        c[k] = a[i];
        i++;
        k++;
    }

    while (j <= high) {
        c[k] = a[j];
        j++;
        k++;
    }

    for (i = 0; i < high - low + 1; i++) {
        a[i + low] = c[i];
    }

    delete[] c;
}

template <class elemType>
void mergeSort(elemType a[], int low, int high)
{
    if (low >= high) {
        return;
    }

    int mid = (low + high) / 2;

    mergeSort(a, low, mid);
    mergeSort(a, mid + 1, high);
    merge(a, low, mid, high);
}

template <class elemType>
void mergeSort(elemType a[], int n)
{
    mergeSort(a, 0, n - 1);
}

int main()
{
    int arr[] = {38, 27, 43, 3, 9, 82, 10};
    int n = sizeof(arr) / sizeof(arr[0]);

    std::cout << "Original array: ";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    mergeSort(arr, n);

    std::cout << "Sorted array: ";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}