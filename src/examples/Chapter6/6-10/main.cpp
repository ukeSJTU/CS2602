#include <iostream>
#include <queue>

using namespace std;

// ======================
//       Node 类
// ======================
template <class elemType>
class binarySearchTree;

template <class elemType>
class Node
{
    friend class binarySearchTree<elemType>;

   private:
    elemType data;
    Node *left, *right;

   public:
    Node() : left(NULL), right(NULL) {}
    Node(const elemType &x, Node *l = NULL, Node *r = NULL) : data(x), left(l), right(r) {}
};

// ======================
//    binarySearchTree 类
// ======================
template <class elemType>
class binarySearchTree
{
   private:
    Node<elemType> *root;
    bool search(const elemType &x, Node<elemType> *t) const;
    void insert(const elemType &x, Node<elemType> *&t);
    void remove(const elemType &x, Node<elemType> *&t);

   public:
    binarySearchTree() : root(NULL) {}
    bool search(const elemType &x) const;
    void insert(const elemType &x);
    void remove(const elemType &x);
    void levelTraverse() const;  // 层次遍历,用于验证插入、删除操作
    ~binarySearchTree();
};

// ======================
// binarySearchTree 方法实现
// ======================

// 搜索元素
template <class elemType>
bool binarySearchTree<elemType>::search(const elemType &x, Node<elemType> *t) const
{
    if (!t) {
        return false;
    }
    if (x == t->data) {
        return true;
    }
    if (x < t->data) {
        return search(x, t->left);
    } else {
        return search(x, t->right);
    }
}

template <class elemType>
bool binarySearchTree<elemType>::search(const elemType &x) const
{
    return search(x, root);
}

// 插入元素
template <class elemType>
void binarySearchTree<elemType>::insert(const elemType &x, Node<elemType> *&t)
{
    if (!t) {
        t = new Node<elemType>(x);
        return;
    }
    if (x == t->data) return;  // 已存在，结束插入
    if (x < t->data)
        insert(x, t->left);
    else
        insert(x, t->right);
}

template <class elemType>
void binarySearchTree<elemType>::insert(const elemType &x)
{
    insert(x, root);
}

// 层次遍历
template <class elemType>
void binarySearchTree<elemType>::levelTraverse() const
{
    if (!root) return;
    queue<Node<elemType> *> q;
    q.push(root);
    while (!q.empty()) {
        Node<elemType> *current = q.front();
        q.pop();
        cout << current->data << " ";
        if (current->left) q.push(current->left);
        if (current->right) q.push(current->right);
    }
    cout << endl;
}

// 删除元素
template <class elemType>
void binarySearchTree<elemType>::remove(const elemType &x, Node<elemType> *&t)
{
    if (!t) return;
    if (x < t->data)
        remove(x, t->left);
    else if (x > t->data)
        remove(x, t->right);
    else {
        if (!t->left && !t->right) {
            delete t;
            t = NULL;
            return;
        }

        if (!t->left || !t->right) {
            Node<elemType> *tmp = t;
            t = (t->left) ? t->left : t->right;
            delete tmp;
            return;
        }

        Node<elemType> *p = t->right;
        while (p->left) p = p->left;
        t->data = p->data;
        remove(p->data, t->right);
    }
}

template <class elemType>
void binarySearchTree<elemType>::remove(const elemType &x)
{
    remove(x, root);
}

// 析构函数
template <class elemType>
binarySearchTree<elemType>::~binarySearchTree()
{
    queue<Node<elemType> *> nodes;
    if (root) {
        nodes.push(root);
    }
    while (!nodes.empty()) {
        Node<elemType> *current = nodes.front();
        nodes.pop();
        if (current->left) {
            nodes.push(current->left);
        }
        if (current->right) {
            nodes.push(current->right);
        }
        delete current;
    }
}

// ======================
//       主函数
// ======================
int main()
{
    binarySearchTree<int> bst;

    int a[10] = {15, 30, 20, 80, 10, 5, 40, 60, 90, 2};
    int x, i;

    cout << "== 插入元素 ==" << endl;
    for (i = 0; i < 10; i++) {
        bst.insert(a[i]);
    }
    cout << "层次遍历: ";
    bst.levelTraverse();

    cout << "== 删除叶子结点 ==" << endl;
    bst.remove(a[9]);
    bst.levelTraverse();

    cout << "== 删除有一个孩子的结点 ==" << endl;
    bst.remove(a[6]);
    bst.levelTraverse();

    cout << "== 删除有两个孩子的结点 ==" << endl;
    bst.remove(a[0]);
    bst.levelTraverse();

    cout << "== 搜索元素x ==" << endl;
    cout << "x: ";
    cin >> x;
    if (bst.search(x)) {
        cout << "元素" << x << "存在" << endl;
    } else {
        cout << "元素" << x << "不存在" << endl;
    }

    return 0;
}