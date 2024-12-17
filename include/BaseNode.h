#ifndef BASE_NODE_H
#define BASE_NODE_H

namespace datastructures
{

/**
 * @brief 抽象基类：树节点
 * @tparam elemType 节点数据类型
 */
template <class elemType>
class BaseNode
{
   public:
    elemType data;              ///< 节点数据
    BaseNode<elemType>* left;   ///< 左子节点
    BaseNode<elemType>* right;  ///< 右子节点

    BaseNode(const elemType& d) : data(d), left(nullptr), right(nullptr) {}

    virtual ~BaseNode() = default;
};

}  // namespace datastructures

#endif  // BASE_NODE_H
