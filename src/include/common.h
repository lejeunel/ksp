#ifndef COMMON_H_
#define COMMON_H_
#include <limits>
#include <memory>
#include <vector>

class Node;
class Edge;
class SPTreeNode;

typedef std::shared_ptr<Edge> EdgePtr;
typedef std::vector<EdgePtr> EdgeList;
typedef std::shared_ptr<Node> NodePtr;
typedef std::shared_ptr<SPTreeNode> SPTreeNodePtr;
typedef std::vector<NodePtr> NodeList;

typedef float scalar_t;
const scalar_t INF_LENGTH = std::numeric_limits<scalar_t>::max();
const scalar_t FLT_MAX = std::numeric_limits<scalar_t>::max();

#endif // COMMON_H_
