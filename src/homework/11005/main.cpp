#include <iostream>
using namespace std;

// 验证一行或一列是否有效（数字1-9只出现一次）
bool isValid(int arr[], int size)
{
    bool used[10] = {false};  // 0号位置不用，1-9对应数字1-9
    for (int i = 0; i < size; i++) {
        int num = arr[i];

        // 数字已经出现过
        if (used[num]) {
            return false;
        }

        used[num] = true;
    }
    return true;
}

// 验证数独是否合法
bool isValidSudoku(int grid[9][9])
{
    // 检查每一行
    for (int i = 0; i < 9; i++) {
        if (!isValid(grid[i], 9)) return false;
    }

    // 检查每一列
    for (int j = 0; j < 9; j++) {
        int column[9];
        for (int i = 0; i < 9; i++) {
            column[i] = grid[i][j];
        }
        if (!isValid(column, 9)) return false;
    }

    // 检查每个3x3方格
    for (int block = 0; block < 9; block++) {
        int startRow = (block / 3) * 3;
        int startCol = (block % 3) * 3;
        int square[9];
        int index = 0;

        // 收集3x3方格中的数字
        for (int i = startRow; i < startRow + 3; i++) {
            for (int j = startCol; j < startCol + 3; j++) {
                square[index++] = grid[i][j];
            }
        }

        if (!isValid(square, 9)) return false;
    }

    return true;
}

int main()
{
    int n;
    cin >> n;  // 输入数独的个数

    while (n--) {
        int grid[9][9];

        // 读入数独
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                cin >> grid[i][j];
            }
        }

        // 验证并输出结果
        if (isValidSudoku(grid)) {
            cout << "Right" << endl;
        } else {
            cout << "Wrong" << endl;
        }
    }

    return 0;
}
