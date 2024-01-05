#include "include/path.h"
#include "include/directed_graph.h"
#include "include/easylogging++.h"
#include <iostream>
#include <memory>

Path::Path() {}
Path::Path(EdgeList const &edge_list) {

  edges = edge_list;
  for (auto e : edges) {
    length += e->length;
  }
}

EdgePtr Path::operator[](int pos) { return edges[pos]; }
bool Path::operator==(const Path &rhs) {
  if (edges.size() != rhs.edges.size()) {
    return false;
  }

  for (int i = 0; i < edges.size(); ++i) {
    if ((edges[i]->source_node->id != rhs.edges[i]->source_node->id)) {
      return false;
    }
    if ((edges[i]->target_node->id != rhs.edges[i]->target_node->id)) {
      return false;
    }
  }
  return true;
}

bool Path::operator==(const std::vector<int> &rhs) {
  if (edges.size() != (rhs.size() - 1)) {
    LOG(DEBUG) << "size mismatch. Got num edges=" << edges.size()
               << " and number of nodes=" << rhs.size();
    return false;
  }
  for (int i = 0; i < rhs.size() - 1; ++i) {
    if ((edges[i]->source_node->id != rhs[i])) {
      return false;
    }
    if ((edges[i]->target_node->id != rhs[i + 1])) {
      return false;
    }
  }
  return true;
}

void Path::print() {
  for (auto e : edges) {
    LOG(DEBUG) << "(" << e->source_node->id << ", " << e->source_node << ") "
               << "-> (" << e->target_node->id << ", " << e->target_node << ")";
  }
}

void Path::invert_edges() {
  for (auto e : edges) {
    LOG(DEBUG) << "inverting edge (" << e->source_node->id << ", "
               << e->source_node << ") "
               << "-> (" << e->target_node->id << ", " << e->target_node << ")";
    e->length = -e->length;
    e->source_node->del_out_edge(e);

    auto orig_tgt = e->target_node;

    (e->source_node).swap(e->target_node);
    orig_tgt->add_out_edge(e);

    LOG(DEBUG) << "inverted edge (" << e->source_node->id << ", "
               << e->source_node << ") "
               << "-> (" << e->target_node->id << ", " << e->target_node << ")";

    LOG(DEBUG) << "num out edge in node " << orig_tgt->id << ": "
               << orig_tgt->out_edges.size();
    for (auto e : orig_tgt->out_edges) {

      LOG(DEBUG) << "(" << e->source_node->id << ", " << e->source_node << ") "
                 << "-> (" << e->target_node->id << ", " << e->target_node
                 << ")";
    }
    break;
  }
}

void Path::set_occupied(const bool &val) {
  for (auto e : edges) {
    e->occupied = val;
  }
}
