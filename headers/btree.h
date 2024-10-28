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

    Node<elemType> *threadMid();
    void threadMidVisit(Node<elemType> *first);
    void threadMidePreVisit();

    Node<elemType> *BTree<elemType>::buildTree(elemType pre[], int pl, int pr, elemType mid[], int ml, int mr);
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

template <class elemType>
void BTree<elemType>::preOrder()
{
    preOrder(root);
}

template <class elemType>
void BTree<elemType>::preOrder(Node<elemType> *t)
{
    if (t == nullptr)
    {
        return;
    }
    std::cout << t->data;

    preOrder(t->left);
    preOrder(t->right);
}

/* non-recursion version of preOrder */
/*
template <class elemType>
void BTree<elemType>::preOrder()
{
    if (root == nullptr)
    {
        return;
    }

    Node<elemType> *p = root;
    SeqStack<Node<elemType> *> stack;

    while (!s.isEmpty())
    {
        p = s.top();
        s.pop()
                std::cout
            << p->data;
        if (p->right)
        {
            s.push(p->right)
        }

        if (p->left)
        {
            s.push(p->left)
        }
    }
    std::cout << std::endl;
}
*/

template <class elemType>
void BTree<elemType>::inOrder()
{
    inOrder(root);
}

template <class elemType>
void BTree<elemType>::inOrder(Node<elemType> *t)
{
    if (t == nullptr)
    {
        return;
    }

    inOrder(t->left);
    std::cout << t->data;
    inOrder(t->right);
}

/* non-recursion version of inOrder */
/*
template <class elemType>
void BTree<elemType>::inOrder()
{
    if (root == nullptr)
    {
        return;
    }

    Node<elemType> *p = root;
    SeqStack<Node<elemType> *> s1;
    SeqStack<int> s2;
    int flag, zero = 0, one = 1;

    s1.push(p);
    s2.push(zero);

    while (!s1.isEmpty())
    {
        p = s1.top();
        flag = s2.top();
        // s1.pop(); do not pop here, pop after the left child is visited
        s2.pop();

        if (flag == one)
        {
            s1.pop();
            std::cout << p->data;
            if (p->right == nullptr)
            {
                continue; // if the right child is null, skip the following steps
            }
            s1.push(p->right);
            s2.push(zero);
        }
        else
        {
            s2.push(one);
            if (p->left)
            {
                s1.push(p->left);
                s2.push(zero);
            }
        }
    }

    std::cout << std::endl;
}
*/

template <class elemType>
void BTree<elemType>::postOrder()
{
    postOrder(root);
}

template <class elemType>
void BTree<elemType>::postOrder(Node<elemType> *t)
{
    if (t == nullptr)
    {
        return;
    }

    postOrder(t->left);
    postOrder(t->right);
    std::cout << t->data;
}

/* non-recursion version of postOrder */
/*
template <class elemType>
void BTree<elemType>::postOrder()
{
    if (root == nullptr)
    {
        return;
    }

    Node<elemType> *p = root;
    SeqStack<Node<elemType> *> s1;
    SeqStack<int> s2;
    int flag, zero = 0, one = 1, two = 2;

    s1.push(p);
    s2.push(zero);

    while (!s1.isEmpty())
    {
        p = s1.top();
        flag = s2.top();
        s2.pop();

        if (flag == two)
        {
            s1.pop();
            std::cout << p->data;
        }
        else if (flag == one)
        {
            s2.push(two);
            if (p->right == nullptr)
            {
                s1.push(p->right);
                s2.push(zero);
            }
        }
        else
        {
            s2.push(one);
            if (p->left)
            {
                s1.push(p->left);
                s2.push(zero);
            }
        }
    }

    std::cout << std::endl;
}
*/

template <class elemType>
void BTree<elemType>::levelOrder()
{
    if (root == nullptr)
    {
        return;
    }

    Node<elemType> *p = root;
    SeqQueue<Node<elemType> *> que;

    que.enQueue(p);
    while (!que.isEmpty())
    {
        p = que.front();
        que.deQueue();
        std::cout << p->data;

        if (p->left)
        {
            que.enQueue(p->left);
        }

        if (p->right)
        {
            que.enQueue(p->right);
        }
    }

    std::cout << std::endl;
}

