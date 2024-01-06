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

Path::Path(EdgePtr const &e) {

  edges.push_back(e);
  length = e->length;
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

bool Path::is_equal(const std::vector<int> &rhs) {
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
std::string Path::to_str() {

  std::stringstream buffer;
  for (auto e : edges) {
    buffer << "(" << e->source_node->id << " -> " << e->target_node->id
           << "), ";
  }

  buffer << " length: " << length;

  return buffer.str();
}

void Path::print() { LOG(DEBUG) << this->to_str(); }

void Path::set_occupied(const bool &val) {
  for (auto e : edges) {
    e->occupied = val;
  }
}

void Path::append_edge(const EdgePtr &e) {
  edges.push_back(e);
  length += e->length;
}
