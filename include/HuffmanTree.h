#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

#include <cfloat>   // for DBL_MAX
#include <iomanip>  // for setw()

#include "BinaryTree.h"
#include "PriorityQueue.h"
#include "SeqStack.h"

namespace datastructures
{

/**
 * @brief Huffman树节点类
 * @tparam elemType 节点数据的类型
 */
template <class elemType>
class HuffmanTreeNode : public BaseNode<elemType>
{
   public:
    double weight;  ///< 节点权重
    int index;
    HuffmanTreeNode<elemType>*parent, *left, *right;

    HuffmanTreeNode() : BaseNode<elemType>(elemType()), weight(0), index(-1), parent(nullptr) {}

    HuffmanTreeNode(const elemType& data, double w = 0, int index = -1,
                    HuffmanTreeNode<elemType>* l = nullptr, HuffmanTreeNode<elemType>* r = nullptr,
                    HuffmanTreeNode<elemType>* p = nullptr)
        : BaseNode<elemType>(data), weight(w), index(index), parent(p)
    {
        this->left = l;
        this->right = r;
    }

    // Operator overloads for PriorityQueue comparison
    bool operator<(const HuffmanTreeNode& other) const { return weight < other.weight; }
    bool operator<=(const HuffmanTreeNode& other) const { return weight <= other.weight; }
};

/**
 * @brief Huffman树类
 * @tparam elemType 节点数据的类型
 */
template <class elemType>
class HuffmanTree : public BTree<elemType, HuffmanTreeNode<elemType>>
{
   private:
    using Node = HuffmanTreeNode<elemType>;

    // 找到权重最小的节点
    int findMinNode(int k)
    {
        double minWeight = DBL_MAX;
        int minIndex = -1;

        // 遍历查找最小权重节点
        for (int i = m - 1; i > k; i--) {
            if (nodes[i]->parent == nullptr && nodes[i]->weight < minWeight) {
                minWeight = nodes[i]->weight;
                minIndex = i;
            }
        }
        return minIndex;
    }

   public:
    int n = 0;
    // 将 nodes 数组作为类的成员变量
    Node** nodes;  ///< 存储所有的节点
    int m;         ///< 用于计算节点数组的大小，2n个节点

    HuffmanTree() : BTree<elemType, Node>(), nodes(nullptr), m(0) {}

    ~HuffmanTree()
    {
        if (nodes != nullptr) {
            delete[] nodes;  // 释放节点数组
        }
    }

    void disp();

    /**
     * @brief 构建Huffman树
     * @param data 数据数组
     * @param weights 权重数组
     * @param n 数组长度
     */
    void buildTree(const elemType data[], const double weights[], int n)
    {
        if (n <= 0) {
            // 没有结点就不构造哈夫曼树
            return;
        }
        this->n = n;

        m = 2 * n;             // 2n 个节点,共2n-1个节点，下标为0处不放节点
        nodes = new Node*[m];  // 动态分配节点数组

        // 初始化叶子节点
        for (int j = 0; j < n; j++) {
            nodes[m - 1 - j] = new Node(data[j], weights[j], m - 1 - j);
        }

        // 构建Huffman树
        for (int i = n - 1; i != 0; i--) {
            Node* new_parent_node = new Node(elemType());

            int min1 = findMinNode(i);
            nodes[min1]->parent = new_parent_node;

            int min2 = findMinNode(i);
            nodes[min2]->parent = new_parent_node;

            new_parent_node->weight = nodes[min1]->weight + nodes[min2]->weight;
            new_parent_node->left = nodes[min1];
            new_parent_node->right = nodes[min2];
            new_parent_node->index = i;
            nodes[i] = new_parent_node;
        }

        // 设置根节点
        this->root = nodes[1];
    }

