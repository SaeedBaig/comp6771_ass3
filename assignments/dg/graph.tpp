//implementation for graph

using namespace gdwg;
template <typename N, typename E>
Graph<N, E>::Graph(typename std::vector<N>::const_iterator start, typename std::vector<N>::const_iterator end) {
	while(start!=end) {
		  std::cout << *start << std::endl;
		  auto copy = *start;
		  nodes_.insert(copy);
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
		  edges_.push_back(e);
		  nodes_.insert(e.GetFrom());
		  nodes_.insert(e.GetTo());
	  	  start++;
	  }
}

template <typename N, typename E>
Graph<N, E>::Graph(typename std::initializer_list<N> list) {
	  for(const auto element:list) {
		  nodes_.insert(element);
	  }
 }

template <typename N, typename E>
Graph<N, E>::Graph(const Graph<N, E>& graph) {
	  nodes_=graph.nodes_;

	  for(auto e: graph.edges_) {
		  Edge copy_edge {e.GetFrom(),e.GetTo(),e.GetWeight()};
		  edges_.push_back(copy_edge);
		  //TODO: add redundant check
		  std::cout << e.GetFrom() << std::endl;
		  std::cout << e.GetTo() << std::endl; 
		  nodes_.insert(e.GetFrom());
		  nodes_.insert(e.GetTo());
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
	  std::cout << "copy operator called" << std::endl;
	  
	  nodes_=graph.nodes_;

	  for(auto e: graph.edges_) {
		  Edge copy_edge {e.GetFrom(),e.GetTo(),e.GetWeight()};
		  edges_.push_back(copy_edge);
	  }
	  
	  return *this;
}

template <typename N, typename E>
Graph<N, E>& Graph<N,E>::operator=(Graph<N, E>&& graph) {
	std::cout << "move operator called" << std::endl;
	nodes_=std::move(graph.nodes_);
	edges_=std::move(graph.edges_);
	return *this;
}

template <typename N, typename E>
bool Graph<N,E>::IsNode(const N& val) {
	  //std::cout << val << std::endl;
	  //contains
	  if(nodes_.find(val)!=nodes_.end()) {
		  return true;
	  }
	  return false;
}