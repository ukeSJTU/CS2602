#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

// 自定义比较函数
unordered_map<char, int> letter_order;  // 字母表顺序映射表

// 比较两个单词
bool custom_compare(const string& word1, const string& word2)
{
    int len1 = word1.size();
    int len2 = word2.size();
    int min_len = min(len1, len2);

    for (int i = 0; i < min_len; ++i) {
        char c1 = word1[i];
        char c2 = word2[i];
        if (letter_order[c1] != letter_order[c2]) {
            return letter_order[c1] < letter_order[c2];
        }
    }

    // 如果前面都相同，比较长度
    return len1 < len2;
}

int main()
{
    int n, m;
    cin >> n >> m;

    // 读取自定义字母表
    for (int i = 0; i < n; ++i) {
        char c;
        cin >> c;
        letter_order[c] = i;  // 字母映射到索引
    }

    // 读取单词
    vector<string> words(m);
    for (int i = 0; i < m; ++i) {
        cin >> words[i];
    }

    // 按自定义比较函数排序
    sort(words.begin(), words.end(), custom_compare);

    // 输出排序后的单词
    for (const auto& word : words) {
        cout << word << endl;
    }

    return 0;
}