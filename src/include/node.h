#ifndef NODE_H_
#define NODE_H_
#include "edge.h"
#include "misc.h"

class Node {
  public:
    Node(int);

    bool visited = false; //used for topological sort

    scalar_t distance_from_source;
    Edge *pred_edge_toward_source;

    Edge *leaving_edge_list_root;
    Node **heap_slot;

    int get_id();
    void add_leaving_edge(Edge *e);
    void del_leaving_edge(Edge *e);
    void decrease_distance_in_heap(Node **heap);
    void increase_distance_in_heap(Node **heap, Node **heap_bottom);
  private:
    int id;
};


#endif // NODE_H_
