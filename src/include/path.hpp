#ifndef PATH_H_
#define PATH_H_

#include "graph.h"
#include <vector>
#include <memory>
#include "misc.h"
#include "node.h"

class Path {
public:
  Path(int n_nodes);
  Path(std::vector<int> node_indices);
  std::unique_ptr<Node> get_node_by_pos(int);
  void print();
  scalar_t length;

private:
  std::vector<std::unique_ptr<Node>> nodes;
};

#endif // PATH_H_
