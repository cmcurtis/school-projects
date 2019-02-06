#ifndef LIST_H
#define LIST_H

#include "Node.h"

class List {
    private:
        node **l_array;
        int size;
        int capacity;
    public:
        List();
        List(int s);
        ~List();
        node* get(unsigned char l);
        node* getHeadNode();
        node** getArray();
        void insert(unsigned char l);
        int getSize();
};

#endif
