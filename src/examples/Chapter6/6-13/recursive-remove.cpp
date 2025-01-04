template <class elemType>
void binaryAVLSearchTree<elemType>::remove(const elemType &x, AVLNode<elemType> *&t)
{
    if (!t)
        return;  // 未找到
    else if (x < t->data) {
        // 在左子树中删除
        remove(x, t->left);

        // t为冲突节点
        if (height(t->right) - height(t->left) == 2) {
            if (height(t->right->right) > height(t->right->left))
                RR(t);
            else
                RL(t);
        } else  // 重新计算t的高度
            t->height = max(height(t->left), height(t->right)) + 1;
    } else if (x > t->data) {
        // 在右子树中删除
        remove(x, t->right);

        // t为冲突节点
        if (height(t->left) - height(t->right) == 2) {
            if (height(t->left->left) > height(t->left->right))
                LL(t);
            else
                LR(t);
        } else {
            t->height = max(height(t->left), height(t->right)) + 1;
        }
    }
    // 删除开始
    else {
        // 删除x
        if (!t->left || !t->right) {  // t为叶子或者只有一个孩子
            AVLNode<elemType> *tmp;
            tmp = t;
            t = (t->left) ? t->left : t->right;  // 父结点链接其唯一的孩子结点
            delete tmp;
            return;
        }

        // 删除有两个孩子的结点
        AVLNode<elemType> *p, *substitute;
        p = t->right;
        while (p->left) p = p->left;

        substitute = p;

        t->data = substitute->data;
        remove(substitute->data, t->right);
    }
}