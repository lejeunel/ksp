#include "include/path.h"

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
    if ((edges[i]->source_node.lock()->id !=
         rhs.edges[i]->source_node.lock()->id)) {
      return false;
    }
    if ((edges[i]->target_node.lock()->id !=
         rhs.edges[i]->target_node.lock()->id)) {
      return false;
    }
  }
  return true;
}

bool Path::operator==(const std::vector<int> &rhs) {
  if (edges.size() != (rhs.size() - 1)) {
    LOG(TRACE) << "size mismatch. Got num edges=" << edges.size()
               << " and number of nodes=" << rhs.size();
    return false;
  }
  for (int i = 0; i < rhs.size() - 1; ++i) {
    if ((edges[i]->source_node.lock()->id != rhs[i])) {
      return false;
    }
    if ((edges[i]->target_node.lock()->id != rhs[i + 1])) {
      return false;
    }
  }
  return true;
}

std::ostream &operator<<(std::ostream &os, const Path &path) {
  os << path.edges[0]->source_node.lock()->id;
  for (auto e : path.edges) {
    os << " -> " << e->target_node.lock()->id;
  }

  os << " (length= " << path.length << ")";

  return os;
}

void Path::set_occupied(const bool &val) {
  for (auto e : edges) {
    e->occupied = val;
  }
}

void Path::append_edge(const EdgePtr &e) {
  edges.push_back(e);
  length += e->length;
}
