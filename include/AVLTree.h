template <class elemType>
class AVL_Tree;

template <class elemType>
class Node
{
    friend class AVL_Tree<elemType>;

   private:
    elemType data;
    Node *left, *right;
    int height;

   public:
    Node()
    {
        left = NULL;
        right = NULL;
        height = 1;
    }
    Node(const elemType &x, Node *l = NULL, Node *r = NULL, int h = 1)
    {
        data = x;
        left = l;
        right = r;
        height = h;
    }
};

template <class elemType>
class AVL_Tree
{
   private:
    Node<elemType> *root;
    bool search(const elemType &x, Node<elemType> *t) const;
    void insert(const elemType &x, Node<elemType> *&t);
    void remove(const elemType &x, Node<elemType> *&t);

    void LL(Node<elemType> *&t);
    void RR(Node<elemType> *&t);

    void LR(Node<elemType> *&t);
    void RL(Node<elemType> *&t);
    int height(Node<elemType> *t) const;
    int max(int a, int b) { return (a > b) ? a : b; }

   public:
    AVL_Tree() { root = NULL; }
    bool search(const elemType &x) const;
    void insert(const elemType &x);
    void remove(const elemType &x);
    ~AVL_Tree();
};

template <class elemType>
int AVL_Tree<elemType>::height(Node<elemType> *t) const
{
    if (!t) return 0;  // 空节点的高度为0
    return t->height;  // 返回当前节点的高度
}

template <class elemType>
void AVL_Tree<elemType>::insert(const elemType &x, Node<elemType> *&t)
{
    // 如果当前节点为空，则插入新节点
    if (!t) t = new Node<elemType>(x);  // 新节点的高度默认为1

    // 如果插入元素已存在，直接返回
    else if (x == t->data)
        return;

    // **插入到左子树**
    else if (x < t->data) {
        insert(x, t->left);  // 递归插入到左子树

        // **检查平衡性**
        if (height(t->left) - height(t->right) == 2)  // 左子树高度增加，导致不平衡
        {
            if (x < t->left->data)  // 插入到了左子树的左孩子（LL型）
                LL(t);
            else  // 插入到了左子树的右孩子（LR型）
                LR(t);
        } else
            // 更新当前节点的高度
            t->height = max(height(t->left), height(t->right)) + 1;
    }

    // **插入到右子树**
    else if (x > t->data) {
        insert(x, t->right);  // 递归插入到右子树

        // **检查平衡性**
        if (height(t->left) - height(t->right) == -2)  // 右子树高度增加，导致不平衡
        {
            if (x > t->right->data)  // 插入到了右子树的右孩子（RR型）
                RR(t);
            else  // 插入到了右子树的左孩子（RL型）
                RL(t);
        } else
            // 更新当前节点的高度
            t->height = max(height(t->left), height(t->right)) + 1;
    }
}

template <class elemType>
void AVL_Tree<elemType>::LL(Node<elemType> *&t)
{
    Node<elemType> *newRoot = t->left;  // 左子节点成为新根
    t->left = newRoot->right;           // 原根的左子树指向新根的右子树
    newRoot->right = t;                 // 新根的右子树指向原根

    // 更新高度
    t->height = max(height(t->left), height(t->right)) + 1;
    newRoot->height = max(height(newRoot->left), height(newRoot->right)) + 1;

    t = newRoot;  // 更新当前子树的根节点
}
template <class elemType>
void AVL_Tree<elemType>::RR(Node<elemType> *&t)
{
    Node<elemType> *newRoot = t->right;  // 树根
    t->right = newRoot->left;
    newRoot->left = t;
    t->height = max(height(t->left), height(t->right)) + 1;
    newRoot->height = max(height(newRoot->left), height(height(newRoot->right))) + 1;
    t = newRoot;
}

template <class elemType>
void AVL_Tree<elemType>::LR(Node<elemType> *&t)
{
    RR(t->left);
    LL(t);
}

template <class elemType>
void AVL_Tree<elemType>::RL(Node<elemType> *&t)
{
    LL(t->right);
    RR(t);
}
