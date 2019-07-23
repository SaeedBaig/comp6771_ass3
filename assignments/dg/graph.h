#ifndef ASSIGNMENTS_DG_GRAPH_H_
#define ASSIGNMENTS_DG_GRAPH_H_

#include <set>
#include <memory>

namespace gdwg {

template <typename N, typename E>
//n for string
//e for double

class Graph {
 public:
  class const_iterator {};

  //constructors
  gdwg::Graph<N, E>();

  gdwg::Graph<N, E>(
    std::vector<N>::const_iterator,
    std::vector<N>::const_iterator
  );

  gdwg::Graph<N, E>(
    std::vector<std::tuple<N, N, E>>::const_iterator,
    std::vector<std::tuple<N, N, E>>::const_iterator
  );

  gdwg::Graph<N, E>(std::initializer_list<N>);

  gdwg::Graph<N, E>(const gdwg::Graph<N, E>&);

  gdwg::Graph<N, E>(gdwg::Graph<N, E>&&);

  ~gdwg::Graph<N, E>();

  gdwg::Graph<N, E>& operator=(const gdwg::Graph<N, E>&);

  gdwg::Graph<N, E>& operator=(gdwg::Graph<N, E>&&);

  //methods
  bool InsertNode(const N& val);
  bool InsertEdge(const N& src, const N& dst, const E& w);
  bool DeleteNode(const N& node);
  bool Replace(const N& oldData, const N& newData);
  void MergeReplace(const N& oldData, const N& newData);
  void Clear();
  bool IsNode(const N& val);
  bool IsConnected(const N& src, const N& dst);
  std::vector<N> GetNodes();
  std::vector<N> GetConnected(const N& src);
  std::vector<E> GetWeights(const N& src, const N& dst);

  //iterator methods
  const_iterator find(const N&, const N&, const E&);
  bool erase(const N& src, const N& dst, const E& w);
  const_iterator erase(const_iterator it);
  const_iterator cbegin();
  const_iterator cend();

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
