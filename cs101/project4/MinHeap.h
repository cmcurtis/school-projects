#ifndef MINHEAP_H
#define MINHEAP_H

#include "Node.h"

class MinHeap {
    private:
        node** h_array;
        int capacity;
        int heap_size;
    public:
        MinHeap(int max, node **l_array);
        ~MinHeap();
        void insert(node *n);
        void MinHeapify(int loc);
        int getParent(int loc);
        int getLeft(int loc);
        int getRight(int loc);
        node* extractMin();
        node* getMin();
        int getSize();
        void printLine();
};

#endif
        