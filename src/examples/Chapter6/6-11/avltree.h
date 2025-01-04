template <class elemType>
class binaryAVLSearchTree;

template <class elemType>
class AVLNode
{
    friend class binaryAVLSearchTree<elemType>;

   private:
    elemType data;
    AVLNode *left, *right;
    int height;  // 记录以该结点为根的二叉树的高度

   public:
    AVLNode()
    {
        left = NULL;
        right = NULL;
        height = 1;
    }
    AVLNode(const elemType &x, AVLNode *l = NULL, AVLNode *r = NULL, int h = 1)
    {
        data = x;
        left = l;
        right = r;
        height = h;
    }
};

template <class elemType>
class binaryAVLSearchTree
{
   private:
    AVLNode<elemType> *root;
    bool search(const elemType &x, AVLNode<elemType> *t) const;
    void insert(const elemType &x, AVLNode<elemType> *&t);
    void remove(const elemType &x, AVLNode<elemType> *&t);

    void LL(AVLNode<elemType> *&t);
    void RR(AVLNode<elemType> *&t);

    void LR(AVLNode<elemType> *&t);
    void RL(AVLNode<elemType> *&t);
    int height(AVLNode<elemType> *t) const;
    int max(int a, int b) { return (a > b) ? a : b; }

   public:
    binaryAVLSearchTree() { root = NULL; }
    bool search(const elemType &x) const;
    void insert(const elemType &x);
    void remove(const elemType &x);
    ~binaryAVLSearchTree();
};

template <class elemType>
int binaryAVLSearchTree<elemType>::height(AVLNode<elemType> *t) const
{
    if (!t) return 0;
    return t->height;
}

// 下面就是LL，RR，LR，RL四种旋转操作
template <class elemType>
void binaryAVLSearchTree<elemType>::LL(AVLNode<elemType> *&t)
{
    AVLNode<elemType> *newRoot = t->left;  // 旋转后的新根结点
    t->left = newRoot->right;
    newRoot->right = t;
    t->height = max(height(t->left), height(t->right)) + 1;
    newRoot->height = max(height(newRoot->left), t->height) + 1;
    t = newRoot;  // 新的父子关联
}

template <class elemType>
void binaryAVLSearchTree<elemType>::RR(AVLNode<elemType> *&t)
{
    AVLNode<elemType> *newRoot = t->right;  // 旋转后的新根结点
    t->right = newRoot->left;
    newRoot->left = t;
    t->height = max(height(t->left), height(t->right)) + 1;
    newRoot->height = max(height(newRoot->right), t->height) + 1;
    t = newRoot;  // 新的父子关联
}

template <class elemType>
void binaryAVLSearchTree<elemType>::LR(AVLNode<elemType> *&t)
{
    RR(t->left);
    LL(t);
}

template <class elemType>
void binaryAVLSearchTree<elemType>::RL(AVLNode<elemType> *&t)
{
    LL(t->right);
    RR(t);
}
