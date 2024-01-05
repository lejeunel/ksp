#ifndef MIN_PRIORITY_QUEUE_H_
#define MIN_PRIORITY_QUEUE_H_
#include "common.h"
#include "tree_node.h"
#include <queue>

struct Compare {
  bool operator()(SPTreeNodePtr const &a, SPTreeNodePtr const &b) {
    return a->get_dist_from_root() > b->get_dist_from_root();
  }
};

class MinPriorityQueue {

public:
  void add_with_distance_priority(SPTreeNodePtr const &);
  SPTreeNodePtr extract_non_deleted_min();
  bool is_empty();

private:
  std::vector<SPTreeNodePtr> tree_nodes;
  std::priority_queue<SPTreeNodePtr, std::vector<SPTreeNodePtr>, Compare> q;
};
#endif // MIN_PRIORITY_QUEUE_H_
