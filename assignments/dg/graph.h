#ifndef ASSIGNMENTS_DG_GRAPH_H_
#define ASSIGNMENTS_DG_GRAPH_H_

#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <tuple>
#include <vector>
#include <string>

using std::cout;
using std::shared_ptr;
using std::make_shared;
using std::vector;
using std::tuple;

namespace gdwg {

template <typename N, typename E>
class Graph {
 public:
   struct Node {
       shared_ptr<N> node_ptr_;
       // constructor
       Node(const N& node): node_ptr_{make_shared<N>(node)} {}

       // necessary for std::find() and graph == operator to work
       friend bool operator==(const Node& a, const Node& b) {
         return *(a.node_ptr_) == *(b.node_ptr_);
       }

       // necessary for std::sort() to work
       friend bool operator<(const Node& a, const Node& b) {
         return *(a.node_ptr_) < *(b.node_ptr_);
       }
   };

   struct Edge {
     shared_ptr<N> src_ptr_;
     shared_ptr<N> dst_ptr_;
     shared_ptr<E> weight_ptr_;

     // constructor
     Edge(const shared_ptr<N>& src, const shared_ptr<N>& dst, const E& w):
       src_ptr_{src},
       dst_ptr_{dst},
       weight_ptr_{make_shared<E>(w)} {}

     // necessary for std::find() and graph == operator to work
     friend bool operator==(const Edge& a, const Edge& b) {
       return *(a.src_ptr_) == *(b.src_ptr_) &&
              *(a.dst_ptr_) == *(b.dst_ptr_) &&
              *(a.weight_ptr_) == *(b.weight_ptr_);
     }

     // necessary for std::sort() to work
     friend bool operator<(const Edge& a, const Edge& b) {
       const auto& a_src = *(a.src_ptr_);
       const auto& b_src = *(b.src_ptr_);
       const auto& a_dst = *(a.dst_ptr_);
       const auto& b_dst = *(b.dst_ptr_);
       const auto& a_weight = *(a.weight_ptr_);
       const auto& b_weight = *(b.weight_ptr_);

       return a_src < b_src
          || (a_src == b_src && a_dst < b_dst)
          || (a_src == b_src && a_dst == b_dst && a_weight < b_weight);
     }
   };


   class const_iterator {
     public:
       using iterator_category = std::bidirectional_iterator_tag;
       using value_type = tuple<N, N, E>;
       using reference = tuple<const N&, const N&, const E&>;
       using difference_type = int;

       // constructor
       const_iterator(const typename vector<Edge>::const_iterator& it) : it_{it} {}
       reference operator*() const;
       const_iterator& operator++();
       const_iterator operator++(int);
       const_iterator& operator--();
       const_iterator operator--(int);

       friend bool operator==(const const_iterator& lhs, const const_iterator& rhs) {
         return lhs.it_ == rhs.it_;
       }

       friend bool operator!=(const const_iterator& lhs, const const_iterator& rhs) {
         return !(lhs == rhs);
       }

     private:
       typename vector<Edge>::const_iterator it_;
       friend class Graph;
   };
   using const_reverse_iterator = std::reverse_iterator<const_iterator>;

   const_iterator cbegin() const { return const_iterator{edges_.cbegin()}; }
   const_iterator cend() const { return const_iterator{edges_.cend()}; }
   const_reverse_iterator crbegin() const { return const_reverse_iterator{edges_.crbegin()}; }
   const_reverse_iterator crend() const { return const_reverse_iterator{edges_.crend()}; }
   const_iterator begin() { return cbegin(); }
   const_iterator end() { return cend(); }
   const_reverse_iterator rbegin() { return crbegin(); }
   const_reverse_iterator rend() { return crend(); }

   const_iterator find(const N& src, const N& dst, const E& w) const;
   const_iterator erase(const_iterator it);

  // constructors//
  Graph<N, E>(void) {}
  Graph<N, E>(typename std::vector<N>::const_iterator start, typename std::vector<N>::const_iterator end);
  Graph<N, E>(typename std::vector<std::tuple<N, N, E>>::const_iterator start, typename std::vector<std::tuple<N, N, E>>::const_iterator end);
  Graph<N, E>(std::initializer_list<N> list);
  Graph<N, E>(const Graph& other);
  Graph<N, E>(Graph&& other);

  //destructor
  ~Graph() = default;   // the vectors and smart pointers will deallocate themselves

  // copy assignment
  Graph<N, E>& operator=(const Graph<N, E>& other);
 // move assignment
  Graph<N, E>& operator=(Graph<N, E>&& other);

  //methods
  bool IsNode(const N& val) const;
  bool InsertNode(const N& val);
  bool InsertEdge(const N& src, const N& dst, const E& w);
  bool DeleteNode(const N& n);
  bool IsConnected(const N& src, const N& dst) const;
  bool Replace(const N& oldData, const N& newData);
  void MergeReplace(const N& oldData, const N& newData);
  void Clear();
  std::vector<N> GetNodes() const;
  std::vector<N> GetConnected(const N& src) const;
  std::vector<E> GetWeights(const N& src, const N& dst) const;
  bool erase(const N& src, const N& dst, const E& w);

  //friends
  friend bool operator==(const Graph& a, const Graph& b) {
	  return a.nodes_ == b.nodes_ && a.edges_ == b.edges_;
   }

  friend bool operator!=(const Graph& a, const Graph& b) {
	  return !(a == b);
  }

  friend std::ostream& operator<<(std::ostream& os, const Graph& graph) {
	  auto tmp_nodes = graph.nodes_;
	  std::sort(tmp_nodes.begin(), tmp_nodes.end());

	  for (const auto& node : tmp_nodes) {
		os << *(node.node_ptr_) << " (\n";
		for (const auto& edge : graph.edges_) {
		  if (*(edge.src_ptr_) == *(node.node_ptr_)) {
			os << "  " << *(edge.dst_ptr_) << " | " << *(edge.weight_ptr_) << '\n';
		  }
		}
		os << ")\n";
	  }

	  return os;
  }

 private:
   vector<Node> nodes_;
   vector<Edge> edges_;
};

}

#include "assignments/dg/graph.tpp"

#endif  // ASSIGNMENTS_DG_GRAPH_H_
