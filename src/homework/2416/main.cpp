#include <iostream>

#include "LinkList.h"

struct MemoryBlock {
    int start;
    int size;

    MemoryBlock(int start = 0, int size = 0) : start(start), size(size) {}

    void disp() { std::cout << "(" << start << "," << size << ")"; }

    int getStart() const { return start; }
    int getSize() const { return size; }
    void setStart(int newStart) { start = newStart; }
    void setSize(int newSize) { size = newSize; }
};

class FreeList : public datastructures::LinkList<MemoryBlock>
{
   public:
    bool allocate(int request_size);
    void release(int start, int size);
    void disp();
};

void FreeList::disp()
{
    // 遍历输出空闲链表信息，每个内存块表示为(start,size)，内存块之间用空格隔开。
    for (int i = 0; i < length(); i++) {
        this->get(i).disp();
        if (i != length() - 1) {
            std::cout << " ";
        }
    }
    std::cout << std::endl;
}

bool FreeList::allocate(int request_size)
{
    for (int i = 0; i < this->length(); i++) {
        MemoryBlock current_block = this->get(i);  // 拷贝出当前的块
        if (current_block.getSize() >= request_size) {
            // 分裂当前内存块
            int new_start = current_block.getStart() + request_size;
            int new_size = current_block.getSize() - request_size;
            // 更新链表，分裂后的内存块替代原块
            if (new_size > 0) {
                this->get(i).setStart(new_start);
                this->get(i).setSize(new_size);
            } else {
                // 如果刚好分配完，移除当前块
                MemoryBlock temp;
                this->remove(i, temp);
            }
            return true;
        }
    }
    return false;
}

void FreeList::release(int start, int size)
{
    MemoryBlock newBlock(start, size);

    // 插入释放的内存块到空闲链表
    int pos = 0;
    for (; pos < this->length(); pos++) {
        if (this->get(pos).getStart() > start) {
            break;
        }
    }
    this->insert(pos, newBlock);

    // 尝试合并相邻内存块
    for (int i = 0; i < this->length() - 1; i++) {
        MemoryBlock &current = this->get(i);
        MemoryBlock &next = this->get(i + 1);
        if (current.getStart() + current.getSize() == next.getStart()) {
            // 合并当前块和下一块
            current.setSize(current.getSize() + next.getSize());
            MemoryBlock temp;
            this->remove(i + 1, temp);
            i--;  // 合并后重新检查当前块与新的下一块
        }
    }
}

int main()
{
    int start[101], size[101];
    int n, m, op;
    std::cin >> n;

    FreeList free_list;

    for (int i = 0; i < n; i++) {
        std::cin >> start[i];
    }

    for (int i = 0; i < n; i++) {
        std::cin >> size[i];
    }

    for (int i = 0; i < n; i++) {
        MemoryBlock memory_block(start[i], size[i]);
        free_list.insert(free_list.length(), memory_block);
    }

    std::cin >> m;

    for (int j = 0; j < m; j++) {
        std::cin >> op;
        switch (op) {
            case 1: {
                int request_size;
                std::cin >> request_size;
                if (!free_list.allocate(request_size)) {
                    // 分配失败
                    // std::cout << "failed" << std::endl;
                }
                break;
            }
            case 2: {
                int start, size;
                std::cin >> start >> size;
                free_list.release(start, size);
                break;
            }
        }
    }

    free_list.disp();
    return 0;
}