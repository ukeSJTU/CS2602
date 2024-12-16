#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "Exceptions.h"

/**
 * @brief 数据结构命名空间
 */
namespace datastructures
{

/**
 * @brief 节点结构体
 *
 * @tparam elemType 元素类型
 */
template <class elemType>
struct Node {
    elemType data;  ///< 数据
    int state;      ///< 状态：0:空 1:占用 2:删除

    /**
     * @brief 构造函数，初始化状态为0
     */
    Node() : state(0) {}
};

/**
 * @brief 哈希表类
 *
 * @tparam elemType 元素类型
 */
template <class elemType>
class HashTable
{
   private:
    Node<elemType>* table;               ///< 哈希表数组
    int tableSize;                       ///< 哈希表大小
    int (*hashFunc)(const elemType& x);  ///< 哈希函数指针

   public:
    /**
     * @brief 构造函数
     *
     * @param size 哈希表大小
     * @param func 哈希函数
     */
    HashTable(int size, int (*func)(const elemType& x));

    /**
     * @brief 析构函数
     */
    ~HashTable() { delete[] table; }

    /**
     * @brief 查找元素
     *
     * @param x 要查找的元素
     * @return true 如果找到元素
     * @return false 如果未找到元素
     */
    bool find(const elemType& x) const;

    /**
     * @brief 插入元素
     *
     * @param x 要插入的元素
     * @return true 如果插入成功
     * @return false 如果插入失败
     */
    bool insert(const elemType& x);

    /**
     * @brief 删除元素
     *
     * @param x 要删除的元素
     * @return true 如果删除成功
     * @return false 如果删除失败
     */
    bool remove(const elemType& x);
};

template <class elemType>
HashTable<elemType>::HashTable(int size, int (*func)(const elemType& x))
{
    tableSize = size;
    table = new Node<elemType>[tableSize];
    if (!table) throw IllegalSize();
    hashFunc = func;
}

template <class elemType>
bool HashTable<elemType>::insert(const elemType& x)
{
    int initialPos = hashFunc(x) % tableSize;
    int pos = initialPos;

    do {
        if (table[pos].state != 1) {  // state==0 or state==2
            table[pos].data = x;
            table[pos].state = 1;
            return true;
        }
        if (table[pos].state == 1) {
            if (table[pos].data == x)
                return false;
            else
                pos = (pos + 1) % tableSize;
        }
    } while (pos != initialPos);
    return false;
}

template <class elemType>
bool HashTable<elemType>::remove(const elemType& x)
{
    int initialPos = hashFunc(x) % tableSize;
    int pos = initialPos;

    do {
        if (table[pos].state == 0) return false;
        if (table[pos].state == 1 && table[pos].data == x) {
            table[pos].state = 2;
            return true;
        }
        pos = (pos + 1) % tableSize;
    } while (pos != initialPos);
    return false;
}

template <class elemType>
bool HashTable<elemType>::find(const elemType& x) const
{
    int initialPos = hashFunc(x) % tableSize;
    int pos = initialPos;

    do {
        if (table[pos].state == 0) return false;
        if (table[pos].state == 1 && table[pos].data == x) return true;
        pos = (pos + 1) % tableSize;
    } while (pos != initialPos);
    return false;
}

}  // namespace datastructures

#endif  // HASHTABLE_H