#ifndef KSP_H_
#define KSP_H_

#include "graph.h"
#include "path.h"
#include <memory>

class KSP {

public:
    KSP(std::unique_ptr<Graph> graph, int source, int sink);
    std::vector<Path> run(int);

private:
  std::unique_ptr<Graph> graph;
  std::shared_ptr<Node> source;
  std::shared_ptr<Node> sink;

};

#endif // KSP_H_
