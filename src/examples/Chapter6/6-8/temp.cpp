// 递归程序：
template <class elemType>  // 递归算法实现
void binarySearchTree<elemType>::remove(const elemType &x, Node<elemType> *&t)
{
    if (!t) return;
    if (x < t->data)
        remove(x, t->left);
    else if (x > t->data)
        remove(x, t->right);
    else {
        if (!t->left || !t->right)  // 待删除结点只有一个孩子，或者是叶子结点
        {
            Node<elemType> *tmp;
            tmp = t;
            t = (t->left) ? t->left : t->right;  // 父结点链接其唯一孩子结点
            delete tmp;                          // 释放待删除结点
            return;
        }
        // 待删除结点有两个孩子的情况
        Node<elemType> *p, *substitute;
        p = t->right;
        while (p->left) p = p->left;
        substitute = p;
        t->data = substitute->data;
        remove(substitute->data, t->right);
    }
}
