#include <string>
#include <iostream>
#include "List.h"

using namespace std;

List::List(){
    size = 0;
    capacity = 0;
}

List::List(int s){
    l_array = new node *[s];
    capacity = s;
    size = 0;
    for (int i = 0; i < s; i++){
        l_array[i] = new node;
    }
}

List::~List(){
    delete []l_array;
}

node* List::get(unsigned char l){
    node *current = new node;
    current = NULL;

    for (int i = 0; i < size; i++){
        if(l_array[i]->letter == l)
            return l_array[i];
    }
    return current;
}

node* List::getHeadNode(){
    return l_array[0];
}

node** List::getArray(){
    return l_array;
}

void List::insert(unsigned char l){
    node *exists = new node;
    node *newChar = new node;
    exists = get(l);

    if (exists == NULL){
        newChar->letter = l;
        newChar->frequency = 1;
        newChar->left = NULL;
        newChar->right = NULL;
        if (size < capacity) {
            l_array[size] = newChar;
        }
        size++;
    }
    else{
        exists->frequency += 1;
    }
}

int List::getSize(){
    return size;
}