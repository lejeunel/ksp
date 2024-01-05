#include "include/node.h"
#include "include/edge.h"
#include <algorithm>
#include <memory>

Node::Node(const int &a_id) : id(a_id) {}
Node::Node(int const &a_id, EdgeList const &a_leaving_edges)
    : id(a_id), leaving_edges(a_leaving_edges) {}

int Node::get_id() { return id; }

void Node::add_leaving_edge(EdgePtr e) { leaving_edges.push_back(e); }

EdgeList Node::get_leaving_edges() { return leaving_edges; }
