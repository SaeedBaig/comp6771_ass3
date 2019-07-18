#ifndef ASSIGNMENTS_DG_GRAPH_H_
#define ASSIGNMENTS_DG_GRAPH_H_

#include <set>
#include <memory>

namespace gdwg {

template <typename N, typename E>
class Graph {
 public:
  class const_iterator {};

  bool InsertNode(const N& val);
  //methods
  
 private:
 	std::set<N> nodes_;
 	std::set<Edge> edges_;
};

class Edge {
 public:

 private:
 	weak_ptr<N> from;
 	weak_ptr<N> to;
 	E weight;
};

}  // namespace gdwg

#include "assignments/dg/graph.tpp"

#endif  // ASSIGNMENTS_DG_GRAPH_H_
