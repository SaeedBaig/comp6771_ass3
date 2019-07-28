#include <iostream>
#include "graph.h"
#include <string>
//using namespace gdwg;

int main() {
	std::string s1{"Hello"};
	std::string s2{"how"};
	std::string s3{"are"};
	auto e1 = std::make_tuple(s1, s2, 5.4);
	auto e2 = std::make_tuple(s2, s3, 7.6);
	auto e = std::vector<std::tuple<std::string, std::string, double>>{e1, e2};
	Graph<std::string, double> graph{e.begin(), e.end()};
	std::cout << graph.IsNode("Hello") << std::endl;
	std::cout << graph.IsNode("how") << std::endl;
	std::cout << graph.IsNode("are") << std::endl;
	return 0;
}
