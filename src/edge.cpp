#include "include/edge.h"
#include <algorithm>

void Edge::invert() {
  length = -length;
  positivized_length = -positivized_length;
}
