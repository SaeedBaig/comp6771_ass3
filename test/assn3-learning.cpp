#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <set>

using namespace std;

// One function works for all data types. This would work
// even for user defined types if operator '>' is overloaded
template <typename N, typename E>
class Graph {
 public:
  //constructors
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

  //template <typename std::vector<N>::const_iterator>
  Graph<N, E>(typename std::vector<N>::const_iterator first, typename std::vector<N>::const_iterator end) {
	  while(first!=end) {
		  std::cout << *first << std::endl;
		  first++;
	  }
  }

  /*
  Graph<N, E>(std::vector<std::string>::const_iterator start, std::vector<std::string>::const_iterator end) {
	  while(start!=end) {
		  std::cout << *start << std::endl;
		  start++;
	  }
  }
  */


  /*
  E GetWeight() {
	  return *weight_;
  }

  N GetNodeName() {
	  return *node_name_;
  }
  */


 private:
  	  std::weak_ptr<N> node_name_;
  	  std::weak_ptr<E> weight_;

  	  std::set<N> nodes;
  	  std::set<E> edges;
};

int main() {
	std::cout << "test" << std::endl;
	//Graph<std::string,double> graph {"melbourne",2.2};

	std::vector<std::string> v{"Hello", "how", "are", "you"};
	//gdwg::Graph<std::string, double> b{v.begin(),v.end()};
	Graph<std::string, double> b{v.begin(),v.end()};

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
