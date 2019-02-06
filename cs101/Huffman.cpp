#include <string>
#include <iostream>
#include "Huffman.h"

using namespace std;

HuffmanTree::HuffmanTree(){
    treeSize = 0;
    treeRoot = new node;
    
    preorder.open("./preorder.txt", ios::out|ios::binary);
    inorder.open("./inorder.txt", ios::out|ios::binary);
    codeFile.open("./code.txt");
    codeBin.open("./code.bin");
}

HuffmanTree::~HuffmanTree(){
    preorder.close();
    inorder.close();
    codeFile.close();
    codeBin.close();
}

node* HuffmanTree::buildTree(MinHeap m_heap){
    node *right = new node;
    node *left = new node;

    int offset = 0;

    while(m_heap.getSize() != 1){
        node *parent = new node;

        left = m_heap.extractMin();
        right = m_heap.extractMin();

        parent->frequency = left->frequency + right->frequency;
        parent->letter = 128 + offset;

        parent->left = left;
        parent->right = right;

        left->parent = right->parent = parent;
        
        m_heap.insert(parent);
        offset++;
    }

    treeRoot = m_heap.extractMin();
    return treeRoot;
}

int HuffmanTree::getSize(){
    return treeSize;
}

void HuffmanTree::printPreOrder(node *root, string code){
    if(root == NULL){
        return;
    }

    root->code = code;
    
    preorder.put(root->letter);

    string leftCode = code + "0";
    string rightCode = code + "1";

    printPreOrder(root->left, leftCode);
    printPreOrder(root->right, rightCode);

}

void HuffmanTree::printInOrder(node *root, string code){
    if(root == NULL){
        return;
    }
    
    string leftCode = code + "0";
    string rightCode = code + "1";

    printInOrder(root->left, leftCode);
    inorder.put(root->letter);
    printInOrder(root->right, rightCode);

}

void HuffmanTree::printCode(string code){
    codeFile << code;
    codeFile.flush();
}

string HuffmanTree::encode(string text){
    string code = "";

    for(int i = 0; i < text.size(); i++){
        code += findCode(treeRoot, text[i], "");
    }
    return code;
}

string HuffmanTree::encodeBin(string text){
 string code = "";
  code = encode(text);
  size_t textSize = text.size();
  size_t size = code.size();
  //cout << textSize << " - " << size << endl;

  int diff = 16;
  if ((size % 8) != 0) {
    diff += (8 - (size % 8));
  }

  size += diff;
  //cout << size/8 << endl;
  unsigned char b_array[size/8] = {0};

  b_array[0] = (textSize & 0xFF);
  b_array[1] = ((textSize >> 8) & 0xFF);

  //cout << b_array[0] << endl;
  //cout << b_array[1] << endl;

  unsigned char ch = 0;
  for (int i = 2; i < size; i++) {
    if ((i-2) < code.size()) {
      if ((i-2) % 8 == 0 && i > 8) {
        b_array[(i/8) + 1] = ch;
        ch = 0;
      }
      unsigned char tempChar = code[i-2] - '0';

      // cout << "if/temp: " << (int)tempChar << endl;
      // cout << "i mod 8: " << (i-2) % 8 << endl;
      if ((i-2) % 8 == 0) {
        ch |= (1 << (7)) * tempChar;
        //cout << (int) ch << endl;
      }
      else {
        ch |= (1 << 7 - ((i-2) % 8)) * tempChar;
        //cout << (int) ch << endl;
      }
      //cout << "ch: " << (int)ch << endl;
    }
    else {
      unsigned char tempChar = 0;
      // cout << "tempChar: " << (int) tempChar << endl;
      // cout << "else/i mod 8: " << (i-2) % 8 << endl;
      if ((i - 2) % 8 != 0) {
        ch |= (1 << 7 - ((i-2) % 8)) * tempChar;
        //cout << (int) ch << endl;
      }
      else {
        b_array[i/8 + 1] = ch;
      }

      if ((i/8) > (size/8)) {
        break;
      }
    }
  }

  /*for (int i = 0; i < (size/8); i++) {
    cout << "b_array[" << i << "]: " << (int)b_array[i] << endl;
  }
    */
  codeBin.write((const char *)&b_array[0], size/8);
  codeBin.flush();

  return code;
}

string HuffmanTree::findCode(node *root, unsigned char l, string code){
    if (root == NULL){
        return "";
    }

    if (root->letter == l){
        return root->code;
    }

    code = findCode(root->left, l, code);
    if (code == ""){
        code = findCode(root->right, l, code);
    }

    return code;
}