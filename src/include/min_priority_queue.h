#ifndef MIN_PRIORITY_QUEUE_H_
#define MIN_PRIORITY_QUEUE_H_
#include "common.h"
#include "directed_graph.h"
#include "node.h"
#include <queue>

struct Compare {
  DirectedGraph const &g;
  Compare(DirectedGraph const &g_) : g(g_) {}

  bool operator()(const int &first_node_id, const int &second_node_id) {
    return g.compare_dist_from_root(first_node_id, second_node_id);
  }
};

typedef std::priority_queue<int, std::deque<int>, Compare> NodePriorityQueue;

class MinPriorityQueue {

public:
  void add(const int &id);
  int extract_min();
  bool is_empty();
  MinPriorityQueue(DirectedGraph const &_g) : q(Compare(_g)) {
    is_node_visited = std::vector<uint8_t>(_g.num_of_nodes(), 0);
  };
  void set_node_as_visited(const int &id) { is_node_visited[id] = 1; }

private:
  NodePriorityQueue q;
  std::vector<uint8_t> is_node_visited;
};
#endif // MIN_PRIORITY_QUEUE_H_
