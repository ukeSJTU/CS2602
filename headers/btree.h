#ifndef BTREE_H_
#define BTREE_H_

#include <iostream>
#include "seqStack.h"
#include "seqQueue.h"

template <class elemType>
class BTree;

template <class elemType>
class Node
{
    friend class BTree<elemType>;

private:
    elemType data;
    Node *left, *right;
    int leftFlag, rightFlag;

public:
    Node()
    {
        left = nullptr;
        right = nullptr, leftFlag = 0;
        rightFlag = 0;
    }
    Node(const elemType &x, Node *L = nullptr, Node *R = nullptr)
    {
        data = x;
        left = L;
        right = R;
        leftFlag = 0;
        rightFlag = 0;
    }
};

template <class elemType>
class BTree
{
private:
    Node<elemType> *root;
    int height(Node<elemType> *t);
    int size(Node<elemType> *t);
    void delTree(Node<elemType> *t);
    void preOrder(Node<elemType> *t);
    void inOrder(Node<elemType> *t);
    void postOrder(Node<elemType> *t);

public:
    BTree() { root = nullptr; }
    void createTree(const elemType &flag);
    int isEmpty() { return root == nullptr; }
    Node<elemType> *getRoot() { return root; }

    int size();
    int height();
    void delTree();
    void preOrder();
    void inOrder();
    void postOrder();
    void levelOrder();
};

template <class elemType>
void BTree<elemType>::createTree(const elemType &flag)
{
    SeqQueue<Node<elemType> *> que;
    elemType e, el, er;
    Node<elemType> *p, *pl, *pr;

    std::cout << "Please input the root: ";
    std::cin >> e;

    if (e == flag)
    {
        root = nullptr;
        return;
    }

    p = new Node<elemType>(e);
    root = p;

    que.enQueue(p);
    while (!que.isEmpty())
    {
        p = que.front();
        que.deQueue();
        std::cout << "Please input the left child and the right child of " << p->data << " using " << flag << " as no child: ";
        std::cin >> el >> er;

        if (el != flag)
        {
            pl = new Node<elemType>(el);
            p->left = pl;
            que.enQueue(pl);
        }

        if (er != flag)
        {
            pr = new Node<elemType>(er);
            p->right = pr;
            que.enQueue(pr);
        }
    }
}

template <class elemType>
int BTree<elemType>::size()
{
    return size(root);
}

template <class elemType>
int BTree<elemType>::size(Node<elemType> *t)
{
    if (t == nullptr)
    {
        return 0;
    }

    return 1 + size(t->left) + size(t->right);
}

template <class elemType>
int BTree<elemType>::height()
{
    return height(root);
}

template <class elemType>
int BTree<elemType>::height(Node<elemType> *t)
{
    if (t == nullptr)
    {
        return 0;
    }

    int lt = height(t->left), rt = height(t->right);
    return 1 + (lt > rt ? lt : rt);
}

template <class elemType>
void BTree<elemType>::delTree()
{
    delTree(root);
    root = nullptr;
}

template <class elemType>
void BTree<elemType>::delTree(Node<elemType> *t)
{
    if (t == nullptr)
    {
        return;
    }

    delTree(t->left);
    delTree(t->right);
    delete t;
}
#endif /* BTREE_H_ */