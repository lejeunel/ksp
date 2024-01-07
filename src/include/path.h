#ifndef PATH_H_
#define PATH_H_

#include "common.h"
#include "directed_graph.h"
#include "easylogging++.h"
#include <algorithm>
#include <iostream>
#include <memory>

class Path {
public:
  Path();
  Path(EdgeList const &);
  Path(EdgePtr const &);

  EdgePtr operator[](int);
  bool operator==(const Path &rhs);
  bool operator==(const std::vector<int> &rhs);
  friend std::ostream &operator<<(std::ostream &, const Path &);

  scalar_t get_length() { return length; }
  void set_occupied(const bool &);
  EdgeList get_edges() { return edges; }
  void append_edge(const EdgePtr &);

private:
  EdgeList edges;
  scalar_t length = 0;
};

struct compare_paths_lengths {
  inline bool operator()(const PathPtr &path1, const PathPtr &path2) {
    return (path1->get_length() < path2->get_length());
  }
};

#endif // PATH_H_
