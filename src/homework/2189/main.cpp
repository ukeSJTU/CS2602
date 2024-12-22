#include <algorithm>
#include <iostream>

using namespace std;

int maxStones(int a, int b, int c)
{
    int total = a + b + c;
    int maxVal = max({a, b, c});

    // 最大得分计算
    int maxScore = min(total / 2, total - maxVal);

    // 每分兑换10原石
    return maxScore * 10;
}

int main()
{
    int a, b, c;
    cin >> a >> b >> c;

    cout << maxStones(a, b, c) << endl;
    return 0;
}