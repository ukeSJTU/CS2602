#include <iostream>

#include "../5-1/adjacency-matrix.cpp"

using namespace std;

int main()
{
    int i, vCount, eCount;
    char v1, v2;
    int value;

    Graph<char, int> g(true, 0);

    cout << "Input the number of verts and edges: ";
    cin >> vCount >> eCount;
    cin.get();

    // 插入所有顶点
    for (i = 0; i < vCount; i++) g.insertVertex('A' + i);

    cout << "Input the edge, for example: AB 5" << endl;
    for (i = 0; i < eCount; i++) {
        v1 = cin.get();
        v2 = cin.get();
        cin >> value;
        cin.get();  // 读入回车

        g.insertEdge(v1, v2, value);  // 插入边
    }

    g.disp();

    cout << "The numbers of verts and edges are: ";
    cout << g.numberOfVertex() << ", " << g.numberOfEdge() << endl;

    cout << "The index of C is: " << g.getVertex('C') << endl;
    if (g.existEdge('A', 'C'))
        cout << "From A to C: no edge!" << endl;
    else
        cout << "From A to C: has an edge!" << endl;

    return 0;
}