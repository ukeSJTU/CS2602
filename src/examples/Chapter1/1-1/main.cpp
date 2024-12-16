#include <iostream>

using namespace std;

void setValue(int b[], int n);
void find(int b[], int n, int x);  // 查找x

int main()
{
    int data[10], a;
    setValue(data, 10);
    cout << "a=";
    cin >> a;
    find(data, 10, a);
    return 0;
}

void setValue(int b[], int n)
{
    for (int i = 0; i < n; i++) {
        b[i] = 2 * i + 1;
    }
}

void find(int b[], int n, int x)
{
    int i;
    for (i = 0; i < n; i++) {
        if (b[i] == x) {
            break;
        }
    }
    if (i == n) {
        cout << x << " doesn't exist in the array!";
    } else {
        cout << x << " exists in the array!";
    }
    cout << endl;
}
