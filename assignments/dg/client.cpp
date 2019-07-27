#include <iostream>
#include "graph.h"
#include <string>
//using namespace gdwg;

int main() {
	//Graph<std::string,int> a;
	//gdwg::Graph<int, int> a;
	//gdwg::Graph<int, int> b {};

	std::vector<std::string> v{"Hello", "how", "are", "you"};
	gdwg::Graph<std::string, double> b{v.begin(),v.end()};

	if (b.IsNode("Hello")) {
			std::cout << "true" << std::endl;
		} else {
			std::cout << "false" << std::endl;
	}
	return 0;
}
