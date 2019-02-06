#include <string>
#include <iostream>
#include "MinHeap.h"

using namespace std;

void swap(node **x, node **y) {
  node *temp = new node;
  temp = *x;
  *x = *y;
  *y = temp;
}

MinHeap::MinHeap(int max, node **l_array){
    h_array = new node *[max];
    capacity = max;
    heap_size = 0;
    for (int i = 0; i < max; i++){
        insert(l_array[i]);
    }
}

MinHeap::~MinHeap(){
    delete[]h_array;
}

void MinHeap::insert(node *n){
    if (heap_size == capacity){
        return;
    }

    int i = heap_size;
    heap_size++;
    h_array[i] = new node;
    h_array[i] = n;
    
    while (i != 0 && h_array[getParent(i)]->frequency > h_array[i]->frequency){
       swap(h_array[i], h_array[getParent(i)]);
       i = getParent(i);
    }
}

void MinHeap::MinHeapify(int loc){
    int left = getLeft(loc);
    int right = getRight(loc);

    int smallest = loc;

    if (left < heap_size && h_array[left]->frequency < h_array[loc]->frequency) smallest = left;
    if (right < heap_size && h_array[right]->frequency < h_array[smallest]->frequency) smallest = right;
    if (smallest != loc) {
        swap(h_array[loc], h_array[smallest]);
        MinHeapify(smallest);
    }
}

int MinHeap::getParent(int loc){
    return ((loc - 1) / 2);
}

int MinHeap::getLeft(int loc){
    return ((loc * 2) + 1);
}

int MinHeap::getRight(int loc){
    return ((loc * 2) + 1);
}

node* MinHeap::extractMin(){
    if (heap_size <= 0){
        node *max = new node;
        max->letter = '$';
        max->frequency = 1000000000;
        return max;
    }
    if (heap_size == 1){
        heap_size--;
        return h_array[0];
    }
    
    node *root = new node;
    root = h_array[0];
    h_array[0] = h_array[heap_size-1];
    heap_size--;
    MinHeapify(0);
 
    return root;
}

node* MinHeap::getMin(){
    return h_array[0];
}

int MinHeap::getSize() {
  return heap_size;
}

void MinHeap::printLine() {
  for (int i = 0; i < heap_size; i++) {
    cout << h_array[i]->letter << ":" << h_array[i]->frequency << ", ";
  }
  cout << endl;
}