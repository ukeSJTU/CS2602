#include <iostream>

using namespace std;

class arr
{
   private:
    int* a;
    int maxSize, count;

   public:
    arr(int size);
    void append(int x);
    void find(int x);
    ~arr() { delete[] a; }
};

arr::arr(int size)
{
    a = new int[size];
    maxSize = size;
    count = 0;
}

void arr::append(int x)
{
    if (count == maxSize) return;
    a[count] = x;
    count++;
}

void arr::find(int x)
{
    int i;
    for (i = 0; i < count; i++) {
        if (a[i] == x) break;
    }
    if (i == count) {
        cout << x << " doesn't exist in the array!";
    } else {
        cout << x << " exists in the array!";
    }
    cout << endl;
}

int main()
{
    arr obj(10);
    int a;
    for (int i = 0; i < 10; i++) {
        // 将几个奇数放入对象
        obj.append(2 * i + 1);
    }
    cout << "a=";
    cin >> a;
    obj.find(a);
    return 0;
}