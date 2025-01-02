template <class elemType>
void bubbleSort1(elemType a[], int n)
{
    if (n == 0 || n == 1) return;
    int i, j;
    elemType tmp;
    for (i = 0; i < n - 1; i++)
        if (a[i] > a[i + 1]) {
            tmp = a[i];
            a[i] = a[i + 1];
            a[i + 1] = tmp;
        }  // if
    bubbleSort1(a, n - 1);
}
