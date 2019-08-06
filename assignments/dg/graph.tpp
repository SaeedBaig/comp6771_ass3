// implementation for graph

#include <algorithm>
#include <iterator>
#include <memory>
#include <string>
#include <tuple>
#include <vector>

using std::vector;

using namespace gdwg;


// iterator-of-nodes constructor
template <typename N, typename E>
Graph<N, E>::Graph(typename std::vector<N>::const_iterator start,
                   typename std::vector<N>::const_iterator end) {
  const auto num_nodes = std::distance(start, end);
  nodes_.reserve(num_nodes);

  for (auto it = start; it != end; ++it) {
    InsertNode(*it);
  }
}


// iterator-of-tuples constructor
template <typename N, typename E>
Graph<N, E>::Graph(
    typename std::vector<std::tuple<N, N, E>>::const_iterator start,
    typename std::vector<std::tuple<N, N, E>>::const_iterator end) {
  const auto num_edges = std::distance(start, end);
  edges_.reserve(num_edges);
  nodes_.reserve(num_edges); // #nodes may be > #edges, but this is just a rough
                             // approximation

  for (auto it = start; it != end; ++it) {
    const N &src = std::get<0>(*it);
    const N &dst = std::get<1>(*it);
    const E &w = std::get<2>(*it);

    InsertNode(src);
    InsertNode(dst);
    InsertEdge(src, dst, w);
  }
  std::sort(edges_.begin(), edges_.end());
}


// list constructor
template <typename N, typename E>
Graph<N, E>::Graph(typename std::initializer_list<N> list) {
  nodes_.reserve(list.size());
  for (const N &element : list) {
    InsertNode(element);
  }
}


// copy constructor
template <typename N, typename E> Graph<N, E>::Graph(const Graph &other) {
  // copy their nodes
  nodes_.reserve(other.nodes_.size());
  for (const auto &node : other.nodes_) {
    InsertNode(*(node.node_ptr_));
  }

  // copy their edges
  edges_.reserve(other.edges_.size());
  for (const auto &edge : other.edges_) {
    InsertEdge(*(edge.src_ptr_), *(edge.dst_ptr_), *(edge.weight_ptr_));
  }

  std::sort(edges_.begin(), edges_.end());
}


// move constructor
template <typename N, typename E>
Graph<N, E>::Graph(Graph &&other)
    : nodes_{std::move(other.nodes_)}, edges_{std::move(other.edges_)} {
  std::sort(edges_.begin(), edges_.end());
}


// copy assignment
template <typename N, typename E>
Graph<N, E> &Graph<N, E>::operator=(const Graph<N, E> &other) {
  Clear();

  // copy their nodes
  nodes_.reserve(other.nodes_.size());
  for (const auto &node : other.nodes_) {
    InsertNode(*(node.node_ptr_));
  }

  // copy their edges
  edges_.reserve(other.edges_.size());
  for (const auto &edge : other.edges_) {
    InsertEdge(*(edge.src_ptr_), *(edge.dst_ptr_), *(edge.weight_ptr_));
  }

  std::sort(edges_.begin(), edges_.end());

  return *this;
}


// move assignment
template <typename N, typename E>
Graph<N, E> &Graph<N, E>::operator=(Graph<N, E> &&other) {
  nodes_ = std::move(other.nodes_);
  edges_ = std::move(other.edges_);
  return *this;
}


// IsNode
template <typename N, typename E> bool Graph<N, E>::IsNode(const N &val) const {
  return std::any_of(nodes_.cbegin(), nodes_.cend(), [&](const Node &node) {
    return *(node.node_ptr_) == val;
  });
}


// InsertNode
template <typename N, typename E> bool Graph<N, E>::InsertNode(const N &val) {
  if (IsNode(val)) {
    return false;
  }
  nodes_.push_back(Node{val});
  return true;
}


