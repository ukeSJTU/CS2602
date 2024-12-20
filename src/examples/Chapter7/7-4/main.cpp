#include <iostream>

template <class elemType>
void shellSort(elemType a[], int n)
{
    int step, i, j;
    elemType tmp;

    // 步长从 n/2 开始，每次减半，直到步长为 1
    for (step = n / 2; step > 0; step /= 2) {
        // 从当前步长位置开始，遍历数组元素
        for (i = step; i < n; i++) {
            tmp = a[i];  // 将当前元素保存到 tmp 中
            j = i;       // j 用来查找合适的位置

            // 将当前元素与前面步长间隔的元素比较，如果当前元素较小，则交换位置
            while ((j - step >= 0) && (tmp <= a[j - step])) {
                a[j] = a[j - step];  // 将较大的元素移动到后面
                j -= step;           // 移动步长位置
            }

            a[j] = tmp;  // 将 tmp 放入找到的位置
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

    shellSort(arr, n);

    std::cout << "After shell sort: " << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }

    std::cout << std::endl;

    return 0;
}