#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

// 使用全局索引来追踪遍历数组
int idx = 0;

// 递归计算二叉树的深度
int calculateDepth(const vector<int>& tree)
{
    if (idx >= tree.size()) {
        return 0;
    }

    int value = tree[idx++];

    // 如果是 -1，表示空节点，深度为 0
    if (value == -1) {
        return 0;
    }

    // 递归计算左子树和右子树的深度
    int leftDepth = calculateDepth(tree);
    int rightDepth = calculateDepth(tree);

    // 当前节点深度为左右子树的最大深度 + 1
    return max(leftDepth, rightDepth) + 1;
}

int main()
{
    string input;
    getline(cin, input);  // 读取整行输入

    vector<int> tree;
    stringstream ss(input);
    int value;

    while (ss >> value) {
        tree.push_back(value);  // 将输入转换为整数数组
    }

    idx = 0;  // 初始化索引
    cout << calculateDepth(tree) << endl;

    return 0;
}