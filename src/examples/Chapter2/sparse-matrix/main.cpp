#include <iostream>

#include "LinkList.h"

// 稀疏矩阵的元素表示
struct MatrixElement {
    int row, col;  // 行号和列号
    int value;     // 元素的值

    // 比较两个 MatrixElement 是否相等
    bool operator==(const MatrixElement &other) const
    {
        return row == other.row && col == other.col && value == other.value;
    }
};

// 稀疏矩阵类定义
class SparseMatrix
{
   private:
    int rows, cols;                                    // 矩阵的行数和列数
    datastructures::LinkList<MatrixElement> elements;  // 存储非零元素的链表

   public:
    SparseMatrix(int r, int c) : rows(r), cols(c) {}  // 构造函数

    void insertElement(int r, int c, int val);               // 插入一个非零元素
    void printMatrix() const;                                // 打印矩阵
    SparseMatrix add(const SparseMatrix &other) const;       // 矩阵加法
    SparseMatrix multiply(const SparseMatrix &other) const;  // 矩阵乘法
    SparseMatrix transpose() const;                          // 矩阵转置
};

// 插入一个非零元素
void SparseMatrix::insertElement(int r, int c, int val)
{
    if (r < 0 || r >= rows || c < 0 || c >= cols) {
        throw std::out_of_range("Invalid row or column index");
    }
    // 稀疏矩阵不用存储零元素
    if (val == 0) {
        return;
    } else {
        MatrixElement elem = {r, c, val};
        elements.insert(elements.length(), elem);
    }
}

// 打印矩阵
void SparseMatrix::printMatrix() const
{
    int currentIndex = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (currentIndex < elements.length() && elements.get(currentIndex).row == i &&
                elements.get(currentIndex).col == j) {
                std::cout << elements.get(currentIndex).value << " ";
                currentIndex++;
            } else {
                std::cout << "0 ";
            }
        }
        std::cout << std::endl;
    }
}

// 矩阵加法
SparseMatrix SparseMatrix::add(const SparseMatrix &other) const
{
    // 确保两个矩阵的维度相同
    if (rows != other.rows || cols != other.cols)
        throw std::invalid_argument("Matrix dimensions must match");

    SparseMatrix result(rows, cols);  // 构造结果矩阵
    int i = 0, j = 0;

    // 遍历两个矩阵的非零元素链表
    while (i < elements.length() || j < other.elements.length()) {
        if (i < elements.length() &&
            (j >= other.elements.length() || elements.get(i).row < other.elements.get(j).row ||
             (elements.get(i).row == other.elements.get(j).row &&
              elements.get(i).col < other.elements.get(j).col))) {
            // 当前元素只存在于第一个矩阵，直接插入结果
            result.insertElement(elements.get(i).row, elements.get(i).col, elements.get(i).value);
            i++;
        } else if (j < other.elements.length() &&
                   (i >= elements.length() || other.elements.get(j).row < elements.get(i).row ||
                    (other.elements.get(j).row == elements.get(i).row &&
                     other.elements.get(j).col < elements.get(i).col))) {
            // 当前元素只存在于第二个矩阵，直接插入结果
            result.insertElement(other.elements.get(j).row, other.elements.get(j).col,
                                 other.elements.get(j).value);
            j++;
        } else {
            // 两个矩阵在同一位置都有元素，计算和
            int sum = elements.get(i).value + other.elements.get(j).value;
            if (sum != 0) {
                // 如果和非零，插入结果
                result.insertElement(elements.get(i).row, elements.get(i).col, sum);
            }
            i++;
            j++;
        }
    }

    return result;
}

// 矩阵乘法
SparseMatrix SparseMatrix::multiply(const SparseMatrix &other) const
{
    // 确保矩阵维度匹配 (第一个矩阵的列数 == 第二个矩阵的行数)
    if (cols != other.rows)
        throw std::invalid_argument("Matrix dimensions must match for multiplication");

    SparseMatrix result(rows, other.cols);  // 构造结果矩阵

    // 遍历第一个矩阵的每个非零元素
    for (int i = 0; i < elements.length(); i++) {
        for (int j = 0; j < other.elements.length(); j++) {
            // 确保列号与行号匹配，满足乘法条件
            if (elements.get(i).col == other.elements.get(j).row) {
                int r = elements.get(i).row;                                    // 结果矩阵的行号
                int c = other.elements.get(j).col;                              // 结果矩阵的列号
                int val = elements.get(i).value * other.elements.get(j).value;  // 计算乘积

                // 插入到结果矩阵中，合并相同位置的元素
                bool found = false;
                for (int k = 0; k < result.elements.length(); k++) {
                    MatrixElement existingElement = result.elements.get(k);
                    if (existingElement.row == r && existingElement.col == c) {
                        // 如果找到相同位置的元素，删除原节点
                        result.elements.remove(k, existingElement);

                        // 创建一个新的节点，值更新为原值加上当前乘积
                        MatrixElement newElement = {r, c, existingElement.value + val};
                        result.elements.insert(k, newElement);

                        found = true;
                        break;
                    }
                }

                if (!found) {
                    // 如果未找到，直接插入新节点
                    result.insertElement(r, c, val);
                }
            }
        }
    }

    return result;
}

// 矩阵转置
SparseMatrix SparseMatrix::transpose() const
{
    SparseMatrix result(cols, rows);  // 构造结果矩阵，行列交换

    // 遍历所有非零元素，将其行列号交换后插入到结果矩阵
    for (int i = 0; i < elements.length(); i++) {
        result.insertElement(elements.get(i).col, elements.get(i).row, elements.get(i).value);
    }

    return result;
}

int main()
{
    SparseMatrix matrix1(3, 3), matrix2(3, 3);

    matrix1.insertElement(0, 0, 1);
    matrix1.insertElement(0, 1, 2);
    matrix1.insertElement(1, 2, 3);

    matrix2.insertElement(0, 0, 4);
    matrix2.insertElement(1, 1, 5);
    matrix2.insertElement(2, 2, 6);

    std::cout << "Matrix 1:" << std::endl;
    matrix1.printMatrix();

    std::cout << "Matrix 2:" << std::endl;
    matrix2.printMatrix();

    SparseMatrix sum = matrix1.add(matrix2);
    std::cout << "Sum of Matrix 1 and Matrix 2:" << std::endl;
    sum.printMatrix();

    SparseMatrix product = matrix1.multiply(matrix2);
    std::cout << "Product of Matrix 1 and Matrix 2:" << std::endl;
    product.printMatrix();

    SparseMatrix transpose = matrix1.transpose();
    std::cout << "Transpose of Matrix 1:" << std::endl;
    transpose.printMatrix();

    return 0;
}