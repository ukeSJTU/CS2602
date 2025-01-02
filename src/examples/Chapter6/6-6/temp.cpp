template <class elemType>  // 递归算法实现
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

// 非递归程序的第二种方法：PPT上提到两种方法，第一种和书本上一样，我放到了头文件中，第二种非递归方法就是下面这个
template <class elemType>  // 非递归算法实现
void binarySearchTree<elemType>::insert(const elemType &x)
{
    Node<elemType> *p, *tmp, *parent = NULL;
    p = root;

    while (p) {
        if (x == p->data) return;  // 已存在，无需插入

        parent = p;
        if (x < p->data)
            p = p->left;  // p为其父parent的左子
        else
            p = p->right;  // p为其父parent的右子
    }

    tmp = new Node<elemType>(x);
    if (!parent) {
        root = tmp;
        return;
    }  // parent为空，表示二叉树为空
      if (x<parent->data parent->left = tmp;
      else  parent->right = tmp;
}
