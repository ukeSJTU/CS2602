// Below is only example code, if you want to run it, please go to main.cpp under
// src/examples/Chapter5/5-4/ and run it.

template <class verType, class edgeType>
void Graph<verType, edgeType>::DFS() const
{
    bool *visited;
    int i;

    // 为visited创建动态数组空间，并设置初始访问标志为false
    visited = new bool[verts];
    if (!visited) {
        throw illegalSize();
    }
    for (i = 0; i < verts; i++) visited[i] = false;

    for (i = 0; i < verts; i++) {
        if (!visited[i]) {
            DFS(i, visited);
        }
        cout << endl;
    }
}

template <class verType, class edgeType>
void Graph<verType, edgeType>::DFS(int start, bool visited[]) const
{
    edgeNode<edgeTpe> *p;

    cout << verList[start].data << "\t";
    visited[start] = true;

    p = verList[start].adj;
    while (p) {
        if (!visited[p->dest]) {
            DFS(p->dest, visited);
        }
        p = p->link;
    }
}