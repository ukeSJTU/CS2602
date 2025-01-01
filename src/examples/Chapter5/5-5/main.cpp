#include <iostream>

#include "SeqStack.h"

using namespace std;

#define DefaultNumVertex 20

class outOfBound
{
};

class illegalSize
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
    bool directed;
    int verts, edges;
    int maxVertex;
    verNode<verType, edgeType> *verList;

   public:
    Graph(bool direct);
    ~Graph();
    int numberOfVertex() const { return verts; }
    int numberOfEdge() const { return edges; }
    int getVertex(verType vertex) const;
    bool existEdge(verType vertex1, verType vertex2) const;
    void insertVertex(verType vertex);
    void insertEdge(verType vertex1, verType vertex2, edgeType edge);
    void removeVertex(verType vertex);
    void removeEdge(verType vertex1, verType vertex2);
    int getFirstNeighbor(verType vertex) const;
    int getNextNeighbor(verType vertex1, verType vertex2) const;
    void disp() const;
    void DFS() const;
};

template <class verType, class edgeType>
Graph<verType, edgeType>::Graph(bool direct)
{
    directed = direct;
    verts = 0;
    edges = 0;
    maxVertex = DefaultNumVertex;
    verList = new verNode<verType, edgeType>[maxVertex];
    for (int i = 0; i < maxVertex; i++) verList[i].adj = NULL;
}

template <class verType, class edgeType>
Graph<verType, edgeType>::~Graph()
{
    for (int i = 0; i < verts; i++) {
        edgeNode<edgeType> *p = verList[i].adj;
        while (p) {
            edgeNode<edgeType> *temp = p;
            p = p->link;
            delete temp;
        }
    }
    delete[] verList;
}

template <class verType, class edgeType>
int Graph<verType, edgeType>::getVertex(verType vertex) const
{
    for (int i = 0; i < verts; i++) {
        if (verList[i].data == vertex) return i;
    }
    return -1;
}

template <class verType, class edgeType>
bool Graph<verType, edgeType>::existEdge(verType vertex1, verType vertex2) const
{
    int i = getVertex(vertex1);
    int j = getVertex(vertex2);
    if ((i == -1) || (j == -1)) return false;

    edgeNode<edgeType> *p = verList[i].adj;
    while (p) {
        if (p->dest == j) return true;
        p = p->link;
    }
    return false;
}

template <class verType, class edgeType>
void Graph<verType, edgeType>::insertVertex(verType vertex)
{
    if (verts == maxVertex) throw outOfBound();
    verList[verts].data = vertex;
    verList[verts].adj = NULL;
    verts++;
}

template <class verType, class edgeType>
void Graph<verType, edgeType>::insertEdge(verType vertex1, verType vertex2, edgeType edge)
{
    int i = getVertex(vertex1);
    int j = getVertex(vertex2);
    if ((i == -1) || (j == -1)) return;

    edgeNode<edgeType> *tmp = new edgeNode<edgeType>;
    tmp->dest = j;
    tmp->weight = edge;
    tmp->link = verList[i].adj;
    verList[i].adj = tmp;
    edges++;

    if (!directed) {
        tmp = new edgeNode<edgeType>;
        tmp->dest = i;
        tmp->weight = edge;
        tmp->link = verList[j].adj;
        verList[j].adj = tmp;
    }
}

template <class verType, class edgeType>
void Graph<verType, edgeType>::DFS() const
{
    datastructures::SeqStack<int> s;
    edgeNode<edgeType> *p;
    bool *visited;
    int i, start;

    // 为visited创建动态数组空间，并设置初始访问标志为false
    visited = new bool[verts];
    if (!visited) {
        throw illegalSize();
    }
    for (i = 0; i < verts; i++) visited[i] = false;

    // 逐一找到未被访问过的顶点，做深度优先遍历
    for (i = 0; i < verts; i++) {
        if (visited[i]) continue;
        s.push(i);

        while (!s.isEmpty()) {
            start = s.top();
            s.pop();
            if (visited[start]) continue;

            cout << verList[start].data << "\t";
            visited[start] = true;

            p = verList[start].adj;
            while (p) {
                if (!visited[p->dest]) {
                    s.push(p->dest);
                }
                p = p->link;
            }
        }
        cout << endl;
    }
}

int main()
{
    Graph<char, int> g(false);

    // 添加顶点
    g.insertVertex('A');
    g.insertVertex('B');
    g.insertVertex('C');
    g.insertVertex('D');
    g.insertVertex('E');

    // 添加边
    g.insertEdge('A', 'B', 1);
    g.insertEdge('A', 'C', 1);
    g.insertEdge('B', 'D', 1);
    g.insertEdge('C', 'E', 1);
    g.insertEdge('D', 'E', 1);

    cout << "DFS traversal:" << endl;
    g.DFS();

    return 0;
}
