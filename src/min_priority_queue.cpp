#include "include/min_priority_queue.h"

void MinPriorityQueue::add_with_distance_priority(const Node *n) { q.push(n); }

const Node *MinPriorityQueue::extract_min() {
  auto n = q.top();
  q.pop();
  return n;
}

bool MinPriorityQueue::is_empty() { return q.empty(); }
