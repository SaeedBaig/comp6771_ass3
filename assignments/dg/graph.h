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

  struct Node {

  	Node (std::string node_name) {
  		node_name_=std::make_shared<std::string>(node_name);
  	}

  	void replaceNodeName(std::string node_name) {
  		node_name_.reset();
  		node_name_=std::make_shared<std::string>(node_name);
  	}

  	std::string getNodeName() {
  		return *node_name_;
  	}

  	std::shared_ptr<std::string> node_name_;
  };


  struct Edge {
  		//public:
  		Edge(N from, N to, E weight) {
			auto share_ptr_for_from=std::make_shared<N>(from);
			from_ = share_ptr_for_from;

			auto share_ptr_for_to=std::make_shared<N>(to);
			to_ = share_ptr_for_to;

			auto share_ptr_for_weight=std::make_shared<E>(weight);
			weight_ = share_ptr_for_weight;
  		}

		~Edge() {
			std::cout << "edge descructor called" << std::endl;
		}

		std::shared_ptr<N> from_; //should be weak pointer
		std::shared_ptr<N> to_; // should be weak pointer
		std::shared_ptr<E> weight_;
  	};

  std::unordered_set<std::shared_ptr<N>> getList() {
	  return nodes_;
  }

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
  bool DeleteNode(const N& val);
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
	  std::unordered_set<std::shared_ptr<N>> nodes_;
	  std::vector<std::shared_ptr<Edge>> edges_; // stored in the stack
};
}

//helper methods
template <typename N, typename E>
//return the first found edge that contains either the soruce or the destination that matches the parameter value
//or otherwise null
auto GetEdgeIterByValue(const N& value);


//#include "assignments/dg/graph.tpp"
#include "assignments/dg/graph.tpp"
#endif  // ASSIGNMENTS_DG_GRAPH_H_
