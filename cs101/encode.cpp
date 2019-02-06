#include <iostream>
#include <fstream>
#include <string>

#include "List.h"
#include "MinHeap.h"
#include "Huffman.h"

using namespace std;

int main(int argc, char *argv[]) {
    string input;
    unsigned char ch;
    ifstream in(argv[1], ios::in|ios::binary|ios::ate);
    size_t size = 0;
    size = in.tellg();

    in.seekg(0, ios::beg);
    List freqList = List(size);

    for (unsigned int i = 0; i < size; i++) {
      ch = in.get();
      freqList.insert((int)ch);
      input += ch;
    }

    MinHeap minHeap = MinHeap(freqList.getSize(), freqList.getArray());

    node *tree = new node;
    HuffmanTree *huffmanTree = new HuffmanTree();
    tree = huffmanTree->buildTree(minHeap);

    string code = "";

    huffmanTree->printPreOrder(tree, code);
    huffmanTree->printInOrder(tree, code);
    
    code = huffmanTree->encode(input);

    huffmanTree->printCode(code);
    huffmanTree->encodeBin(input);

    delete huffmanTree;
}