#ifndef MIN_PRIORITY_QUEUE_H_
#define MIN_PRIORITY_QUEUE_H_
#include "common.h"
#include "node.h"
#include <queue>

struct Compare {
  bool operator()(const Node *a, const Node *b) {
    return a->get_dist_from_root() > b->get_dist_from_root();
  }
};

class MinPriorityQueue {

public:
  void add_with_distance_priority(const Node *);
  const Node *extract_min();
  bool is_empty();

private:
  std::priority_queue<const Node *, std::vector<const Node *>, Compare> q;
};
#endif // MIN_PRIORITY_QUEUE_H_
