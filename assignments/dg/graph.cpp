//implementation for graph

#include "graph.h"
using namespace gdwg;

template <typename N, typename E>
Graph<N, E>::Graph(typename std::vector<N>::const_iterator start, typename std::vector<N>::const_iterator end) {
	for (auto it = start; it != end; ++it) {
	      InsertNode(*it);
	}
}

template <typename N, typename E>
Graph<N, E>::Graph(typename std::vector<std::tuple<N, N, E>>::const_iterator start,
    typename std::vector<std::tuple<N, N, E>>::const_iterator end) {
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

template <typename N, typename E>
Graph<N, E>::Graph(typename std::initializer_list<N> list) {
	  for(const N& element:list) {
		  InsertNode(element);
	  }
}

template <typename N, typename E>
Graph<N, E>::Graph(const Graph& other) {
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

template <typename N, typename E>
Graph<N, E>& Graph<N,E>::operator=(const Graph<N, E>& other) {
	nodes_=graph.nodes_;

  for(auto e: graph.edges_) {
	  Edge copy_edge{*e->from_,*e->to_,*e->weight_};
	  edges_.push_back(std::make_shared<Edge>(copy_edge));
	  //TODO: add redundant check
	  nodes_.push_back(std::make_shared<Node>(*e->from_));
	  nodes_.push_back(std::make_shared<Node>(*e->to_));
  }
  return *this;
}

template <typename N, typename E>
bool Graph<N,E>::IsNode(const N& val) {
	return std::find(nodes_.cbegin(), nodes_.cend(), Node{val}) != nodes_.end();
}

template <typename N, typename E>
bool Graph<N,E>::InsertNode(const N& val) {
    if (IsNode(val)) {
      return false;
    }
    nodes_.push_back(Node{val});
    return true;
}

template <typename N, typename E>
bool Graph<N,E>::InsertEdge(const N& src, const N& dst, const E& w) {
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


template <typename N, typename E>
Graph<N, E>::Graph(Graph&& other) : nodes_{std::move(other.nodes_)}, edges_{std::move(other.edges_)} {
    std::sort(edges_.begin(), edges_.end());
}


template <typename N, typename E>
bool Graph<N,E>::DeleteNode(const N& n) {
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

template <typename N, typename E>
bool Graph<N,E>::IsConnected(const N& src, const N& dst) const {
	if (!IsNode(src) || !IsNode(dst)) {
      throw std::runtime_error(
    "Cannot call Graph::IsConnected if src or dst node don't exist in the graph"
      );
    }

    return std::any_of(edges_.cbegin(), edges_.cend(), [&](const Edge& edge) {
      return *(edge.src_ptr_) == src && *(edge.dst_ptr_) == dst;
    });
}

template <typename N, typename E>
bool Graph<N,E>::Replace(const N& oldData, const N& newData) {
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

//start from here

template <typename N, typename E>
void MergeReplace(const N& oldData, const N& newData) {
	if (!IsNode(oldData) || !IsNode(newData)) {
      throw std::runtime_error(
      "Cannot call Graph::MergeReplace on old or new data if they don't exist in the graph"
      );
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

template <typename N, typename E>
void Graph<N,E>::Clear() {
  edges_.clear();
  nodes_.clear();
}

template <typename N, typename E>
std::vector<N> GetNodes() const {
    std::vector<N> result;
    for (const auto& node : nodes_) {
      const N copy_val = *(node.node_ptr_);
      result.push_back(copy_val);
    }
    std::sort(result.begin(), result.end());
    return result;
}

template <typename N, typename E>
std::vector<N> Graph<N,E>::GetConnected(const N& src) const {
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


template <typename N, typename E>
std::vector<E> Graph<N,E>::GetWeights(const N& src, const N& dst) const {
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

template <typename N, typename E>
bool Graph<N,E>::erase(const N& src, const N& dst, const E& w) {
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


