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
}  // 尾递归，无回溯，非递归不需要栈