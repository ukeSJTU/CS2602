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
 * @brief 哈夫曼树节点类
 * @tparam ElementType 节点数据的类型
 */
template <class ElementType>
class HuffmanTreeNode : public BaseNode<ElementType>
{
   public:
    double weight;                         ///< 节点权重
    int index;                             ///< 节点索引
    HuffmanTreeNode<ElementType>* parent;  ///< 父节点指针
    HuffmanTreeNode<ElementType>* left;    ///< 左子节点指针
    HuffmanTreeNode<ElementType>* right;   ///< 右子节点指针

    /**
     * @brief 默认构造函数
     */
    HuffmanTreeNode();

    /**
     * @brief 带参数的构造函数
     * @param data 节点数据
     * @param w 节点权重
     * @param idx 节点索引
     * @param l 左子节点指针
     * @param r 右子节点指针
     * @param p 父节点指针
     */
    HuffmanTreeNode(const ElementType& data, double w = 0, int idx = -1,
                    HuffmanTreeNode<ElementType>* l = nullptr,
                    HuffmanTreeNode<ElementType>* r = nullptr,
                    HuffmanTreeNode<ElementType>* p = nullptr);

    /**
     * @brief 小于运算符重载，用于优先级队列比较
     * @param other 另一个节点
     * @return 如果当前节点权重小于other节点权重，返回true
     */
    bool operator<(const HuffmanTreeNode& other) const;

    /**
     * @brief 小于等于运算符重载，用于优先级队列比较
     * @param other 另一个节点
     * @return 如果当前节点权重小于等于other节点权重，返回true
     */
    bool operator<=(const HuffmanTreeNode& other) const;
};

/**
 * @brief 哈夫曼树类
 * @tparam ElementType 节点数据的类型
 */
template <class ElementType>
class HuffmanTree : public BTree<ElementType, HuffmanTreeNode<ElementType>>
{
   private:
    using Node = HuffmanTreeNode<ElementType>;

    /**
     * @brief 查找权重最小的节点
     * @param k 查找范围的上限
     * @return 最小权重节点的索引
     */
    int findMinNode(int k);

   public:
    int n;         ///< 叶子节点数量
    Node** nodes;  ///< 存储所有节点的数组
    int m;         ///< 节点数组的大小，为2n

    /**
     * @brief 默认构造函数
     */
    HuffmanTree();

    /**
     * @brief 析构函数
     */
    ~HuffmanTree();

    /**
     * @brief 显示哈夫曼树的结构
     */
    void disp();

    /**
     * @brief 使用数据和权重数组构建哈夫曼树
     * @param data 数据数组
     * @param weights 权重数组
     * @param size 数组长度
     */
    void buildTree(const ElementType data[], const double weights[], int size);

    /**
     * @brief 使用优先级队列构建哈夫曼树
     * @param pq 包含初始节点的优先级队列
     */
    void buildTree(PriorityQueue<Node>& pq);

    /**
     * @brief 生成哈夫曼编码
     * @param codes 存储编码的二维字符数组，如果为nullptr则会新建
     * @param size 数组大小
     * @return 返回哈夫曼编码的二维字符数组
     */
    char** HuffmanCode(char** codes, int size);
};

template <class ElementType>
HuffmanTreeNode<ElementType>::HuffmanTreeNode()
    : BaseNode<ElementType>(ElementType()),
      weight(0),
      index(-1),
      parent(nullptr),
      left(nullptr),
      right(nullptr)
{
}

template <class ElementType>
HuffmanTreeNode<ElementType>::HuffmanTreeNode(const ElementType& data, double w, int idx,
                                              HuffmanTreeNode<ElementType>* l,
                                              HuffmanTreeNode<ElementType>* r,
                                              HuffmanTreeNode<ElementType>* p)
    : BaseNode<ElementType>(data), weight(w), index(idx), parent(p), left(l), right(r)
{
}

template <class ElementType>
bool HuffmanTreeNode<ElementType>::operator<(const HuffmanTreeNode& other) const
{
    return weight < other.weight;
}

template <class ElementType>
bool HuffmanTreeNode<ElementType>::operator<=(const HuffmanTreeNode& other) const
{
    return weight <= other.weight;
}

template <class ElementType>
HuffmanTree<ElementType>::HuffmanTree() : BTree<ElementType, Node>(), nodes(nullptr), m(0), n(0)
{
}

template <class ElementType>
HuffmanTree<ElementType>::~HuffmanTree()
{
    if (nodes != nullptr) {
        delete[] nodes;
    }
}

