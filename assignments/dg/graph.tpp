//implementation for graph
#include <string>

using namespace gdwg;
template <typename N, typename E>
Graph<N, E>::Graph(typename std::vector<N>::const_iterator start, typename std::vector<N>::const_iterator end) {
	while(start!=end) {
		  //std::cout << *start << std::endl;
		  nodes_.insert(std::make_shared<N>(*start));
		  start++;
	  }
}


template <typename N, typename E>
Graph<N, E>::Graph(typename std::vector<std::tuple<N, N, E>>::const_iterator start,
    typename std::vector<std::tuple<N, N, E>>::const_iterator end) {
	  while(start!=end) {
		  auto curr = *start;
		  Edge e {std::get<0>(curr),std::get<1>(curr),std::get<2>(curr)};
		  //edges.insert(e);
		  //TODO: add the custom iteartor check in here
		  edges_.push_back(std::make_shared<Edge>(e));
		  std::cout << std::get<0>(curr) << std::get<1>(curr) << std::endl;
		  nodes_.insert(std::make_shared<N>(std::get<0>(curr)));
		  nodes_.insert(std::make_shared<N>(std::get<1>(curr)));
	  	  start++;
	  }
}

template <typename N, typename E>
Graph<N, E>::Graph(typename std::initializer_list<N> list) {
	  for(const auto element:list) {
		  nodes_.insert(std::make_shared<N>(element));
	  }
 }

template <typename N, typename E>
Graph<N, E>::Graph(const Graph<N, E>& graph) {
	  nodes_=graph.nodes_;

	  for(auto e: graph.edges_) {
	  	  Edge copy_edge {*e->from_,*e->to_,*e->weight_};
		  edges_.push_back(std::make_shared<Edge>(copy_edge));
		  //TODO: add redundant check
		  nodes_.insert(std::make_shared<N>(*e->from_));
		  nodes_.insert(std::make_shared<N>(*e->to_));
	  }
}

template <typename N, typename E>
Graph<N, E>::Graph(Graph<N, E>&& graph) {
	  nodes_=std::move(graph.nodes_);
	  edges_=std::move(graph.edges_);
}


template <typename N, typename E>
//EuclideanVector& EuclideanVector:: operator=(const EuclideanVector& vec)
Graph<N, E>& Graph<N,E>::operator=(const Graph<N, E>& graph) {
	  nodes_=graph.nodes_;

	  for(auto e: graph.edges_) {
	  	  Edge copy_edge{*e->from_,*e->to_,*e->weight_};
		  edges_.push_back(std::make_shared<Edge>(copy_edge));
		  //TODO: add redundant check
		  nodes_.insert(std::make_shared<N>(*e->from_));
		  nodes_.insert(std::make_shared<N>(*e->to_));
	  }
	  return *this;
}

template <typename N, typename E>
Graph<N, E>& Graph<N,E>::operator=(Graph<N, E>&& graph) {
	std::cout << "move operator called" << std::endl;
	nodes_=std::move(graph.nodes_);
	//fix this
	//edges_=std::move(graph.edges_);
	return *this;
}

template <typename N, typename E>
bool Graph<N,E>::IsNode(const N& val) {
	for (auto curr: nodes_) {
		if (*curr == val) {
			return true;
		}
	}
	  /*
	  if(nodes_.find(val)!=nodes_.end()) {
		  return true;
	  }
	  
	  
	  if(nodes_.find(std::make_shared<N>(val))!=nodes_.end()) {
		  return true;
	  }
	  */
	  return false;
}

template <typename N, typename E>
bool Graph<N,E>::InsertNode(const N& val) {
	if (IsNode(val)) {
		return false;
	}
	
	nodes_.insert(std::make_shared<N>(val));
	return true;
}


template <typename N, typename E>
bool Graph<N,E>::InsertEdge(const N& src, const N& dst, const E& w) {
	 //std::cout << "method called " << edges_.size() << std::endl;

	  if(edges_.size()==0) {
		  Edge tmpEdge {src,dst,w};
		  auto sharedPtr = std::make_shared<Edge>(tmpEdge);
		  edges_.push_back(sharedPtr);
		  nodes_.insert(std::make_shared<N>(src));
		  nodes_.insert(std::make_shared<N>(dst));
		  return true;
	  }

	  for(auto edge: edges_) {
		//std::cout << *edge->from_ << " " << *edge->to_ << " " << *edge->weight_ << std::endl;
		if ((*edge->from_)==src &&(*edge->to_)==dst && (*edge->weight_)==w) {
			std::cout << "false found!" << *edge->from_ << std::endl;
			return false;
		}
	  }

	  Edge tmpEdge {src,dst,w};
	  auto sharedPtr = std::make_shared<Edge>(tmpEdge);
	  edges_.push_back(sharedPtr);
	  nodes_.insert(std::make_shared<N>(src));
	  nodes_.insert(std::make_shared<N>(dst));
  	  return true;
}

/*
template <typename N, typename E>
//true if removed or otherwise false

bool Graph<N,E>::DeleteNode(const N&) {
	//pre-condition:assume after each time inserting edges nodes keep track of the item
	if(!IsNode(N)) {
		return false;
	}
	
	nodes_.erase (N);
	
	std::vector<N>::iterator iter;
	//this method only work once
	for(iter=edges_.begin();iter!=edges_.end();iter++) {
	
	}

	for(auto& edge: edges_ ) {
		if(edge.GetFrom()==N) {
			edges_.
		}
	}
	
}
*/