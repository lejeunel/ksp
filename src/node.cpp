#include "include/node.h"
#include "include/easylogging++.h"
#include "include/edge.h"
#include <algorithm>
#include <memory>

int Node::get_id() { return id; }

void Node::add_leaving_edge(EdgePtr e) { out_edges.push_back(e); }

EdgeList Node::get_out_edges() { return out_edges; }

Path Node::make_path_from_root() {
  Path res;
  res.append(id);
  LOG(DEBUG) << "making path from " << id << " to root";
  auto pred = get_predecessor();
  while (pred != nullptr) {
    LOG(DEBUG) << "got predecessor " << pred->get_id();
    auto id = pred->id;
    res.append(id);
    pred = pred->get_predecessor();
  }
  LOG(DEBUG) << "done";

  res.reverse();
  return res;
}