template <class ElementType>
int HuffmanTree<ElementType>::findMinNode(int k)
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

template <class ElementType>
void HuffmanTree<ElementType>::buildTree(const ElementType data[], const double weights[], int size)
{
    if (size <= 0) {
        return;  // 没有节点就不构造哈夫曼树
    }

    this->n = size;
    m = 2 * size;          // 2n个节点，共2n-1个节点，下标为0处不放节点
    nodes = new Node*[m];  // 动态分配节点数组

    // 初始化叶子节点
    for (int j = 0; j < size; j++) {
        nodes[m - 1 - j] = new Node(data[j], weights[j], m - 1 - j);
    }

    // 构建哈夫曼树
    for (int i = size - 1; i != 0; i--) {
        Node* newParentNode = new Node(ElementType());

        int min1 = findMinNode(i);
        nodes[min1]->parent = newParentNode;

        int min2 = findMinNode(i);
        nodes[min2]->parent = newParentNode;

        newParentNode->weight = nodes[min1]->weight + nodes[min2]->weight;
        newParentNode->left = nodes[min1];
        newParentNode->right = nodes[min2];
        newParentNode->index = i;
        nodes[i] = newParentNode;
    }

    // 设置根节点
    this->root = nodes[1];
}

template <class ElementType>
void HuffmanTree<ElementType>::buildTree(PriorityQueue<Node>& pq)
{
    if (pq.isEmpty()) {
        return;
    }

    n = pq.getSize();
    m = 2 * n;             // 2n个节点，共2n-1个节点，下标为0处不放节点
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

    // 构建哈夫曼树
    for (int i = n - 1; i != 0; i--) {
        Node* newParentNode = new Node(ElementType());

        // 获取第一个最小权重节点
        Node min1 = tempQueue.front();
        tempQueue.deQueue();
        nodes[min1.index]->parent = newParentNode;

        // 获取第二个最小权重节点
        Node min2 = tempQueue.front();
        tempQueue.deQueue();
        nodes[min2.index]->parent = newParentNode;

        // 创建新的父节点
        newParentNode->weight = nodes[min1.index]->weight + nodes[min2.index]->weight;
        newParentNode->left = nodes[min1.index];
        newParentNode->right = nodes[min2.index];
        newParentNode->index = i;
        nodes[i] = newParentNode;

        // 将新节点加入优先级队列
        tempQueue.enQueue(*newParentNode);
    }

    // 设置根节点
    this->root = nodes[1];
}

template <class ElementType>
char** HuffmanTree<ElementType>::HuffmanCode(char** codes, int size)
{
    SeqStack<char> s;
    char** huffmanCode;

    // 如果codes为空，分配新内存
    if (codes == nullptr) {
        huffmanCode = new char*[size];
        for (int i = 0; i < size; i++) {
            huffmanCode[i] = new char[size + 1];  // 每个元素编码最长n-1位，+1为n=1时的储备
        }
    } else {
        huffmanCode = codes;
    }

    char zero = '0', one = '1';
    int child;
    Node* parent = nullptr;

    if (size == 0) {
        return huffmanCode;
    }

    if (size == 1) {
        huffmanCode[0][0] = '0';
        huffmanCode[0][1] = '\0';
        return huffmanCode;
    }

    m = 2 * size;

    for (int i = m - 1; i >= size; i--) {
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
            huffmanCode[m - i - 1][j] = s.top();
            s.pop();
            j++;
        }

        huffmanCode[m - i - 1][j] = '\0';
    }
    return huffmanCode;
}

template <class ElementType>
void HuffmanTree<ElementType>::disp()
{
    // 输出表头
    std::cout << std::setw(6) << "索引" << std::setw(8) << "数据" << std::setw(8) << "权重"
              << std::setw(10) << "父节点" << std::setw(8) << "左子" << std::setw(8) << "右子"
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
            std::cout << std::setw(10) << node->parent->index;
        } else {
            std::cout << std::setw(10) << "无";
        }

        // 输出左子节点的索引
        if (node->left) {
            std::cout << std::setw(8) << node->left->index;
        } else {
            std::cout << std::setw(8) << "无";
        }

        // 输出右子节点的索引
        if (node->right) {
            std::cout << std::setw(8) << node->right->index;
        } else {
            std::cout << std::setw(8) << "无";
        }

        std::cout << std::endl;
    }
}

}  // namespace datastructures

#endif  // HUFFMAN_TREE_H
