#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <unordered_set>
#include <tuple>
#include <set>

using namespace std;

// One function works for all data types. This would work
// even for user defined types if operator '>' is overloaded
template <typename N, typename E>
class Graph {
 public:
	class Edge {
		public:
			Edge(N from, N to, E weight):from_(from),to_(to),weight_(weight) {}
			//Edge(std::weak_ptr<N> from, std::<N> to, E weight):from_(from),to_(to),weight_(weight) {}

			N GetFrom() {
				return from_;
			}

			N GetTo() {
				return to_;
			}

			E GetWeight() {
				return weight_;
			}

	 private:
		N from_;
		N to_;
		E weight_;
	};

  Graph<N, E>() {}

  //custom test constructors
  Graph<N, E>(N node_name, E weight) {
	  //node_name_ = node_name;
	  //weight_ = weight;
	  auto share_ptr_for_node=std::make_shared<N>(node_name);
	  node_name_ = share_ptr_for_node;

	  if( auto sharedPtr1 = node_name_.lock() ) {
	    std::cout << "*sharedPtr1: " << *sharedPtr1 << std::endl;
	    std::cout << "sharedPtr1.use_count(): " << sharedPtr1.use_count() << std::endl;
	  }

	  auto share_ptr_for_weight=std::make_shared<E>(weight);
	  weight_ = share_ptr_for_weight;

	  if( auto sharedPtr1 = weight_.lock() ) {
	  	   std::cout << "*sharedPtr1: " << *sharedPtr1 << std::endl;
	  	   std::cout << "sharedPtr1.use_count(): " << sharedPtr1.use_count() << std::endl;
	  }
  }

  ~Graph<N,E>() {
	  std::cout << "hello i am graph and i am out of scope!" << std::endl;
  }

  //template <typename std::vector<N>::const_iterator>
  Graph<N, E>(typename std::vector<N>::const_iterator start, typename std::vector<N>::const_iterator end) {
	  while(start!=end) {
		  std::cout << *start << std::endl;
		  auto copy = *start;
		  nodes_.insert(copy);
		  start++;
	  }
  }

  Graph<N, E>(typename std::vector<std::tuple<N, N, E>>::const_iterator start, typename std::vector<std::tuple<N, N, E>>::const_iterator end) {
	  while(start!=end) {
		  auto curr = *start;
		  Edge e {std::get<0>(curr),std::get<1>(curr),std::get<2>(curr)};
		  //edges.insert(e);
		  //TODO: add the custom iteartor check in here
		  edges_.push_back(e);
	  	  start++;
	  }
  }

  Graph<N, E>(typename std::initializer_list<N> list) {
	  for(const auto element:list) {
		  nodes_.insert(element);
	  }
  }

  Graph<N, E>(const Graph<N, E>& graph) {
	  nodes_=graph.nodes_;

	  for(auto e: graph.edges_) {
		  Edge copy_edge {e.GetFrom(),e.GetTo(),e.GetWeight()};
		  edges_.push_back(copy_edge);
	  }
  }

  Graph<N, E>(Graph<N, E>&& graph) {
	  nodes_=std::move(graph.nodes_);
	  edges_=std::move(graph.edges_);
  }

  bool isNode(const N& val) {
	  //contains
	  if(nodes_.find(val)!=nodes_.end()) {
		  return true;
	  }
	  return false;

  }

  /*
  const_iterator find(const N& from, const N& to, const E& weight) {
	 //std::<vector<std::<Edge>> constItr::iteartor=edges.begin();
	 for(auto e:edges) {

		 if (e.from_==from && e.to_==to && e.weight_==weight) {
			 return true;
		 }
	 }

	 return false;
 }
 */

 private:
  	  std::weak_ptr<N> node_name_; //need to use this
  	  std::weak_ptr<E> weight_;

  	  std::unordered_set<N> nodes_;
  	  std::vector<Edge> edges_;
};

int main() {
	//Graph<std::string,double> graph {"melbourne",2.2};
	/*
	Graph<std::string,int> a;
	std::cout << a.isNode("hello") << '\n';
	Graph<std::string,double> dougraph;

	{
		std::vector<std::string> v{"Hello", "how", "are", "you"};
			//gdwg::Graph<std::string, double> b{v.begin(),v.end()};
			Graph<std::string, double> b{v.begin(),v.end()};
			if (b.isNode("Hello")) {
				std::cout << "true" << std::endl;
			} else {
				std::cout << "false" << std::endl;
			}

	}

	//
	{
		std::string s1{"Hello"};
		std::string s2{"how"};
		std::string s3{"are"};
		auto e1 = std::make_tuple(s1, s2, 5.4);
		auto e2 = std::make_tuple(s2, s3, 7.6);
		auto e = std::vector<std::tuple<std::string, std::string, double>>{e1, e2};
		Graph<std::string, double> b{e.begin(), e.end()};

		if (b.isNode("Hello")) {
			std::cout << "true" << std::endl;
		} else {
			std::cout << "false" << std::endl;
		}

		if (b.isNode("test")) {
					std::cout << "true" << std::endl;
				} else {
					std::cout << "false" << std::endl;
				}
	}


	{
		Graph<char, std::string> b{'a', 'b', 'x', 'y'};

		if (b.isNode('H')) {
			std::cout << "true" << std::endl;
		} else {
			std::cout << "false" << std::endl;
		}

		if (b.isNode('x')) {
			std::cout << "true" << std::endl;
		} else {
			std::cout << "false" << std::endl;
		}
	}*/

	{
		std::vector<std::string> v{"Hello", "how", "are", "you"};
		//gdwg::Graph<std::string, double> b{v.begin(),v.end()};
		Graph<std::string, double> b{v.begin(),v.end()};
		Graph<std::string, double> aCopy{b};

	}



	return 0;
}

/*
N myMax(N x, N y) {
	return (x > y)? x: y;
}

int main() {
	cout << myMax<int>(3, 7) << endl; // Call myMax for int
	cout << myMax<double>(3.0, 7.0) << endl; // call myMax for double
	cout << myMax<char>('g', 'e') << endl; // call myMax for char
	return 0;
}
*/
