#include <iostream>

class illegalSize
{
};
template <class elemType>
class staticSearch
{
   private:
    elemType *data;  // 存储静态数据
    int len;

   public:
    staticSearch(elemType a[], int n);
    int Search(const elemType &x) const;   // 顺序查找
    int BSearch(const elemType &x) const;  // 折半查找
    ~staticSearch() { delete[] data; }
};

template <class elemType>
staticSearch<elemType>::staticSearch(elemType a[], int n)
{
    len = n;
    data = new elemType[n + 1];  // 多一个哨兵位
    if (!data) throw illegalSize();
    for (int i = 1; i < n + 1; i++) data[i] = a[i - 1];  // 0下标不用
}

template <class elemType>
int staticSearch<elemType>::Search(const elemType &x) const  // 顺序查找
{
    int i;
    data[0] = x;
    for (i = len; data[i] != x; i--);
    return i;
}

template <class elemType>
int staticSearch<elemType>::BSearch(const elemType &x) const  // 折半查找
{
    int mid, low, high;
    low = 1;
    high = len;
    while (low <= high) {
        mid = (low + high) / 2;
        if (x == data[mid])
            break;  // 查找成功
        else if (x < data[mid])
            high = mid - 1;  // x小于中间位置元素
        else
            low = mid + 1;  // x大于中间位置元素
    }
    if (low <= high) return mid;
    return 0;
}

int main()
{
    std::cout << "TODO: needs to be completed." << std::endl;

    return 0;
}