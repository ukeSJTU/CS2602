#include <iostream>

template <class elemType>
void bubbleSort(elemType a[], int n)
{
    int i, j;
    bool changeFlag = true;
    elemType tmp;

    for (j = n - 1; j > 0; j--) {
        if (!changeFlag) {
            break;
        }

        changeFlag = false;
        for (i = 0; i < n - 1; i++) {
            if (a[i] > a[i + 1]) {
                // swap
                tmp = a[i];
                a[i] = a[i + 1];
                a[i + 1] = tmp;
                changeFlag = true;
            }
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

    bubbleSort(arr, n);

    std::cout << "After bubble sort: " << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }

    std::cout << std::endl;

    return 0;
}