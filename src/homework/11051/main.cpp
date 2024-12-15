#include <iostream>

class Node
{
   public:
    int data;    // 存储数据
    Node* next;  // 指向下一个节点

    Node(int value) : data(value), next(nullptr) {}  // 构造函数
};

class LinkList
{
   private:
    Node* head;       // 链表头节点
    int comparisons;  // 总的比较次数

   public:
    LinkList() : head(nullptr), comparisons(0) {}

    // 插入节点到链表尾部
    void insert(int value)
    {
        if (head == nullptr) {
            head = new Node(value);
        } else {
            Node* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = new Node(value);
        }
    }

    // 查找节点并移动到表头，返回是否找到
    bool findAndMoveToFront(int value)
    {
        Node* prev = nullptr;
        Node* current = head;

        while (current != nullptr) {
            comparisons++;  // 每次比较计数
            if (current->data == value) {
                // 如果是第一个节点，直接返回
                if (prev == nullptr) {
                    return true;
                }
                // 否则将节点移到表头
                prev->next = current->next;
                current->next = head;
                head = current;
                return true;
            }
            prev = current;
            current = current->next;
        }
        return false;  // 未找到
    }

    // 获取总的比较次数
    int getComparisons() const { return comparisons; }

    // 清理链表内存
    ~LinkList()
    {
        Node* current = head;
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }
};

int main()
{
    int n;
    std::cin >> n;

    LinkList list;
    int value;

    // 读取静态查找表
    for (int i = 0; i < n; ++i) {
        std::cin >> value;
        list.insert(value);
    }

    int m;
    std::cin >> m;

    // 模拟查找过程
    for (int i = 0; i < m; ++i) {
        std::cin >> value;
        list.findAndMoveToFront(value);
    }

    // 输出总的比较次数
    std::cout << list.getComparisons() << std::endl;

    return 0;
}