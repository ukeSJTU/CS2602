#include <iostream>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// 函数用于构建二叉树
TreeNode* buildTree(int* preorder, int& index, int size)
{
    if (index >= size || preorder[index] == -1) {
        index++;
        return nullptr;
    }

    TreeNode* node = new TreeNode(preorder[index++]);
    node->left = buildTree(preorder, index, size);
    node->right = buildTree(preorder, index, size);
    return node;
}

// 释放树的内存
void deleteTree(TreeNode* root)
{
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;  // 释放当前节点的内存
}

// 查找节点的深度
int findDepth(TreeNode* root, int target, int depth)
{
    if (!root) return -1;  // 找不到节点返回 -1

    if (root->val == target) return depth;

    int leftDepth = findDepth(root->left, target, depth + 1);
    if (leftDepth != -1) return leftDepth;

    return findDepth(root->right, target, depth + 1);
}

// 查找节点的父节点
TreeNode* findParent(TreeNode* root, int target)
{
    if (!root || root->val == target) {
        return nullptr;
    }  // 根节点或者就是目标节点本身

    if ((root->left && root->left->val == target) || (root->right && root->right->val == target)) {
        return root;
    }

    TreeNode* leftParent = findParent(root->left, target);
    if (leftParent) return leftParent;

    return findParent(root->right, target);
}

// 判断两个节点是否为堂姐妹堂兄弟节点
bool areCousins(TreeNode* root, int x, int y)
{
    int depthX = findDepth(root, x, 0);
    int depthY = findDepth(root, y, 0);

    if (depthX == -1 || depthY == -1 || depthX != depthY) {
        return false;
    }

    TreeNode* parentX = findParent(root, x);
    TreeNode* parentY = findParent(root, y);

    return parentX != parentY;  // 不同父节点且深度相同
}

int main()
{
    int q;
    std::cin >> q;

    int queries[q][2];  // 假设最大查询数量为 q
    for (int i = 0; i < q; ++i) {
        std::cin >> queries[i][0] >> queries[i][1];
    }

    int preorder[1500];  // 假设最大节点数量为 1000
    int index = 0;

    // 使用 std::cin 直接读取前序遍历数据
    while (std::cin >> preorder[index]) {
        index++;
        if (std::cin.peek() == '\n') break;  // 一行结束时停止读取
    }

    int size = index;
    index = 0;
    TreeNode* root = buildTree(preorder, index, size);

    for (int i = 0; i < q; ++i) {
        int x = queries[i][0];
        int y = queries[i][1];
        if (areCousins(root, x, y)) {
            std::cout << 1 << std::endl;
        } else {
            std::cout << 0 << std::endl;
        }
    }

    // 释放树的内存
    deleteTree(root);

    return 0;
}