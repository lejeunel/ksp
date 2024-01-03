#include "include/node.h"
#include "include/edge.h"
#include <algorithm>
#include <memory>

Node::Node(int a_id) { id = a_id; }

int Node::get_id() { return id; }

void Node::add_leaving_edge(std::shared_ptr<Edge> e) {
  leaving_edges.push_back(e);
}

std::vector<std::shared_ptr<Edge>> Node::get_leaving_edges() {
    return leaving_edges;
}

