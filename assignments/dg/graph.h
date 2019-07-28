#ifndef ASSIGNMENTS_DG_GRAPH_H_
#define ASSIGNMENTS_DG_GRAPH_H_

#include <string>
#include <memory>
#include <vector>
#include <unordered_set>
#include <tuple>
#include <set>
#include <iostream>

namespace gdwg {

template <typename N, typename E>
class Graph {
 public:
  class const_iterator {};

  Graph() {}

  class Edge {
	public:
		Edge(N from, N to, E weight):from_(from),to_(to),weight_(weight) {}

		N& GetFrom() {
			return from_;
		}

		N& GetTo() {
			return to_;
		}

		E& GetWeight() {
			return weight_;
		}

	 private:
		N from_;
		N to_;
		E weight_;
  	};
  Graph<N, E>(typename std::vector<N>::const_iterator start,typename std::vector<N>::const_iterator end);

  Graph<N, E>(typename std::vector<std::tuple<N, N, E>>::const_iterator start,
    typename std::vector<std::tuple<N, N, E>>::const_iterator end);

  Graph<N, E>(std::initializer_list<N> list);

  Graph<N, E>(const Graph<N, E>& graph);

  Graph<N, E>(Graph<N, E>&& graph);

  ~Graph<N,E>() {}

  Graph<N, E>& operator=(const Graph<N, E>& graph);
  Graph<N, E>& operator=(Graph<N, E>&& graph);

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
	  std::weak_ptr<N> node_name_; //need to use this
	  std::weak_ptr<E> weight_;

	  std::unordered_set<N> nodes_;
	  std::vector<Edge> edges_;
};
}

//#include "assignments/dg/graph.tpp"
#include "assignments/dg/graph.tpp"
#endif  // ASSIGNMENTS_DG_GRAPH_H_
