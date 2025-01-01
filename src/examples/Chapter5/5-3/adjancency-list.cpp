#ifndef GRAPH2_H_INCLUDED
#define GRAPH2_H_INCLUDED

#include <iostream>
using namespace std;

#define DefaultNumVertex 20
class outOfBound
{
};

template <class edgeType>
struct edgeNode {
    int dest;
    edgeType weight;
    edgeNode *link;
};

template <class verType, class edgeType>
struct verNode {
    verType data;
    edgeNode<edgeType> *adj;
};

template <class verType, class edgeType>
class Graph
{
   private:
    bool directed;                        // 有向图为1，无向图为0
    int verts, edges;                     // 图的实际顶点数和实际边数
    int maxVertex;                        // 图顶点的最大可能数量
    verNode<verType, edgeType> *verList;  // 保存顶点数据的一维数组
   public:
    // 初始化图结构g，direct为是否有向图标志，e为无边数据
    Graph(bool direct);
    ~Graph();

    int numberOfVertex() const { return verts; };  // 返回图当前顶点数
    int numberOfEdge() const { return edges; };    // 返回图当前边数

    int getVertex(verType vertex) const;  // 返回值为vertex的元素在顶点表中的下标,无则-1.
    bool existEdge(verType vertex1, verType vertex2) const;  // 判断某两个顶点间是否有边

    void insertVertex(verType vertex);                                 // 插入顶点
    void insertEdge(verType vertex1, verType vertex2, edgeType edge);  // 插入边

    int getFirstNeighbor(verType vertex) const;
    // 返回顶点vertex1的相对vertex2的下一个邻接点，如无下一个邻接点返回-1
    int getNextNeighbor(verType vertex1, verType vertex2) const;

    void removeVertex(verType vertex);                  // 删除顶点
    void removeEdge(verType vertex1, verType vertex2);  // 删除边

    void disp() const;  // 显示邻接矩阵的值
};

// 初始化图结构g，direct为是否有向图标志
template <class verType, class edgeType>
Graph<verType, edgeType>::Graph(bool direct)
{
    int i;
    // 初始化属性
    directed = direct;
    verts = 0;
    edges = 0;
    maxVertex = DefaultNumVertex;

    // 为存顶点的一维数组创建空间
    verList = new verNode<verType, edgeType>[maxVertex];
    for (i = 0; i < maxVertex; i++) verList[i].adj = NULL;
}

template <class verType, class edgeType>
Graph<verType, edgeType>::~Graph()
{
    int i;
    edgeNode<edgeType> *p;

    for (i = 0; i < verts; i++)  // 释放所有边表中的结点
    {
        while (verList[i].adj) {
            p = verList[i].adj;
            verList[i].adj = p->link;
            delete p;
        }
    }
    delete[] verList;
}

// 返回顶点为vertex值的元素在顶点表中的下标
template <class verType, class edgeType>
int Graph<verType, edgeType>::getVertex(verType vertex) const
{
    int i;
    for (i = 0; i < verts; i++) {
        if (verList[i].data == vertex) return i;
    }

    return -1;
}

// 判断某两个顶点间是否有边
template <class verType, class edgeType>
bool Graph<verType, edgeType>::existEdge(verType vertex1, verType vertex2) const
{
    int i, j;
    edgeNode<edgeType> *p;

    // 找到vertex1和vertex2的下标
    i = getVertex(vertex1);
    j = getVertex(vertex2);

    // 无此顶点
    if ((i == -1) || (j == -1)) return false;

    p = verList[i].adj;
    while (p) {
        if (p->dest == j) {
            return true;
        }
        p = p->link;
    }
    return false;
}

// 插入顶点
template <class verType, class edgeType>
void Graph<verType, edgeType>::insertVertex(verType vertex)
{
    if (verts == maxVertex) throw outOfBound();
    verts++;
    verList[verts - 1].data = vertex;
    verList[verts + 1].adj = NULL;
}

// 插入边
template <class verType, class edgeType>
void Graph<verType, edgeType>::insertEdge(verType vertex1, verType vertex2, edgeType edge)
{
    int i, j;
    edgeNode<edgeType> *tmp;

    // 找到vertex1和vertex2的下标
    i = getVertex(vertex1);
    j = getVertex(vertex2);

    // 无此顶点
    if ((i == -1) || (j == -1)) return;
    // if (i == j) return;

    // 在i下标引导的单链表中插入一个边结点
    tmp = new edgeNode<edgeType>;
    tmp->dest = j;
    tmp->weight = edge;
    tmp->link = verList[i].adj;
    verList[i].adj = tmp;
    edges++;

    if (!directed)  // 如果是无向图，矩阵中关于主对角线的对称点也要设置
    {
        tmp = new edgeNode<edgeType>;
        tmp->dest = i;
        tmp->weight = edge;
        tmp->link = verList[j].adj;
        verList[j].adj = tmp;
    }
}

