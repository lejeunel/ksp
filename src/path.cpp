#include "include/path.h"

Path::Path() {}

void Path::append_edge(const int &from, const int &to,
                       const scalar_t &a_length) {
  if (nodes.size() == 0) {
    nodes.push_back(from);
  }
  nodes.push_back(to);
  length += a_length;
}

bool Path::operator==(const Path &rhs) const {
  if (this->length != rhs.length) {
    LOG(TRACE) << "length mismatch. Got " << this->length << " and (rhs) "
               << rhs.length;
    return false;
  }
  if (nodes.size() != rhs.nodes.size()) {
    LOG(TRACE) << "size mismatch. Got num nodes=" << nodes.size()
               << " and number of nodes=" << rhs.nodes.size();
    return false;
  }
  for (unsigned int i = 0; i < rhs.nodes.size(); ++i) {
    if ((nodes[i] != rhs.nodes[i])) {
      return false;
    }
  }
  return true;
}

std::ostream &operator<<(std::ostream &os, const Path &path) {
  os << path.nodes[0];
  for (unsigned int i = 1; i < path.nodes.size(); ++i) {
    os << " -> " << path.nodes[i];
  }

  os << " (length= " << path.length << ")";

  return os;
}
