// TODO：这个二叉搜索树的实现必须调整，注意命名空间，变量名冲突以及和普通二叉树的继承/组合关系
#ifndef BINARYSEARCHTREE_H_INCLUDED
#define BINARYSEARCHTREE_H_INCLUDED

template <class elemType>
class binarySearchTree;

template <class elemType>
class Node
{
    friend class binarySearchTree<elemType>;

   private:
    elemType data;
    Node *left, *right;
    int factor;  // 平衡因子
   public:
    Node()
    {
        left = nullptr;
        right = nullptr;
    }
    Node(const elemType &x, Node *l = nullptr, Node *r = nullptr)
    {
        data = x;
        left = l;
        right = r;
    }
};
template <class elemType>
class binarySearchTree
{
   private:
    Node<elemType> *root;
    bool search(const elemType &x, Node<elemType> *t) const;
    void insert(const elemType &x, Node<elemType> *&t);
    void remove(const elemType &x, Node<elemType> *&t);

   public:
    binarySearchTree() { root = nullptr; }
    bool search(const elemType &x) const;
    void insert(const elemType &x);
    void remove(const elemType &x);
    void levelTravese() const;  // 层次遍历,用于验证插入、删除操作
    ~binarySearchTree();
};

template <class elemType>
bool binarySearchTree<elemType>::search(const elemType &x) const
{
    Node<elemType> *p;
    p = root;
    while (p) {
        if (x == p->data) return true;
        if (x < p->data)
            p = p->left;
        else
            p = p->right;
    }
    return false;
}

template <class elemType>  // 非递归算法实现
void binarySearchTree<elemType>::insert(const elemType &x)
{
    Node<elemType> *p;
    if (!root)  // 如果查找树的根为空，直接建立一个结点并作为根结点
    {
        root = new Node<elemType>(x);
        return;
    }
    p = root;
    while (p) {
        if (x == p->data) return;  // 已经在二叉树中
        if (x < p->data) {
            if (!p->left)  // 左子为空，插入位置即此地
            {
                p->left = new Node<elemType>(x);
                return;
            }
            p = p->left;
        } else {
            if (!p->right)  // 右子为空，插入位置即此地
            {
                p->right = new Node<elemType>(x);
                return;
            }
            p = p->right;
        }  // if
    }  // while
}

template <class elemType>  // 非递归算法实现
void binarySearchTree<elemType>::remove(const elemType &x)
{
    if (!root) return;
    Node<elemType> *p, *parent;
    p = root;

    parent = nullptr;
    while (p) {
        if (x < p->data) {
            parent = p;
            p = p->left;
            continue;
        }
        if (x > p->data) {
            parent = p;
            p = p->right;
            continue;
        }
        // x==p->data, 删除开始
        if (!p->left || !p->right)  // 待删除结点仅有一个孩子结点或者为叶结点
        {
            Node<elemType> *tmp;
            tmp = p;
            if (!parent)  // 待删除结点为根，且根有一个孩子
                root = (p->left) ? p->left : p->right;
            else if (x < parent->data)  // 待删除结点为父结点的左子
                parent->left = (p->left) ? p->left : p->right;
            else  // 待删除结点为父结点的右子
                parent->right = (p->left) ? p->left : p->right;
            delete tmp;
            return;
        }  // 仅有一个孩子

        // 待删除结点有二个孩子结点
        Node<elemType> *q, *substitute;
        parent = p;
        q = p->left;
        while (q->right) {
            parent = q;
            q = q->right;
        }
        substitute = q;

        // 交换待删除结点和替身的元素值
        p->data = substitute->data;
        substitute->data = x;
        p = substitute;  // 删除结点指针变为替身继续返回循环
    }  // while
}

#endif  // BINARYSEARCHTREE_H_INCLUDED