template <class elemtype>
void binarySearchTree<elemType>::remove(const elemType &x)
{
    if (!root) return;

    Node<elemtype> *p, *parent;
    p = root;
    parent = NULL;

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

        // 删除开始
        if (!p->left && !p->right)  // 叶子结点
        {
            delete p;

            // 待删除结点为根，且根为叶子结点
            if (!parent) {
                root = NULL;
                return;
            }

            // 待删除结点为父结点的左子
            if (parent->left == p)
                parent->left = NULL;
            else
                parent->right = NULL;
        }

        if (!p->left || !p->right)  // 待删除结点仅有一个孩子结点
        {
            Node<elemtype> *tmp;
            tmp = p;

            if (!parent)  // 待删除结点为根

                root = (p->left) ? p->left : p->right;
            else {
                if (x < parent->data)
                    parent->left = (p->left) ? p->left : p->right;
                else
                    parent->right = (p->left) ? p->left : p->right;
            }

            delete tmp;
            return;
        }

        // 待删除结点有两个孩子结点
        Node<elemType> *q, *substitute;
        parent = p;
        q = p->left;
        while (q->right) {
            parent = q;
            q = q->right;
        }
        substitute = q;

        // 交换待删除的结点和替身的元素值
        p->data = substitute->data;
        substitue->data = x;

        p = substitute;  // 待删除的结点指针变成替身，继续回到循环
    }
}