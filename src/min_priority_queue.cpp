#include "include/min_priority_queue.h"

void MinPriorityQueue::add_with_distance_priority(NodePtr const &n) {
  q.push(n);
}

NodePtr MinPriorityQueue::extract_non_deleted_min() {
  while (true) {
    auto n = q.top();
    q.pop();
    if (!n->is_deleted()) {
      return n;
    }
  }
}

bool MinPriorityQueue::is_empty() { return q.empty(); }
