#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

struct TreeNode {
    int value;
    TreeNode *left_child, *right_child;

    TreeNode(int val) : value(val), left_child(nullptr), right_child(nullptr) {}
};

// 构建二叉树
TreeNode* buildTree(const vector<int>& node_values, int index)
{
    if (index >= node_values.size() || node_values[index] == -1) {
        return nullptr;
    }

    TreeNode* node = new TreeNode(node_values[index]);
    node->left_child = buildTree(node_values, 2 * index + 1);   // 左子节点
    node->right_child = buildTree(node_values, 2 * index + 2);  // 右子节点

    return node;
}

// 中序遍历
void inorderTraversal(TreeNode* root)
{
    if (!root) return;

    inorderTraversal(root->left_child);  // 遍历左子树
    if (root->value != -1) {             // 跳过 -1
        cout << root->value << " ";
    }
    inorderTraversal(root->right_child);  // 遍历右子树
}

int main()
{
    int n;
    cin >> n;  // 输入二叉树的层数

    int node_cnt = pow(2, n) - 1;  // 满二叉树的总节点数
    vector<int> node_values(node_cnt);

    for (int i = 0; i < node_cnt; i++) {
        cin >> node_values[i];  // 读入层次遍历结果
    }

    TreeNode* root = buildTree(node_values, 0);  // 构建二叉树
    inorderTraversal(root);                      // 中序遍历
    cout << endl;

    return 0;
}