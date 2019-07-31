//implementation for graph
#include <string>

using namespace gdwg;
template <typename N, typename E>
Graph<N, E>::Graph(typename std::vector<N>::const_iterator start, typename std::vector<N>::const_iterator end) {
	while(start!=end) {
		  nodes_.push_back(std::make_shared<Node>(*start));
		  start++;
	  }
}

template <typename N, typename E>
Graph<N, E>::Graph(typename std::vector<std::tuple<N, N, E>>::const_iterator start,
    typename std::vector<std::tuple<N, N, E>>::const_iterator end) {
	  while(start!=end) {
		  auto curr = *start;
		  Edge e {std::get<0>(curr),std::get<1>(curr),std::get<2>(curr)};
		  //TODO: add the custom iteartor check in here
		  edges_.push_back(std::make_shared<Edge>(e));
		  nodes_.push_back(std::make_shared<Node>(std::get<0>(curr)));
		  nodes_.push_back(std::make_shared<Node>(std::get<1>(curr)));
	  	  start++;
	  }
}

template <typename N, typename E>
Graph<N, E>::Graph(typename std::initializer_list<N> list) {
	  for(const auto element:list) {
		  nodes_.push_back(std::make_shared<Node>(element));
	  }
 }

template <typename N, typename E>
Graph<N, E>::Graph(const Graph<N, E>& graph) {
	  nodes_=graph.nodes_;

	  for(auto e: graph.edges_) {
	  	  Edge copy_edge {*e->from_,*e->to_,*e->weight_};
	  	  //TODO: add redundant check
		  edges_.push_back(std::make_shared<Edge>(copy_edge));
		  nodes_.push_back(std::make_shared<Node>(*e->from_));
		  nodes_.push_back(std::make_shared<Node>(*e->to_));
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
		  nodes_.push_back(std::make_shared<Node>(*e->from_));
		  nodes_.push_back(std::make_shared<Node>(*e->to_));
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
	  auto search_iter = std::find_if(nodes_.begin(), nodes_.end(), [&val](std::shared_ptr<Node> n) {
	          return n->getNodeName() == val;
	  });
	  
	  if (search_iter!=nodes_.end()) {
	  	return true;
	  }
	  return false;
}

template <typename N, typename E>
bool Graph<N,E>::InsertNode(const N& val) {
	if (IsNode(val)) {
		return false;
	}
	
	nodes_.push_back(std::make_shared<Node>(val));
	return true;
}


template <typename N, typename E>
bool Graph<N,E>::InsertEdge(const N& src, const N& dst, const E& w) {
	 //std::cout << "method called " << edges_.size() << std::endl;

	  if(edges_.size()==0) {
		  Edge tmpEdge {src,dst,w};
		  auto sharedPtr = std::make_shared<Edge>(tmpEdge);
		  edges_.push_back(sharedPtr);
		  nodes_.push_back(std::make_shared<Node>(src));
		  nodes_.push_back(std::make_shared<Node>(dst));
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
	  nodes_.push_back(std::make_shared<Node>(src));
	  nodes_.push_back(std::make_shared<Node>(dst));
  	  return true;
}

/*
template <typename N, typename E>
auto GetEdgeIterByValue(const N& value) {
	auto edge_iter = std::find_if(edges_.begin(), edges_.end(), [&val](std::shared_ptr<Edge> edge){
	        return *edge->from_ == val || *edge->to_==val;
	});
}
*/

template <typename N, typename E>
//true if removed or otherwise false

bool Graph<N,E>::DeleteNode(const N& val) {
	
	auto del_iter = std::find_if(nodes_.begin(), nodes_.end(), [&val](std::shared_ptr<Node> n){
	  return n->getNodeName() == val;
	});

	if(del_iter == nodes_.end()) return false;
	nodes_.erase(del_iter);

	//TODO: while(hasEdge) del->edge, del,nodes,associated
	//start deleting edges
	
	/*
	std::unordered_set<std::shared_ptr<N>> nodes_to_be_deleted;
	
	while (auto edge_iter = GetEdgeIterByValue(val)==edges_end()) {
		nodes_to_be_deleted.insert(*edge_iter->from_);
		nodes_to_be_deleted.insert(*edge_iter->to_);
	}
	*/
	
	auto edge_iter = std::find_if(edges_.begin(), edges_.end(), [&val](std::shared_ptr<Edge> edge){
	        return *edge->from_ == val || *edge->to_==val;
	});

	if(edge_iter == edges_.end()) return false;
	edges_.erase(edge_iter);

  	return true;
	
}

/*
template <typename N, typename E>
bool Graph<N,E>::Replace(const N& oldData, const N& newData) {
	
	//replace node data 
	
	//search for the node
	auto search_iter = std::find_if(nodes_.begin(), nodes_.end(), [&val](std::shared_ptr<N> n) {
          return *n == val;
  	});
  	
  	//found element
  	if (search_iter != nodes_.end()) {
  		//access the content of the iter element
  		
  	}
  	
  	//deleting by iterator is the only way
	//replace edge data
}

*/