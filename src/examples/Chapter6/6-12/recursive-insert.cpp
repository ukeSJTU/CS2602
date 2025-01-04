template <class elemType>
void binaryAVLSearchTree<elemType>::insertAVL(const elemType &x, AVLNode<elemType> *&t)
{
    if (!t)
        t = new AVLNode<elemType>(x);
    else if (x == t->data)
        return;
    else if (x < t->data) {
        // 在左子树上插入
        insert(x, t->left);
        if (height(t->left) - height(t->right) == 2) {
            // t为冲突结点
            if (x < t->left->data)
                LL(t);
            else
                LR(t);
        }
    } else {
        // 在右子树上插入
        insert(x, t->right);
        if (height(t->right) - height(t->left) == 2) {
            // t为冲突结点
            if (x > t->right->data)
                RR(t);
            else
                RL(t);
        }
    }

    // 重新计算t的高度
    t->height = max(height(t->left), height(t->right)) + 1;
}