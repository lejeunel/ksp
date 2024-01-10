#ifndef COMMON_H_
#define COMMON_H_
#include <limits>
#include <memory>
#include <vector>

class Node;
class Edge;

typedef float scalar_t;
const scalar_t INF_LENGTH = std::numeric_limits<scalar_t>::max();
const scalar_t FLT_MAX = std::numeric_limits<scalar_t>::max();

struct DiGraphEdge {
  int in_node;
  int out_node;
  float weight;
};

typedef std::vector<DiGraphEdge> DiGraphEdges;

#endif // COMMON_H_
