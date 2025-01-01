template <class verType, class edgeType>
void Graph<verType, edgeType>::topoSort() const
{
    int *inDegree;
    seqStack<int> s;
    int i, j;

    // 创建空间并初始化计算每个顶点的入度
    // 邻接矩阵每一列元素相加，加完入度为零的压栈
    inDegree = new int[verts];
    for (j = 0; j < verts; j++) {
        inDegree[j] = 0;
        for (i = 0; i < verts; i++) {
            if ((i != j) && (edgeMatrix[i][j] != noEdge)) {
                inDegree[j]++;
            }
        }
        if (inDegree[j] == 0) s.push(j);
    }

    // 逐一处理栈中元素
    while (!s.isEmpty()) {
        i = s.top();
        s.pop();
        cout << i << " ";

        // 将i射出的边指示的邻接点入度减1
        // 将i射出的边指示的邻接点入度减1，减为0时压栈
        for (j = 0; j < verts; j++)
            if ((j != i) && (edgeMatrix[i][j] != noEdge)) {
                inDegree[j]--;
                if (inDegree[j] == 0) s.push(j);
            }
    }
    cout << endl;
}