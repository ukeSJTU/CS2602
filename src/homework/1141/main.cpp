#include <string.h>

#include <iostream>

#include "HashTable.h"

using namespace datastructures;
using namespace std;

int hashFunc(const string &s)
{
    int index = 0, i = 0;
    while (s[i++] != '\0') {
        if (s[i] >= 'a' && s[i] <= 'z') {
            index += (s[i] - 'a');
        } else if (s[i] >= 'A' && s[i] <= 'Z') {
            index += (s[i] - 'A');

        } else {
            index += (s[i] - '0');
        }
    }
    index = index % 10001;
    return index;
}

int main()
{
    int n;
    cin >> n;
    HashTable<string> hash_table(10001, hashFunc);
    string t;
    int cnt = 0;

    for (int i = 0; i < n; i++) {
        cin >> t;
        if (hash_table.insert(t)) {
            cnt++;
        }
    }

    cout << cnt << endl;
    return 0;
}