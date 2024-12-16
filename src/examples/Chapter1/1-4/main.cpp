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
    elemType fetch(int i) const;
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
elemType arr<elemType>::fetch(int i) const
{
    if ((i < 0) || (i >= count)) {
        cout << "index is out of the bound!" << endl;
        exit(1);
    } else
        return a[i];
}

int main()
{
    arr<int> obj1(10);
    const arr<int> obj2(20);
    int i;

    for (i = 0; i < 10; i++) {
        obj1.append(2 * i + 1);
    }
    while (cin >> i) {
        cout << i << ": " << obj1.fetch(i) << endl;
    }

    cout << "Return to main, it is Over!" << endl;
    return 0;
}