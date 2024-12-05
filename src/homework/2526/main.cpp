#include "SeqQueue.h"
#include <iostream>
#include <string>

using namespace datastructures;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

TreeNode *buildTree() {
    int n;
    std::cin >> n;
    if (n <= 0)
        return nullptr;

    datastructures::SeqQueue<TreeNode *> q;
    std::string value;
    std::cin >> value;

    if (value == "null")
        return nullptr;

    TreeNode *root = new TreeNode(std::stoi(value));
    q.enQueue(root);

    int index = 0;
    while (!q.isEmpty() && index < n - 1) {
        TreeNode *current = q.front();
        q.deQueue();

        // Left child
        if (index < n - 1) {
            std::cin >> value;
            index++;
            if (value != "null") {
                current->left = new TreeNode(std::stoi(value));
                q.enQueue(current->left);
            }
        }

        // Right child
        if (index < n - 1) {
            std::cin >> value;
            index++;
            if (value != "null") {
                current->right = new TreeNode(std::stoi(value));
                q.enQueue(current->right);
            }
        }
    }

    return root;
}

int getDepth(TreeNode *root) {
    if (root == nullptr)
        return 0;
    return std::max(getDepth(root->left), getDepth(root->right)) + 1;
}

void deleteTree(TreeNode *root) {
    if (root == nullptr)
        return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    TreeNode *root = buildTree();
    int depth = getDepth(root);
    std::cout << depth << std::endl;
    deleteTree(root);
    return 0;
}