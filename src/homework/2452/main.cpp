#include <iostream>
int arr[8];
int main()
{
    for (int i = 0; i < 7; i++) {
        std::cin >> arr[i];
    }
    int cnt;
    std::cin >> cnt;

    switch (cnt) {
        case 1:
            std::cout << arr[6] << std::endl;
            break;
        case 2:
            std::cout << arr[2] << std::endl;
            break;
        case 3:
            std::cout << arr[5] << std::endl;
            break;
        case 4:
            std::cout << arr[0] << std::endl;
            break;
        case 5:
            std::cout << arr[4] << std::endl;
            break;
        case 6:
            std::cout << arr[1] << std::endl;
            break;
        case 7:
            std::cout << arr[3] << std::endl;
            break;

        default:
            break;
    }
    return 0;
}