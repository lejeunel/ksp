#include "include/tree_node.h"
#include "include/easylogging++.h"

Path SPTreeNode::make_path_from_root() {
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