// InsertEdge
template <typename N, typename E>
bool Graph<N, E>::InsertEdge(const N &src, const N &dst, const E &w) {
  if (!IsNode(src) || !IsNode(dst)) {
    throw std::runtime_error("Cannot call Graph::InsertEdge when either src or "
                             "dst node does not exist");
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


// DeleteNode
template <typename N, typename E> bool Graph<N, E>::DeleteNode(const N &n) {
  if (!IsNode(n)) {
    return false;
  } // else

  // delete all edges containing n (uses the erase-remove idiom)
  edges_.erase(std::remove_if(edges_.begin(), edges_.end(),
                              [&](const Edge &edge) {
                                return *(edge.src_ptr_) == n ||
                                       *(edge.dst_ptr_) == n;
                              }),
               edges_.end());

  std::sort(edges_.begin(), edges_.end());

  // then delete n from nodes
  nodes_.erase(std::find(nodes_.cbegin(), nodes_.cend(), Node{n}));
  return true;
}


// IsConnected
template <typename N, typename E>
bool Graph<N, E>::IsConnected(const N &src, const N &dst) const {
  if (!IsNode(src) || !IsNode(dst)) {
    throw std::runtime_error("Cannot call Graph::IsConnected if src or dst "
                             "node don't exist in the graph");
  }

  return std::any_of(edges_.cbegin(), edges_.cend(), [&](const Edge &edge) {
    return *(edge.src_ptr_) == src && *(edge.dst_ptr_) == dst;
  });
}


// Replace
template <typename N, typename E>
bool Graph<N, E>::Replace(const N &oldData, const N &newData) {
  if (!IsNode(oldData)) {
    throw std::runtime_error(
        "Cannot call Graph::Replace on a node that doesn't exist");
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


// MergeReplace
template <typename N, typename E>
void Graph<N, E>::MergeReplace(const N &oldData, const N &newData) {
  if (!IsNode(oldData) || !IsNode(newData)) {
    throw std::runtime_error("Cannot call Graph::MergeReplace on old or new "
                             "data if they don't exist in the graph");
  }

  // replace oldData with newData
  auto src_iter = std::find(nodes_.cbegin(), nodes_.cend(), Node{oldData});
  *((*src_iter).node_ptr_) = newData;

  //
  // look for and delete duplicate edges
  // The following code borrowed from:
  // https://en.cppreference.com/w/cpp/algorithm/unique
  //
  // sort edges_
  std::sort(edges_.begin(), edges_.end());
  // remove adjacent duplicates
  auto last = std::unique(edges_.begin(), edges_.end());
  // remove undefined values
  edges_.erase(last, edges_.end());
}


// Clear
template <typename N, typename E> void Graph<N, E>::Clear() {
  edges_.clear();
  nodes_.clear();
}


// GetNodes
template <typename N, typename E> std::vector<N> Graph<N, E>::GetNodes() const {
  vector<N> result;
  result.reserve(nodes_.size());

  for (const auto &node : nodes_) {
    result.push_back(*(node.node_ptr_));
  }

  std::sort(result.begin(), result.end());
  return result;
}


// GetConnected
template <typename N, typename E>
std::vector<N> Graph<N, E>::GetConnected(const N &src) const {
  if (!IsNode(src)) {
    throw std::out_of_range(
        "Cannot call Graph::GetConnected if src doesn't exist in the graph");
  }

  vector<N> result;
  result.reserve(edges_.size());

  for (const auto &edge : edges_) {
    if (*(edge.src_ptr_) == src) {
      result.push_back(*(edge.dst_ptr_));
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


// GetWeights
template <typename N, typename E>
std::vector<E> Graph<N, E>::GetWeights(const N &src, const N &dst) const {
  if (!IsNode(src) || !IsNode(dst)) {
    throw std::out_of_range("Cannot call Graph::GetWeights if src or dst node "
                            "don't exist in the graph");
  }

  vector<E> result;
  result.reserve(edges_.size());

  for (const auto &edge : edges_) {
    if (*(edge.src_ptr_) == src && *(edge.dst_ptr_) == dst) {
      result.push_back(*(edge.weight_ptr_));
    }
  }

  return result;
}


// erase(src, dst, w)
template <typename N, typename E>
bool Graph<N, E>::erase(const N &src, const N &dst, const E &w) {
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


// * operator for const_iterator
template <typename N, typename E>
typename Graph<N, E>::const_iterator::reference Graph<N, E>::const_iterator::
operator*() const {
  const N &node1 = *((*it_).src_ptr_);
  const N &node2 = *((*it_).dst_ptr_);
  const E &edge_w = *((*it_).weight_ptr_);
  return {node1, node2, edge_w};
}


// ++ operator (prefix) for const_iterator
template <typename N, typename E>
typename Graph<N, E>::const_iterator &Graph<N, E>::const_iterator::
operator++() {
  ++it_;
  return *this;
}


// ++ operator (postfix) for const_iterator
template <typename N, typename E>
typename Graph<N, E>::const_iterator Graph<N, E>::const_iterator::
operator++(int) {
  auto copy{*this};
  ++(*this);
  return copy;
}


// -- operator (prefix) for const_iterator
template <typename N, typename E>
typename Graph<N, E>::const_iterator &Graph<N, E>::const_iterator::
operator--() {
  --it_;
  return *this;
}


// -- operator (postfix) for const_iterator
template <typename N, typename E>
typename Graph<N, E>::const_iterator Graph<N, E>::const_iterator::
operator--(int) {
  auto copy{*this};
  --(*this);
  return copy;
}


// find
template <typename N, typename E>
typename Graph<N, E>::const_iterator
Graph<N, E>::find(const N &src, const N &dst, const E &w) const {
  const auto it =
      std::find_if(edges_.cbegin(), edges_.cend(), [&](const Edge &edge) {
        return *(edge.src_ptr_) == src && *(edge.dst_ptr_) == dst &&
               *(edge.weight_ptr_) == w;
      });

  if (it != edges_.end()) {
    return const_iterator{it};
  } // else
  return cend();
}


// erase(it)
template <typename N, typename E>
typename Graph<N, E>::const_iterator Graph<N, E>::erase(const_iterator it) {
  const auto iter = edges_.erase(it.it_);
  if (iter != edges_.end()) {
    return const_iterator{iter};
  } // else
  return end();
}
