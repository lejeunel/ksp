#include "include/node.h"
#include "include/edge.h"
#include <algorithm>

Node::Node(int _index) {
  leaving_edge_list_root = 0;
  index=_index;
}

void Node::add_leaving_edge(Edge *e) {
  e->next_leaving_edge = leaving_edge_list_root;
  e->pred_leaving_edge = 0;
  if (leaving_edge_list_root) {
    leaving_edge_list_root->pred_leaving_edge = e;
  }
  leaving_edge_list_root = e;
}

void Node::del_leaving_edge(Edge *e) {
  if (e == leaving_edge_list_root) {
    leaving_edge_list_root = e->next_leaving_edge;
  }
  if (e->pred_leaving_edge) {
    e->pred_leaving_edge->next_leaving_edge = e->next_leaving_edge;
  }
  if (e->next_leaving_edge) {
    e->next_leaving_edge->pred_leaving_edge = e->pred_leaving_edge;
  }
}

void Node::decrease_distance_in_heap(Node **heap) {
  Node **p, **h;
  h = heap_slot;
  while (1) {
    if (h <= heap)
      break;
    p = heap + ((h - heap + 1) >> 1) - 1;
    if ((*p)->distance_from_source <= distance_from_source)
      break;
    std::swap((*p)->heap_slot, heap_slot);
    std::swap(*p, *h);
    h = p;
  }
}

void Node::increase_distance_in_heap(Node **heap, Node **heap_bottom) {
  Node **c1, **c2, **h;
  h = heap_slot;
  while (1) {
    c1 = heap + 2 * (h - heap) + 1;
    if (c1 >= heap_bottom)
      break;
    c2 = c1 + 1;
    if ((*c1)->distance_from_source < distance_from_source) {
      if (c2 < heap_bottom &&
          (*c2)->distance_from_source < (*c1)->distance_from_source) {
        std::swap((*c2)->heap_slot, heap_slot);
        std::swap(*c2, *h);
        h = c2;
      } else {
        std::swap((*c1)->heap_slot, heap_slot);
        std::swap(*c1, *h);
        h = c1;
      }
    } else {
      if (c2 < heap_bottom &&
          (*c2)->distance_from_source < distance_from_source) {
        std::swap((*c2)->heap_slot, heap_slot);
        std::swap(*c2, *h);
        h = c2;
      } else
        break;
    }
  }
}
