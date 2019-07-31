#ifndef ASSIGNMENTS_DG_GRAPH_H_
#define ASSIGNMENTS_DG_GRAPH_H_

// NOTE: sort(edges_) everytime you modify edges_ (so that iterator works properly)

#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <tuple>
#include <vector>
#include <string>

using std::cout;
using std::shared_ptr;
using std::unique_ptr;
using std::make_shared;
using std::make_unique;
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

       reference operator*() const {
         const N& node1 = *((*it_).src_ptr_);
         const N& node2 = *((*it_).dst_ptr_);
         const E& edge_w = *((*it_).weight_ptr_);

         return {node1, node2, edge_w};
       }

       const_iterator& operator++() {
         ++it_;
         return *this;
       }

       const_iterator operator++(int) {
         auto copy{*this};
         ++(*this);
         return copy;
       }

       const_iterator& operator--() {
         --it_;
         return *this;
       }

       const_iterator operator--(int) {
         auto copy{*this};
         --(*this);
         return copy;
       }

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


   class const_reverse_iterator {
     public:
       using iterator_category = std::bidirectional_iterator_tag;
       using value_type = tuple<N, N, E>;
       using reference = tuple<const N&, const N&, const E&>;
       using difference_type = int;

       // constructor
       const_reverse_iterator(const typename vector<Edge>::const_reverse_iterator& it) : it_{it} {}

       reference operator*() const {
         const N& node1 = *((*it_).src_ptr_);
         const N& node2 = *((*it_).dst_ptr_);
         const E& edge_w = *((*it_).weight_ptr_);

         return {node1, node2, edge_w};
       }

       const_reverse_iterator& operator++() {
         ++it_;
         return *this;
       }

       const_reverse_iterator operator++(int) {
         auto copy{*this};
         ++(*this);
         return copy;
       }

       const_reverse_iterator& operator--() {
         --it_;
         return *this;
       }

       const_reverse_iterator operator--(int) {
         auto copy{*this};
         --(*this);
         return copy;
       }

       friend bool operator==(const const_reverse_iterator& lhs, const const_reverse_iterator& rhs) {
         return lhs.it_ == rhs.it_;
       }
       friend bool operator!=(const const_reverse_iterator& lhs, const const_reverse_iterator& rhs) {
         return !(lhs == rhs);
       }

     private:
       typename vector<Edge>::const_reverse_iterator it_;

       friend class Graph;
   };


   //using const_reverse_iterator = std::reverse_iterator<const_iterator>;

   /* iterator methods */
   const_iterator cbegin() const { return const_iterator{edges_.cbegin()}; }
   const_iterator cend() const { return const_iterator{edges_.cend()}; }
   const_reverse_iterator crbegin() const { return const_reverse_iterator{edges_.crbegin()}; }
   const_reverse_iterator crend() const { return const_reverse_iterator{edges_.crend()}; }
   const_iterator begin() { return cbegin(); }
   const_iterator end() { return cend(); }
   const_reverse_iterator rbegin() { return crbegin(); }
   const_reverse_iterator rend() { return crend(); }


   const_iterator find(const N& src, const N& dst, const E& w) const {
     const auto it = std::find_if(edges_.cbegin(), edges_.cend(),
       [&](const Edge& edge){
         return *(edge.src_ptr_) == src && *(edge.dst_ptr_) == dst &&
                *(edge.weight_ptr_) == w;
       }
     );

     if (it != edges_.end()) {
       return const_iterator{it};
     } // else
     return cend();
   }


   const_iterator erase(const_iterator it) {
     const auto iter = edges_.erase(it.it_);
     if (iter != edges_.end()) {
       return const_iterator{iter};
     } // else
     return end();
   }


  /* constructors */
  // default
  Graph<N, E>(void) {}


  Graph<N, E>(typename std::vector<N>::const_iterator start, typename std::vector<N>::const_iterator end) {
    for (auto it = start; it != end; ++it) {
      InsertNode(*it);
    }
  }


  Graph<N, E>(typename std::vector<std::tuple<N, N, E>>::const_iterator start, typename std::vector<std::tuple<N, N, E>>::const_iterator end) {
    for (auto it = start; it != end; ++it) {
      const N& src = std::get<0>(*it);
      const N& dst = std::get<1>(*it);
      const E& w = std::get<2>(*it);

      InsertNode(src);
      InsertNode(dst);
      InsertEdge(src, dst, w);
    }
    std::sort(edges_.begin(), edges_.end());
  }


  Graph<N, E>(std::initializer_list<N> list) {
    for (const N& elem : list) {
      InsertNode(elem);
    }
  }


  // copy constructor
  Graph<N, E>(const Graph& other) {
    // copy their nodes
    for (const auto& node : other.nodes_) {
      InsertNode(*(node.node_ptr_));
    }

    // copy their edges
    for (const auto& edge : other.edges_) {
      InsertEdge(*(edge.src_ptr_), *(edge.dst_ptr_), *(edge.weight_ptr_));
    }
    std::sort(edges_.begin(), edges_.end());
  }


  // move constructor
  Graph<N, E>(Graph&& other) : nodes_{std::move(other.nodes_)}, edges_{std::move(other.edges_)} {
    std::sort(edges_.begin(), edges_.end());
  }


  /* destructor */
  ~Graph() = default;   // the vectors and smart pointers will deallocate themselves


  /* methods */
  bool IsNode(const N& val) const {
    return std::find(nodes_.cbegin(), nodes_.cend(), Node{val}) != nodes_.end();
  }


  bool InsertNode(const N& val) {
    if (IsNode(val)) {
      return false;
    }
    nodes_.push_back(Node{val});
    return true;
  }


  bool InsertEdge(const N& src, const N& dst, const E& w) {
    if (!IsNode(src) || !IsNode(dst)) {
      throw std::runtime_error(
    "Cannot call Graph::InsertEdge when either src or dst node does not exist"
      );
    }

    const auto src_iter = std::find(nodes_.cbegin(), nodes_.cend(), Node{src});
    const auto dst_iter = std::find(nodes_.cbegin(), nodes_.cend(), Node{dst});
    const Edge new_edge{(*src_iter).node_ptr_, (*dst_iter).node_ptr_, w};

    // if edge already in graph
    if (std::find(edges_.cbegin(), edges_.cend(), new_edge) != edges_.end()) {
      return false;
    } // else

    edges_.push_back(new_edge);
    std::sort(edges_.begin(), edges_.end());
    return true;
  }


  bool IsConnected(const N& src, const N& dst) const {
    if (!IsNode(src) || !IsNode(dst)) {
      throw std::runtime_error(
    "Cannot call Graph::IsConnected if src or dst node don't exist in the graph"
      );
    }

    return std::any_of(edges_.cbegin(), edges_.cend(), [&](const Edge& edge) {
      return *(edge.src_ptr_) == src && *(edge.dst_ptr_) == dst;
    });
  }


  bool DeleteNode(const N& n) {
    if (!IsNode(n)) {
      return false;
    } // else

    // delete all edges containing n (uses the erase-remove idiom)
    edges_.erase(std::remove_if(edges_.begin(), edges_.end(),
      [&](const Edge& edge) {
        return *(edge.src_ptr_) == n || *(edge.dst_ptr_) == n;
      }),
    edges_.end());

    std::sort(edges_.begin(), edges_.end());

    // then delete n from nodes
    nodes_.erase(std::find(nodes_.cbegin(), nodes_.cend(), Node{n}));
    return true;
  }


  bool Replace(const N& oldData, const N& newData) {
    if (!IsNode(oldData)) {
      throw
      std::runtime_error("Cannot call Graph::Replace on a node that doesn't exist");
    }

    if (IsNode(newData)) {
      return false;
    } // else

    // replace oldData with newData
    auto src_iter = std::find(nodes_.cbegin(), nodes_.cend(), Node{oldData});
    *((*src_iter).node_ptr_) = newData;

    std::sort(edges_.begin(), edges_.end());
    return true;
  }


  void MergeReplace(const N& oldData, const N& newData) {
    if (!IsNode(oldData) || !IsNode(newData)) {
      throw std::runtime_error(
      "Cannot call Graph::MergeReplace on old or new data if they don't exist in the graph"
      );
    }

    // replace oldData with newData
    auto src_iter = std::find(nodes_.cbegin(), nodes_.cend(), Node{oldData});
    *((*src_iter).node_ptr_) = newData;

    /*
     * look for and delete duplicate edges
     * The following code borrowed from:
     * https://en.cppreference.com/w/cpp/algorithm/unique
     */
    // sort edges_
    std::sort(edges_.begin(), edges_.end());
    // remove adjacent duplicates
    auto last = std::unique(edges_.begin(), edges_.end());
    // remove undefined values
    edges_.erase(last, edges_.end());
  }


  void Clear() {
    edges_.clear();
    nodes_.clear();
  }


  std::vector<N> GetNodes() const {
    std::vector<N> result;
    for (const auto& node : nodes_) {
      const N copy_val = *(node.node_ptr_);
      result.push_back(copy_val);
    }
    std::sort(result.begin(), result.end());
    return result;
  }


  std::vector<N> GetConnected(const N& src) const {
    if (!IsNode(src)) {
      throw std::out_of_range(
      "Cannot call Graph::GetConnected if src doesn't exist in the graph");
    }

    std::vector<N> result;
    for (const auto& edge : edges_) {
      if (*(edge.src_ptr_) == src) {
        const N copy_val = *(edge.dst_ptr_);
        result.push_back(copy_val);
      }
    }

    // sort
    std::sort(result.begin(), result.end());
    // remove adjacent duplicates
    auto last = std::unique(result.begin(), result.end());
    // remove undefined values
    result.erase(last, result.end());

    return result;
  }



    std::vector<E> GetWeights(const N& src, const N& dst) const {
      if (!IsNode(src) || !IsNode(dst)) {
        throw std::out_of_range(
        "Cannot call Graph::GetWeights if src or dst node don't exist in the graph");
      }

      vector<E> result;
      for (const auto& edge : edges_) {
        if (*(edge.src_ptr_) == src && *(edge.dst_ptr_) == dst) {
          const E copy_weight = *(edge.weight_ptr_);
          result.push_back(copy_weight);
        }
      }

      return result;
    }


    bool erase(const N& src, const N& dst, const E& w) {
      const auto src_iter = std::find(nodes_.cbegin(), nodes_.cend(), Node{src});
      const auto dst_iter = std::find(nodes_.cbegin(), nodes_.cend(), Node{dst});
      if (src_iter == nodes_.end() || dst_iter == nodes_.end()) {
        return false;
      } // else

      const Edge tmp{(*src_iter).node_ptr_, (*dst_iter).node_ptr_, w};
      auto it = std::find(edges_.cbegin(), edges_.cend(), tmp);
      if (it == edges_.end()) {
        return false;
      } // else

      edges_.erase(it);
      std::sort(edges_.begin(), edges_.end());
      return true;
    }

    friend bool operator==(const Graph& a, const Graph& b) {
      return a.nodes_ == b.nodes_ && a.edges_ == b.edges_;
    }

    friend bool operator!=(const Graph& a, const Graph& b) {
      return !(a == b);
    }

    friend std::ostream& operator<<(std::ostream& os, const Graph& graph) {
      auto tmp_nodes = graph.nodes_;
      std::sort(tmp_nodes.begin(), tmp_nodes.end());

      /*
      for node in graph:
          print "<node> ("
          for edge where src == node:
              print "<dst> | <weight>"
          print ")"
      */
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


    // debugging functions; remove from final version
    void printNodes(void) const {
      for (const auto& node : nodes_) {
        // "node = <address in memory>, *node = string_representation"
        cout << "node = " << node.node_ptr_ << ", *node = \"" << *(node.node_ptr_) << "\"\n";
      }
    }
    void printEdges(void) const {
      for (const auto& edge : edges_) {
        // "edge = src -> dst, weight = 5"
        cout << "edge = " << *(edge.src_ptr_) << " -> " << *(edge.dst_ptr_) << ", weight = " << *(edge.weight_ptr_) << '\n';
      }
    }



 private:
   vector<Node> nodes_;
   vector<Edge> edges_;
};

}  // namespace gdwg

#include "assignments/dg/graph.tpp"

#endif  // ASSIGNMENTS_DG_GRAPH_H_
