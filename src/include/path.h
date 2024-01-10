#ifndef PATH_H_
#define PATH_H_

#include "directed_graph.h"
#include "easylogging++.h"
#include "edge.h"
#include <iostream>

class Path {
public:
  Path();
  Path(const std::vector<int> &a_nodes, const scalar_t &a_length)
      : nodes(a_nodes), length(a_length) {}

  bool operator==(const Path &rhs) const;
  bool operator==(const std::vector<int> &rhs);
  int operator[](const int &place) const { return nodes[place]; }
  friend std::ostream &operator<<(std::ostream &, const Path &);

  scalar_t get_length() const { return length; }
  void append_edge(const int &from, const int &to, const scalar_t &a_length);
  void reverse() { std::reverse(nodes.begin(), nodes.end()); }
  int num_edges() const { return nodes.size() - 1; }
  int num_nodes() const { return nodes.size(); }

private:
  std::vector<int> nodes;
  scalar_t length = 0;
};

struct compare_paths_lengths {
  inline bool operator()(const Path &path1, const Path &path2) {
    return (path1.get_length() < path2.get_length());
  }
};

#endif // PATH_H_
