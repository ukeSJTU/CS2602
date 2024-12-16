#include <iostream>

template <class T>
class Node
{
   public:
    T data;
    Node *left, *right;

    Node() : left(nullptr), right(nullptr) {}
    Node(const T &x, Node *L = nullptr, Node *R = nullptr) : data(x), left(L), right(R) {}
};

// 后序遍历：右子树 -> 左子树 -> 根节点
void postOrderTraverse(Node<int> *root, bool isLast = false)
{
    if (root == nullptr) return;

    // 先访问右子树（镜像后的左子树）
    postOrderTraverse(root->right, false);
    // 再访问左子树（镜像后的右子树）
    postOrderTraverse(root->left, false);
    // 最后访问根节点
    std::cout << root->data << " ";
    // if (!isLast)
    // std::cout << " ";
}

// 释放树的内存
void deleteTree(Node<int> *root)
{
    if (root == nullptr) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main()
{
    Node<int> *node_index[10001] = {nullptr};  // 初始化为nullptr
    int n;
    std::cin >> n;

    // 读取第一行，创建根节点
    int root_val, left_val, right_val;
    std::cin >> root_val >> left_val >> right_val;

    // 创建根节点
    if (left_val != -1) {
        node_index[left_val] = new Node<int>(left_val);
    }
    if (right_val != -1) {
        node_index[right_val] = new Node<int>(right_val);
    }
    node_index[root_val] = new Node<int>(root_val, left_val != -1 ? node_index[left_val] : nullptr,
                                         right_val != -1 ? node_index[right_val] : nullptr);

    // 处理剩余的n-1行
    for (int i = 1; i < n; i++) {
        int parent, left, right;
        std::cin >> parent >> left >> right;

        // 如果这个父节点还没有创建，创建它
        if (node_index[parent] == nullptr) {
            node_index[parent] = new Node<int>(parent);
        }

        // 创建并连接左子节点
        if (left != -1) {
            node_index[left] = new Node<int>(left);
            node_index[parent]->left = node_index[left];
        }

        // 创建并连接右子节点
        if (right != -1) {
            node_index[right] = new Node<int>(right);
            node_index[parent]->right = node_index[right];
        }
    }

    // 执行后序遍历（因为是镜像树，所以先右后左）
    postOrderTraverse(node_index[root_val], true);
    std::cout << std::endl;

    // 释放内存
    deleteTree(node_index[root_val]);

    return 0;
}