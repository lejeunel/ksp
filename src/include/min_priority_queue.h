#ifndef MIN_PRIORITY_QUEUE_H_
#define MIN_PRIORITY_QUEUE_H_
#include "common.h"
#include "node.h"
#include <queue>

struct Compare {
  bool operator()(NodePtr const &a, NodePtr const &b) {
    return a->dist_from_root > b->dist_from_root;
  }
};

class MinPriorityQueue {

public:
  void add_with_distance_priority(NodePtr const &);
  NodePtr extract_non_deleted_min();
  bool is_empty();

private:
  std::priority_queue<NodePtr, std::vector<NodePtr>, Compare> q;
};
#endif // MIN_PRIORITY_QUEUE_H_