template <class verType, class edgeType>
void Graph<verType, edgeType>::removeEdge(verType vertex1, verType vertex2)
{
    int i, j;
    edgeNode<edgeType> *p, *q;

    // 找到vertex1和vertex2的下标
    i = getVertex(vertex1);
    j = getVertex(vertex2);

    // 无此顶点
    if ((i == -1) || (j == -1)) return;

    // 在i下标引导的单链表中删除一个边结点
    p = verList[i].adj;
    q = NULL;
    while (p) {
        if (p->dest == j) break;
        q = p;
        p = p->link;
    }
    if (!p) return;
    if (!q)  // 删除首结点
        verList[i].adj = p->link;
    else
        q->link = p->link;
    delete p;
    edges--;

    if (directed) return;

    // 如果是无向图，还需要删除下标j引导的单链表中的一个dest=i的结点
    p = verList[j].adj;
    q = NULL;
    while (p) {
        if (p->dest == i) break;
        q = p;
        p = p->link;
    }
    if (!p) return;
    if (!q)  // 删除首结点
        verList[j].adj = p->link;
    else
        q->link = p->link;
    delete p;
}

// 删除顶点
template <class verType, class edgeType>
void Graph<verType, edgeType>::removeVertex(verType vertex)
{
    int i, j;
    int count = 0;
    edgeNode<edgeType> *p, *q;
    // 找到该顶点在顶点表中的下标
    i = getVertex(vertex);

    if (i == -1) return;  // 该顶点不在顶点表中

    // 删除下标为i的顶点引导的单链表中所有结点并计数删除的边
    p = verList[i].adj;
    while (p) {
        count++;
        verList[i].adj = p->link;
        delete p;
        p = verList[i].adj;
    }
    cout << "count= " << count << endl;

    // 检查所有单链表，凡是dest为verts-1的都改为i
    for (j = 0; j < verts; j++) {
        p = verList[j].adj;
        q = NULL;
        while (p) {
            if (p->dest == i) break;
            q = p;
            p = p->link;
        }
        if (!p) continue;
        if (!q)
            verList[j].adj = p->link;
        else
            q->link = p->link;
        delete p;
        count++;
    }

    // 检查所有单链表，凡是dest>i的都删减1
    for (j = 0; j < verts; j++) {
        p = verList[i].adj;
        while (p) {
            if (p->dest > i) p->dest--;
            p = p->link;
        }
    }

    if (directed)
        edges -= count;
    else
        edges -= count / 2;  // 无向图，减少count的一半

    // 将最后一个顶点移入第i个位置，也即删除顶点
    verList[i] = verList[verts - 1];
    verts--;
}

// 返回顶点vertex的第一个邻接点，如果无邻接点返回-1
template <class verType, class edgeType>
int Graph<verType, edgeType>::getFirstNeighbor(verType vertex) const
{
    int i, j;
    edgeNode<edgeType> *p;

    i = getVertex(vertex);
    if (i == -1) return -1;

    *p = verList[i].adj;
    if (!p) return -1;
    return p->dest;
}

// 返回顶点vertex1相对于vertex2的下一个邻接点，如果无下一个邻接点返回-1
template <class verType, class edgeType>
int Graph<verType, edgeType>::getNextNeighbor(verType vertex1, verType vertex2) const
{
    int i, j, k;
    edgeNode<edgeType> *p;

    i = getVertex(vertex1);
    j = getVertex(vertex2);
    if ((i == -1) || (j == -1)) return -1;

    p = verList[i].adj;
    while (p) {
        if (p->dest == j) break;
        p = p->link;
    }
    if (!p || !p->link) return -1;
    return p->link->dest;
}

// 显示邻接表的值
template <class verType, class edgeType>
void Graph<verType, edgeType>::disp() const
{
    int i;
    edgeNode<edgeType> *p;

    for (i = 0; i < verts; i++) {
        cout << verList[i].data << ": ";
        p = verList[i].adj;
        while (p) {
            cout << verList[p->dest].data << "(" << p->weight << ") ";
            p = p->link;
        }
        cout << endl;
    }
}

#endif
