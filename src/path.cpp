#include "include/path.h"
#include "include/graph.h"
#include <iostream>
#include <memory>

Path::Path() {}

void Path::append(std::shared_ptr<Node> node){
  nodes.push_back(node);
};

std::shared_ptr<Node> Path::operator[](int pos){
  return nodes[pos];
}

void Path::print() {

  std::cout << "length: " << length << std::endl;
  for (int i = 0; i < this->length; ++i) {
    if (i < this->length - 1)
      std::cout << "->";
  }
  std::cout << std::endl;
}
