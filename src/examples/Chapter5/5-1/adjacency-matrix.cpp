#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <iostream>

using namespace std;

#define DefaultNumVertex 20

class outOfBound
{
};

template <class verType, class edgeType>
class Graph
{
   private:                 // 7个属性
    int verts, edges;       // 图的实际顶点数和实际边数
    int maxVertex;          // 图顶点的最大可能数量
    verType *verList;       // 保存顶点数据的一维数组
    edgeType **edgeMatrix;  // 保存邻接矩阵内容的二维数组
    edgeType noEdge;        // 无边的标志，一般图为0， 网为无穷大MAXNUM
    bool directed;          // 有向图为1，无向图为0

   public:
    // 初始化图结构g，direct为是否有向图标志，e为无边数据
    Graph(bool direct, edgeType e);
    ~Graph();
    int numberOfVertex() const { return verts; };  // 返回图当前顶点数
    int numberOfEdge() const { return edges; };    // 返回图当前边数
    // 返回顶点为vertex值的元素在顶点表中的下标，无则-1。
    int getVertex(verType vertex) const;
    ;
    // 判断某两个顶点间是否有边
    bool existEdge(verType vertex1, verType vertex2) const;
    void insertVertex(verType vertex);                                 // 插入顶点
    void insertEdge(verType vertex1, verType vertex2, edgeType edge);  // 插入边
    void removeVertex(verType vertex);                                 // 删除顶点
    void removeEdge(verType vertex1, verType vertex2);                 // 删除边

    // 返回顶点vertex的第一个邻接点,如果无邻接点返回-1
    int getFirstNeighbor(verType vertex) const;
    // 返回顶点vertex1相对vertex2的下一个邻接点，如果无下一个邻接点返回-1
    int getNextNeighbor(verType vertex1, verType vertex2) const;
    void disp() const;  // 显示邻接矩阵的值
};

// 初始化图结构g，direct为是否有向图标志，e为无边数据
template <class verType, class edgeType>
Graph<verType, edgeType>::Graph(bool direct, edgeType e)
{
    int i, j;

    // 初始化属性
    directed = direct;
    noEdge = e;
    verts = 0;
    edges = 0;
    maxVertex = DefaultNumVertex;

    // 为存储顶点的一维数组和存储边的二维数组创建空间
    verList = new verType[maxVertex];
    edgeMatrix = new edgeType *[maxVertex];
    for (i = 0; i < maxVertex; i++) edgeMatrix[i] = new edgeType[maxVertex];

    // 初始化二维数组，边的条数为0
    for (i = 0; i < verts; i++) {
        for (j = 0; j < verts; j++) {
            if (i == j)
                edgeMatrix[i][j] = 0;  // 对角线元素
            else
                edgeMatrix[i][j] = noEdge;  // 无边
        }
    }
}

template <class verType, class edgeType>
Graph<verType, edgeType>::~Graph()
{
    int i;
    delete[] verList;

    for (i = 0; i < maxVertex; i++) {
        delete[] edgeMatrix[i];
    }
    delete[] edgeMatrix;
}

// 返回顶点为vertex值的元素在顶点表中的下标
template <class verType, class edgeType>
int Graph<verType, edgeType>::getVertex(verType vertex) const
{
    int i;
    for (i = 0; i < verts; i++)
        if (verList[i] == vertex) return i;

    return -1;
}

// 判断某两个顶点之间是否有边
template <class verType, class edgeType>
bool Graph<verType, edgeType>::existEdge(verType vertex1, verType vertex2) const
{
    int i, j;

    // 找到vertex1和vertex2的下标
    i = getVertex(vertex1);
    j = getVertex(vertex2);

    // 无此顶点
    if ((i == -1) || (j == -1)) return false;
    if (i == j) return false;

    if (edgeMatrix[i][j] == noEdge) return false;

    return true;
}