template <class elemType>
Node<elemType> *BTree<elemType>::threadMid()
{
    if (root == nullptr)
    {
        return nullptr;
    }

    SeqStack<Node<elemType> *> s1;
    SeqStack<int> s2;

    Node<elemType> *p = root, *pre = nullptr;
    Node<elemType> *first = nullptr;

    int flag, zero = 0, one = 1;
    s1.push(p);
    s2.push(zero);

    while (!s1.isEmpty())
    {
        p = s1.top();
        flag = s2.top();
        s2.pop();

        if (flag == one)
        {
            s1.pop();
            // std::cout << p->data;
            if (first == nullptr)
            {
                first = p;
            }

            if (p->right)
            {
                s1.push(p->right);
                s2.push(zero);
            }

            if (!p->left)
            {
                p->leftFlag = 1;
                p->left = pre;

                // std::cout << p->data << " pre: ";
                // if (p->left)
                // {
                //     std::cout << p->left->data << std::endl;
                // }
                // else
                // {
                //     std::cout << "NULL" << std::endl;
                // }
            }

            if (pre && (!pre->right))
            {
                pre->rightFlag = 1;
                pre->right = p;

                std::cout << pre->data << " next: " << p->data << std::endl;
            }

            pre = p;
        }
        else
        {
            s2.push(one);
            if (p->left)
            {
                s1.push(p->left);
                s2.push(zero);
            }
        }
    }

    p->rightFlag = 1;
    // std::cout << p->data << " next: " << "NULL" << std::endl;
}

template <class elemType>
void BTree<elemType>::threadMidVisit(Node<elemType> *first)
{
    if (!first)
    {
        return;
    }

    Node<elemType> *p = first;

    while (p)
    {
        std::cout << p->data;
        if (p->rightFlag == 0)
        {
            p = p->right;

            while (p->left)
            {
                p = p->left;
            }
        }
        else
        {
            p = p->right;
        }
    }

    std::cout << std::endl;
}

template <class elemType>
void BTree<elemType>::threadMidePreVisit()
{
    Node<elemType> *p = root;

    while (p->left)
    {
        p = p->left;
    }

    while (p)
    {
        std::cout << p->data;
        if (p->leftFlag == 0)
        {
            p = p->left;
        }
        else
        {
            if (p->rightFlag == 0)
            {
                p = p->right;
            }
            else
            {
                while (p && (p->rightFlag == 1))
                {
                    p = p->right;
                }

                if (!p)
                {
                    return;
                }
                p = p->right;
            }
        }
    }

    std::cout << std::endl;
}

template <class elemType>
Node<elemType> *BTree<elemType>::buildTree(elemType pre[], int pl, int pr, elemType mid[], int ml, int mr)
{
    Node<elemType> *p, *leftRoot, *rightRoot;
    int i, pos, num;
    int lpl, lpr, lml, lmr, rpl, rpr, rml, rmr; // [left/right-subtree] + [pre/mid] + [left/right-bound]

    if (pl > pr)
    {
        return nullptr;
    }
    p = new Node<elemType>(pre[pl]);
    if (!root)
    {
        root = p;
    }

    for (i = ml; i <= mr; i++)
    {
        if (mid[i] == pre[pl])
        {
            break;
        }
    }

    pos = i;
    num = pos - ml;

    lpl = pl + 1;
    lpr = pl + num;
    lml = ml;
    lmr = pos - 1;
    leftRoot = buildTree(pre, lpl, lpr, mid, lml, lmr);

    rpl = pl + num + 1;
    rpr = pr;
    rml = pos + 1;
    rmr = mr;
    rightRoot = buildTree(pre, rpl, rpr, mid, rml, rmr);

    p->left = leftRoot;
    p->right = rightRoot;
    return p;
}

#endif /* BTREE_H_ */