// Below is only example code, if you want to run it, please go to main.cpp under
// src/examples/Chapter5/5-5/ and run it.

template <class verType, class edgeType>
void Graph<verType, edgeType>::DFS() const
{
    seqStack<int> s;
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