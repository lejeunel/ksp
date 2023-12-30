#ifndef EDGE_H_
#define EDGE_H_
#include "misc.h"
#include <memory>

class Node;

class Edge {
public:
    Edge(std::shared_ptr<Node> _start_node,
                std::shared_ptr<Node> _end_node, scalar_t _length);
    std::shared_ptr<Node> get_start_node();
    std::shared_ptr<Node> get_end_node();

    inline void invert();
  private:

    int occupied;
    scalar_t length, positivized_length;
    std::shared_ptr<Node> start_node, end_node;

    // These fields are used for the linked list of a node's leaving
    // edge list. We have to do insertions / deletions.
    Edge *next_leaving_edge, *pred_leaving_edge;
};


#endif // EDGE_H_
