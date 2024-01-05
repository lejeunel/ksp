#ifndef PATH_H_
#define PATH_H_

#include "common.h"
#include <algorithm>

class Path {
public:
  Path();
  Path(EdgeList const &);

  EdgePtr operator[](int);
  bool operator==(const Path &rhs);
  bool operator==(const std::vector<int> &rhs);
  void print();
  scalar_t get_length() { return length; }
  void invert_edges();
  void set_occupied(const bool &);

private:
  EdgeList edges;
  scalar_t length = 0;
};

#endif // PATH_H_
