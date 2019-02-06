#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "MinHeap.h"
#include <fstream>

using namespace std;

class HuffmanTree{
    private:
        int treeSize;
        node *treeRoot;
        ofstream preorder;
        ofstream inorder;
        ofstream codeFile;
        ofstream codeBin;

    public:
        HuffmanTree();
        ~HuffmanTree();
        node* buildTree(MinHeap m_heap);
        int getSize();
        void printPreOrder(node *root, string code);
        void printInOrder(node *root, string code);
        void printCode(string code);
        string encode(string text);
        string encodeBin(string text);
        string findCode(node *root, unsigned char l, string code);
};

#endif