#include "include/min_priority_queue.h"

void MinPriorityQueue::add(const int &id) { q.push(id); }

int MinPriorityQueue::extract_min() {

  while (true) {
    auto n = q.top();

    q.pop();

    if (!is_node_visited[n]) {
      return n;
    }
  }
}

bool MinPriorityQueue::is_empty() { return q.empty(); }
