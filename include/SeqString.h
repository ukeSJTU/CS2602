#ifndef SEQSTRING_H
#define SEQSTRING_H

#include <iostream>

#include "Exceptions.h"

namespace datastructures
{

// 匹配算法的枚举类型
enum class MatchAlgorithm { BF, KMP };

class String
{
   private:
    char *str;    // 动态数组，存储字符串
    int maxSize;  // 数组的尺寸

    int BF_find(const String &t, int start) const;
    int KMP_find(const String &t, int start) const;

   public:
    /**
     * @brief  显示字符串，结尾无换行
     */
    void disp() const { std::cout << str; };

    /**
     * @brief 构造函数，创建动态空间
     * @param size 动态数组的大小
     * @throws IllegalSize 如果 size 小于等于 0
     * @throws NoSpace 如果动态内存分配失败
     */
    inline String(int size);

    /**
     * @brief 构造函数，用 C 风格字符串初始化
     * @param t C 风格字符串
     * @throws NoSpace 如果动态内存分配失败
     */
    inline String(const char *t);

    /**
     * @brief 拷贝构造函数
     * @param t 要拷贝的 String 对象
     */
    inline String(const String &t);

    /**
     * @brief 获取字符串的实际长度
     * @return 字符串的长度（不包括末尾的 '\0'）
     */
    inline int length() const;

    /**
     * @brief 判断两个字符串是否相等
     * @param t 另一个字符串
     * @return 如果相等返回 true，否则返回 false
     */
    inline bool equal(const String &t) const;

    /**
     * @brief 赋值操作，将 t 的值赋给当前对象
     * @param t 赋值来源的 String 对象
     * @throws NoSpace 如果动态内存分配失败
     */
    inline void assign(const String &t);

    /**
     * @brief 求子串
     * @param pos 起始位置（从 0 开始）
     * @param len 子串的长度
     * @return 一个新的 String 对象，表示子串
     * @throws OutOfBound 如果 pos 小于 0
     */
    inline String &subString(int pos, int len) const;

    /**
     * @brief 在指定位置插入一个字符串
     * @param pos 插入位置（从 0 开始）
     * @param t 要插入的字符串
     * @return 如果插入成功返回 true，否则返回 false
     */
    inline bool insert(int pos, const String &t);

    /**
     * @brief 删除指定位置后的 n 个字符
     * @param pos 起始位置（从 0 开始）
     * @param n 要删除的字符个数
     * @return 如果删除成功返回 true，否则返回 false
     */
    inline bool remove(int pos, int n);

    // int BF_find(const String &t, int start) const;
    // int KMP_find(const String &t, int start) const;
    // 书本上是这么写的，但是这个编码相对来说有些繁琐.我们对调用者隐藏实现细节（到底是BF还是KMP）,
    // 在private中实现。
    // 从串的第start个字符起，向后查找字符串t第一次在串中出现的位置，找到返回位置序号，未找到返回-1
    int find(const String &t, int start, MatchAlgorithm algorithm = MatchAlgorithm::KMP) const;

    ~String() { delete[] str; }  // 析构函数，释放动态空间
};

// 构造函数实现
inline String::String(int size)
{
    if (size <= 0) {
        throw IllegalSize();
    }
    str = new char[size];
    if (!str) {
        throw NoSpace();
    }
    maxSize = size;
    str[0] = '\0';  // 初始化为空字符串
}

// 用 C 风格字符串初始化
inline String::String(const char *t)
{
    int len = 0;
    while (t[len] != '\0') {
        len++;  // 计算字符串长度
    }

    maxSize = len + 1;  // 加上 '\0' 的空间
    str = new char[len + 1];

    int i = 0;
    while (t[i] != '\0') {
        str[i] = t[i];  // 拷贝字符
        i++;
    }

    str[i] = '\0';  // 添加结束符
}

// 拷贝构造函数实现
inline String::String(const String &t)
{
    maxSize = t.maxSize;
    str = new char[maxSize];
    for (int i = 0; i < maxSize; i++) {
        str[i] = t.str[i];  // 拷贝每个字符
    }
}

// 获取字符串长度
inline int String::length() const
{
    int i = 0;
    while (str[i] != '\0') {
        i++;  // 遍历直到结束符
    }
    return i;
}

// 判断字符串是否相等
inline bool String::equal(const String &t) const
{
    if (this->length() != t.length()) {
        return false;  // 长度不同直接返回 false
    }

    int i = 0;
    while (str[i] != '\0') {
        if (str[i] != t.str[i]) {
            return false;  // 发现字符不同
        }
        i++;
    }

    return true;  // 字符串完全相同
}

// 赋值操作
inline void String::assign(const String &t)
{
    int len = t.length();
    if (maxSize <= len) {  // 检查空间是否足够
        delete[] str;
        maxSize = len + 1;
        str = new char[maxSize];
        if (!str) {
            throw NoSpace();
        }
    }

    for (int i = 0; i <= len; i++) {
        str[i] = t.str[i];  // 拷贝字符串
    }
}

// 子串操作
inline String &String::subString(int pos, int len) const
{
    if (pos < 0) {
        throw OutOfBound();  // 起始位置无效
    }

    String *tmp = new String(len + 1);
    int i;
    for (i = 0; i < len; i++) {
        if (str[pos + i] == '\0') {
            break;  // 到达原字符串结束
        }
        tmp->str[i] = str[pos + i];
    }

    tmp->str[i] = '\0';  // 添加结束符
    return *tmp;
}

// 插入操作
inline bool String::insert(int pos, const String &t)
{
    int len1 = this->length(), len2 = t.length();
    if ((pos < 0) || (pos > len1)) {
        return false;  // 插入位置无效
    }
    if (len1 + len2 > maxSize - 1) {
        return false;  // 空间不足
    }

    // 将原字符串从 pos 开始后移 len2 位
    for (int i = len1; i >= pos; i--) {
        str[i + len2] = str[i];
    }

    // 插入新字符串
    for (int i = 0; i < len2; i++) {
        str[pos + i] = t.str[i];
    }

    return true;
}

// 删除操作
inline bool String::remove(int pos, int n)
{
    int len = length();
    if (pos < 0) {
        return false;  // 起始位置无效
    }

    // 将后面的字符左移覆盖
    for (int i = pos; i + n < len; i++) {
        str[i] = str[i + n];
    }

    str[len - n] = '\0';  // 更新结束符
    return true;
}

}  // namespace datastructures

#endif  // SEQSTRING_H