// 插入顶点
template <class verType, class edgeType>
void Graph<verType, edgeType>::insertVertex(verType vertex)
{
    int i;

    if (verts == maxVertex) outOfBound();
    verts++;
    verList[verts - 1] = vertex;

    // 清空矩阵新加入的最后一行和最后一列
    for (i = 0; i < verts; i++) edgeMatrix[verts - 1][i] = noEdge;
    for (i = 0; i < verts; i++) edgeMatrix[i][verts - 1] = noEdge;

    edgeMatrix[verts - 1][verts - 1] = 0;  // 对角线
}

// 插入边
template <class verType, class edgeType>
void Graph<verType, edgeType>::insertEdge(verType vertex1, verType vertex2, edgeType edge)
{
    int i, j;

    // 找到vertex1和vertex2的下标
    i = getVertex(vertex1);
    j = getVertex(vertex2);

    // 无此顶点
    if ((i == -1) || (j == -1)) return;
    if (i == j) return;

    edgeMatrix[i][j] = edge;
    edges++;

    // 如果是无向图，矩阵中关于主对角线的对称点也要设置
    if (!directed) edgeMatrix[j][i] = edge;
}

// 删除顶点
template <class verType, class edgeType>
void Graph<verType, edgeType>::removeVertex(verType vertex)
{
    int i, j, k;
    i = getVertex(vertex);
    if (i == -1) return;

    // 在顶点表中将最后一个顶点移入表中下标i处
    verList[i] = verList[verts - 1];

    // 计数删除顶点射出的边，边数减少
    for (j = 0; j < verts; j++) {
        if ((i != j) && (edgeMatrix[i][j] != noEdge)) {
            edges--;
        }
    }

    // 如果是有向图，计数删除顶点射入的边，边数减少
    if (directed) {
        for (k = 0; k < verts; k++) {
            if ((i != k) && (edgeMatrix[k][i] != noEdge)) {
                edges--;
            }
        }
    }

    // 将矩阵最后一行移入第i行
    for (j = 0; j < verts; j++) edgeMatrix[i][j] = edgeMatrix[verts - 1][j];

    // 将矩阵最后一列移入第i列
    for (j = 0; j < verts; j++) edgeMatrix[j][i] = edgeMatrix[j][verts - 1];

    verts--;
}

// 删除边
template <class verType, class edgeType>
void Graph<verType, edgeType>::removeEdge(verType vertex1, verType vertex2)
{
    int i, j;

    // 找到vertex1和vertex2的下标
    i = getVertex(vertex1);
    j = getVertex(vertex2);

    // 无此顶点
    if ((i == -1) || (j == -1)) return;
    if (i == j) return;

    edgeMatrix[i][j] = noEdge;
    edges--;

    if (!directed) edgeMatrix[j][i] = noEdge;
}

// 返回顶点vertex的第一个邻接点，如果无邻接点返回-1
template <class verType, class edgeType>
int Graph<verType, edgeType>::getFirstNeighbor(verType vertex) const
{
    int i, j;

    i = getVertex(vertex);
    if (i == -1) return -1;

    for (j = 0; j < verts; i++)
        if ((i != j) && (edgeMatrix[i][j] != noEdge)) return j;

    return -1;
}

// 返回顶点vertex1像对于vertex2的下一个邻接点，如果无下一个邻接点返回-1
template <class verType, class edgeType>
int Graph<verType, edgeType>::getNextNeighbor(verType vertex1, verType vertex2) const
{
    int i, j, k;

    // 找到vertex1和vertex2的下标
    i = getVertex(vertex1);
    j = getVertex(vertex2);

    // 无此顶点
    if ((i == -1) || (j == -1)) return -1;
    if (i == j) return -1;

    for (k = j + 1; k < verts; k++) {
        if ((i != k) && (edgeMatrix[i][k] != noEdge)) return k;
    }

    return -1;
}

template <class verType, class edgeType>
void Graph<verType, edgeType>::disp() const
{
    int i, j;
    for (i = 0; i < verts; i++) {
        for (j = 0; j < verts; j++) {
            cout << edgeMatrix[i][j] << " ";
        }
        cout << endl;
    }
}

#endif  // GRAPH_H_INCLUDED
