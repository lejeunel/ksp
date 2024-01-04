#ifndef PATH_H_
#define PATH_H_

#include "common.h"
#include <algorithm>

class Path {
public:
  Path();

  void append(const int &id);
  int operator[](int);
  bool operator==(const std::vector<int> &rhs);
  void reverse() { std::reverse(nodes.begin(), nodes.end()); }
  void print();
  scalar_t length;

private:
  std::vector<int> nodes;
};

#endif // PATH_H_
