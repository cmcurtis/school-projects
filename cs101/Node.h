#ifndef NODE_H
#define NODE_H

#include <string>

struct node {
  unsigned char letter;
  int frequency;
  std::string code;
  node *left;
  node *right;
  node *parent;
};

#endif