    /**
     * @brief 使用优先级队列构建Huffman树
     * @param pq 包含初始节点的优先级队列
     */
    void buildTree(PriorityQueue<Node>& pq)
    {
        if (pq.isEmpty()) {
            return;
        }

        n = pq.getSize();
        m = 2 * n;             // 2n 个节点,共2n-1个节点，下标为0处不放节点
        nodes = new Node*[m];  // 动态分配节点数组

        // 初始化叶子节点
        for (int j = 0; j < n; j++) {
            Node temp = pq.front();
            nodes[m - 1 - j] = new Node(temp.data, temp.weight, m - 1 - j);
            pq.deQueue();
        }

        // 构建新的优先级队列用于构建树
        PriorityQueue<Node> tempQueue(n);
        for (int j = 0; j < n; j++) {
            tempQueue.enQueue(*nodes[m - 1 - j]);
        }

        // 构建Huffman树
        for (int i = n - 1; i != 0; i--) {
            Node* new_parent_node = new Node(elemType());

            // 获取第一个最小权重节点
            Node min1 = tempQueue.front();
            tempQueue.deQueue();
            nodes[min1.index]->parent = new_parent_node;

            // 获取第二个最小权重节点
            Node min2 = tempQueue.front();
            tempQueue.deQueue();
            nodes[min2.index]->parent = new_parent_node;

            // 创建新的父节点
            new_parent_node->weight = nodes[min1.index]->weight + nodes[min2.index]->weight;
            new_parent_node->left = nodes[min1.index];
            new_parent_node->right = nodes[min2.index];
            new_parent_node->index = i;
            nodes[i] = new_parent_node;

            // 将新节点加入优先级队列
            tempQueue.enQueue(*new_parent_node);
        }

        // 设置根节点
        this->root = nodes[1];
    }

    char** HuffmanCode(char** codes, int n)
    {
        SeqStack<char> s;
        char** HFCode;

        // If codes is not provided, allocate new memory
        if (codes == nullptr) {
            HFCode = new char*[n];
            for (int i = 0; i < n; i++) {
                HFCode[i] = new char[n + 1];  // 每位元素编码最长n-1位，+1时为n=1是储备
            }
        } else {
            HFCode = codes;
        }

        char zero = '0', one = '1';
        int child;
        HuffmanTreeNode<elemType>* parent = nullptr;

        if (n == 0) {
            return HFCode;
        }

        if (n == 1) {
            HFCode[0][0] = '0';
            HFCode[0][1] = '\0';
            return HFCode;
        }

        m = 2 * n;

        for (int i = m - 1; i >= n; i--) {
            child = i;
            parent = nodes[child]->parent;
            while (parent != nullptr) {
                if (parent->left->index == child) {
                    s.push(zero);
                } else {
                    s.push(one);
                }

                child = parent->index;
                parent = nodes[child]->parent;
            }

            int j = 0;
            while (!s.isEmpty()) {
                HFCode[m - i - 1][j] = s.top();
                s.pop();
                j++;
            }

            HFCode[m - i - 1][j] = '\0';
        }
        return HFCode;
    }
};

template <class elemType>
void HuffmanTree<elemType>::disp()
{
    // 输出表头，使用setw来设置列宽
    std::cout << std::setw(6) << "Index" << std::setw(8) << "Data" << std::setw(8) << "Weight"
              << std::setw(10) << "Parent" << std::setw(8) << "Left" << std::setw(8) << "Right"
              << std::endl;

    std::cout << "-------------------------------------------------------------\n";

    // 输出每个节点的信息
    for (int i = 1; i <= m; i++) {
        Node* node = nodes[i];
        if (node == nullptr) continue;

        // 输出索引、数据、权重
        std::cout << std::setw(6) << i << std::setw(8) << node->data << std::setw(8)
                  << node->weight;

        // 输出父节点的索引
        if (node->parent) {
            std::cout << std::setw(10) << (node->parent->index);  // 父节点的索引
        } else {
            std::cout << std::setw(10) << "None";  // 没有父节点
        }

        // 输出左子节点的索引
        if (node->left) {
            std::cout << std::setw(8) << (node->left->index);  // 左子节点的索引
        } else {
            std::cout << std::setw(8) << "None";  // 没有左子节点
        }

        // 输出右子节点的索引
        if (node->right) {
            std::cout << std::setw(8) << (node->right->index);  // 右子节点的索引
        } else {
            std::cout << std::setw(8) << "None";  // 没有右子节点
        }

        std::cout << std::endl;
    }
}
}  // namespace datastructures

#endif  // HUFFMAN_TREE_H
