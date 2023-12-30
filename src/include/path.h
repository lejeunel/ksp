#ifndef PATH_H_
#define PATH_H_

#include <vector>
#include <memory>
#include "misc.h"
#include "node.h"

class Path {
public:
  Path();

  void append(std::shared_ptr<Node>);
  std::shared_ptr<Node> operator[](int);
  void print();
  scalar_t length;

private:
  std::vector<std::shared_ptr<Node>> nodes;
};

#endif // PATH_H_
