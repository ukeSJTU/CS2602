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
template <class elemType>
void binarySearchTree<elemType>::insert(const elemType &x)
{
    insert(x, root);
}