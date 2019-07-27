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
	  	  start++;
	  }
}

template <typename N, typename E>
bool Graph<N,E>::IsNode(const N& val) {
	 std::cout << val << std::endl;
	  //contains
	  if(nodes_.find(val)!=nodes_.end()) {
		  return true;
	  }
	  return false;
}