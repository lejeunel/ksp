#ifndef NODE_H_
#define NODE_H_
#include "edge.h"
#include "misc.h"
#include <vector>

class Node {
  public:
    Node(int);


    int get_id();
    void add_leaving_edge(std::shared_ptr<Edge>);
    void del_leaving_edge(std::shared_ptr<Edge>);
    std::vector<std::shared_ptr<Edge>> get_leaving_edges();

  private:
    int id;
    std::vector<std::shared_ptr<Edge>> leaving_edges;
};


#endif // NODE_H_
