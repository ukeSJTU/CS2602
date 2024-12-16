#include <iostream>

using namespace std;

template <class elemType>
class arr
{
   private:
    elemType* a;
    int maxSize, count;

   public:
    arr(int size);
    void append(const elemType& x);
    void find(const elemType& x) const;
    ~arr() { delete[] a; }
};

template <class elemType>
arr<elemType>::arr(int size)
{
    a = new elemType[size];
    maxSize = size;
    count = 0;
}

template <class elemType>
void arr<elemType>::append(const elemType& x)
{
    if (count == maxSize) return;
    a[count] = x;
    count++;
}

template <class elemType>
void arr<elemType>::find(const elemType& x) const
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
    arr<int> obj1(10);
    const arr<int> obj2(20);
    int a;
    const int b = 100;

    for (int i = 0; i < 10; i++) {
        obj1.append(2 * i + 1);
    }

    cout << "a=";
    cin >> a;
    cout << "In obj1: ";
    obj1.find(a);
    cout << "In obj1: ";
    obj1.find(b);
    cout << "In obj2: ";
    obj2.find(a);

    return 0;
}