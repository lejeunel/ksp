#include "include/path.h"
#include "include/directed_graph.h"
#include <iostream>
#include <memory>

Path::Path() {}

void Path::append(const int &id) { nodes.push_back(id); };

int Path::operator[](int pos) { return nodes[pos]; }
bool Path::operator==(const std::vector<int> &rhs) { return nodes == rhs; }

void Path::print() {

  std::cout << "length: " << length << std::endl;
  for (int i = 0; i < this->length; ++i) {
    if (i < this->length - 1)
      std::cout << "->";
  }
  std::cout << std::endl;
}
